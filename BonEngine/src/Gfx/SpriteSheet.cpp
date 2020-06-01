#include <Gfx/SpriteSheet.h>
#include <Assets/Types/Config.h>
#include <string>
#include <algorithm>
#include <iterator>
#include <Framework/Exceptions.h>

namespace bon
{
	namespace gfx
	{
		// get a string in format of "x,y", and extract x and y components from it.
		void SplitPointStr(const std::string& str, int& outX, int& outY)
		{
			try
			{
				std::string xStr = str.substr(0, str.find(','));
				outX = std::stoi(xStr);
				std::string yStr = str.substr(str.find(',') + 1);
				outY = std::stoi(yStr);
			}
			catch (const std::exception&)
			{
				throw framework::AssetLoadError("Invalid point format! Must be 'x,y'.");
			}
		}

		// split strings by delimiter
		template <class Container>
		void SplitString(const std::string& str, Container& cont, char delim = ' ')
		{
			std::size_t current, previous = 0;
			current = str.find(delim);
			while (current != std::string::npos) {
				cont.push_back(str.substr(previous, current - previous));
				previous = current + 1;
				current = str.find(delim, previous);
			}
			cont.push_back(str.substr(previous, current - previous));
		}

		// create the spritesheet from config file.
		SpriteSheet::SpriteSheet(assets::ConfigAsset config)
		{
			LoadFromConfig(config);
		}

		// load from config file
		void SpriteSheet::LoadFromConfig(assets::ConfigAsset config)
		{
			// clear animations
			_animations.clear();

			// get sprites count in spritesheet
			std::string spritesCountStr(config->GetStr("general", "sprites_count", "1,1"));
			SplitPointStr(spritesCountStr, SpritesCount.X, SpritesCount.Y);

			// get animation names
			std::string animations(config->GetStr("general", "animations", ""));
			if (!animations.empty())
			{
				// convert to list
				std::list<std::string> animsList;
				SplitString(animations, animsList, ',');

				// iterate and init animations
				for (auto animName : animsList)
				{
					SpriteAnimationPtr curr(new SpriteAnimation(animName.c_str(), config));
					_animations[animName] = curr;
				}
			}

			// get bookmarks
			auto bookmarks = config->Keys("bookmarks");
			for (auto bookid : bookmarks)
			{
				framework::PointI index;
				SplitPointStr(config->GetStr("bookmarks", bookid.c_str(), "0,0"), index.X, index.Y);
				AddBookmark(bookid.c_str(), index);
			}
		}

		// add animation to spritesheet
		void SpriteSheet::AddAnimation(SpriteAnimationPtr animation) 
		{ 
			_animations[animation->Identifier()] = animation;
		}

		// create animation from config
		SpriteAnimation::SpriteAnimation(const char* identifier, assets::ConfigAsset config) : _identifier(identifier)
		{
			// get section name
			std::string section = "anim_" + _identifier;

			// load general config from config file
			Repeats = config->GetBool(section.c_str(), "repeats", false);
			int steps_count = config->GetInt(section.c_str(), "steps_count", 0);

			// sanity check
			if (steps_count <= 0)
			{
				throw framework::AssetLoadError(("Invalid spritesheet file! Animation '" + _identifier + "' either missing its section '" + section + "' or have invalid steps_count value.").c_str());
			}

			// load animation steps
			for (int i = 0; i < steps_count; ++i)
			{
				//  step name prefix
				std::string step_prefix = "step_" + std::to_string(i);

				// load duration and index
				float duration = config->GetFloat(section.c_str(), (step_prefix + "_duration").c_str(), 0.1f);
				std::string indexStr(config->GetStr(section.c_str(), (step_prefix + "_source").c_str(), "0,0"));
				int x, y;
				SplitPointStr(indexStr, x, y);

				// add step
				SpriteAnimationStep step;
				step.Duration = duration;
				step.Index.Set(x, y);
				_steps.push_back(step);
			}
		}

		// set sprite from sprite sheet
		void SpriteSheet::SetSprite(Sprite& sprite, framework::PointI indexInSheet, float sizeFactor) const
		{
			// get size in texture
			framework::PointI sizeInTexture(sprite.Image->Width() / SpritesCount.X, sprite.Image->Height() / SpritesCount.Y);

			// set source rect
			sprite.SourceRect.Set(indexInSheet.X * sizeInTexture.X, indexInSheet.Y * sizeInTexture.Y, sizeInTexture.X, sizeInTexture.Y);

			// size size 
			if (sizeFactor != 0.0f)
			{
				sprite.Size.Set((int)(sizeInTexture.X * sizeFactor), (int)(sizeInTexture.Y * sizeFactor));
			}
		}
		
		// set a sprite's source rectangle from index in spritesheet.
		void SpriteSheet::SetSprite(Sprite& sprite, const char* bookmarkId, float sizeFactor) const
		{
			framework::PointI index = _bookmarks.at(std::string(bookmarkId));
			SetSprite(sprite, index, sizeFactor);
		}

		// animate sprite
		void SpriteAnimation::Animate(double& progress, double deltaTime, framework::PointI& outIndex, int* currStep, bool* didFinish) const
		{
			// get previous step
			int prevStep = (int)floor(progress);

			// special case - if prev step is bigger than max, it means 3 things:
			//	1. we're not in repeat mode (otherwise we would have reset back to 0 by now).
			//	2. we already finished animation.
			if (prevStep >= _steps.size()) {
				prevStep = (int)_steps.size() - 1;
				if (currStep) {
					*currStep = prevStep;
				}
				if (didFinish) {
					*didFinish = true;
				}
				outIndex = _steps[prevStep].Index;
				return;
			}

			// set as didn't finish
			if (didFinish) {
				*didFinish = false;
			}

			// increase progress and get current step
			progress += deltaTime / _steps[prevStep].Duration;
			int newStep = (int)floor(progress);

			// did step change?
			if (prevStep != newStep)
			{
				// did finish animation?
				if (newStep >= _steps.size()) {

					// set new step to either start of animation, or last step
					newStep = Repeats ? 0 : (int)_steps.size() - 1;
					if (newStep == 0) { progress = 0.0; }

					// set as finished
					if (didFinish) {
						*didFinish = true;
					}
				}
			}

			// set curr step out param
			if (currStep) {
				*currStep = newStep;
			}

			// lastly, set out index
			outIndex.Copy(_steps[newStep].Index);
		}

		// animate sprite
		void SpriteSheet::Animate(Sprite& sprite, const char* animationId, double& progress, double deltaTime, int* currStep, bool* didFinish, float sizeFactor) const
		{
			// get animation
			SpriteAnimationPtr animation = _animations.at(std::move(animationId));

			// animate
			framework::PointI index;
			animation->Animate(progress, deltaTime, index, currStep, didFinish);
		
			// set sprite source rect
			SetSprite(sprite, index, sizeFactor);
		}

		// get animation by identifier
		SpriteAnimationPtr SpriteSheet::GetAnimation(const char* identifier)
		{
			return (_animations)[identifier];
		}

		// add a bookmark to spritesheet.
		void SpriteSheet::AddBookmark(const char* bookmarkId, framework::PointI spriteIndex)
		{
			_bookmarks[bookmarkId] = spriteIndex;
		}

		// get bookmark value
		framework::PointI SpriteSheet::GetBookmark(const char* bookmarkId) const
		{
			return _bookmarks.at(bookmarkId);
		}
	}
}