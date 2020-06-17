/*****************************************************************//**
 * \file   SpriteSheet.h
 * \brief  Define a spritesheet with animation and specific steps.
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "Defs.h"
#include "../Assets/Types/Image.h"
#include "../Assets/Defs.h"
#include "../Framework/Point.h"
#include "../Framework/Rectangle.h"
#include "Sprite.h"
#include <vector>
#include <unordered_map>
#include <memory>

#pragma warning ( push )
#pragma warning ( disable: 4251 ) // "..needs to have dll-interface to be used by clients..." it's ok in this case because its private.


namespace bon
{
	namespace gfx
	{
		/**
		 * A single sprite animation step.
		 */
		struct BON_DLLEXPORT SpriteAnimationStep
		{
		public:
			// For how long, in seconds, to display this step.
			float Duration = 1.0f;

			// The index of the sprite in the spritesheet during this animation step.
			framework::PointI Index;
		};

		/**
		 * SpriteSheet animation.
		 */
		class BON_DLLEXPORT SpriteAnimation
		{
		private:
			// animation identifier
			std::string _identifier;

			// animation steps
			std::vector<SpriteAnimationStep> _steps;

		public:

			/**
			 * Should this animation repeat when done?
			 */
			bool Repeats = false;

			/**
			 * Create the animation.
			 * 
			 * \param identifier Animation unique identifier.
			 */
			SpriteAnimation(const char* identifier) : _identifier(identifier) {}

			/**
			 * Create the animation from config file.
			 *
			 * \param identifier Animation unique identifier.
			 * \param config Configuration file to load animation from.
			 *				* config must contain a section called 'anim_xxx', where xxx is this animation's unique identifier.
			 *				* under this section, we should have the following keys:
			 *				* - repeats = true / false - does this animation loops, or remain stuck on last step after done?
			 *				* - steps_count = how many steps we have in this animation.
			 *				* - setp_x_duration [x is step index] = duration, in seconds, of this animation step.
			 *				* - setp_x_source [x is step index] = index in spritesheet file, format is: "x,y".
			 *	For more info, check out demo_spritesheet.ini in test assets folder.
			 */
			SpriteAnimation(const char* identifier, assets::ConfigAsset config);

			/**
			 * Animate a sprite using this animation.
			 * 
			 * \param progress Animation total progress. You need to keep this value unchanged between Animate() calls, and zero it when switching animation.
			 * \param deltaTime Current animation step's delta time, ie how much to advance progress.
			 * \param outIndex Will contain sprite index in spritesheet, corresponding to the animation steps we're in.
			 * \param currStep If provided, will contain step index when done.
			 * \param didFinish If provided, will contain true if animation finished.
			 *					Note: if Repeats = true, will be set to true every time animation resets, for a single frame.
			 *						  if Repeats = false, will remain 'true' once animation finished its final step.
			 */
			void Animate(double& progress, double deltaTime, framework::PointI& outIndex, int* currStep = nullptr, bool* didFinish = nullptr) const;

			/**
			 * Get identifier.
			 * 
			 * \return Animation identifier.
			 */
			const char* Identifier() const { return _identifier.c_str(); }

			/**
			 * Add step to animation.
			 * 
			 * \param step Animation step to add.
			 */
			void AddStep(SpriteAnimationStep step) { _steps.push_back(step); }

			/**
			 * Get animation steps count.
			 */
			int StepsCount() const { return (int)_steps.size(); }
		};

		// Sprite animation pointer type
		typedef std::shared_ptr<SpriteAnimation> SpriteAnimationPtr;

		/**
		 * A sprite sheet with animations.
		 * You can load sprite sheets from config files.
		 */
		class BON_DLLEXPORT SpriteSheet
		{
		private:
			// spritesheet animations
			std::unordered_map<std::string, SpriteAnimationPtr> _animations;

			// spritesheet bookmarks
			std::unordered_map<std::string, framework::PointI> _bookmarks;

		public:
			/**
			 * How many sprites we have on X and Y axis inside the spritesheet.
			 */
			framework::PointI SpritesCount;

			/**
			 * Create empty spritesheet.
			 */
			SpriteSheet() {}

			/**
			 * Create the spritesheet from config file.
			 *
			 * \param config Configuration file to load spritesheet from. See comment on 'LoadFromConfig' for more info.
			 */
			SpriteSheet(assets::ConfigAsset config);

			/**
			 * Create the spritesheet from config file.
			 *
			 * \param config Configuration file to load spritesheet from.
			 *				* config must contain the following section:
			 *				*	[general]
			 *				*		- sprites_count = how many sprites there are in this spritesheet, format is: "x,y".
			 *				*		- animations = list of comma-separated animations found in this spritesheet config. 
			 *				*						for every animation listed here, you need to also include a section with animation data.
			 *				*						check out 'SpriteAnimation' constructor for more info.
			 *				*
			 *				*	[bookmarks]
			 *				*		- optional, contains a list of values where every key is a bookmark identifier and value is sprite index "x,y".
			 *				*			later, you can use this to set sprites from spritesheet by names. for example: sheet.SetSprite(sprite, "item_sword");
			 *	For more info, check out demo_spritesheet.ini in test assets folder.
			 */
			void LoadFromConfig(assets::ConfigAsset config);

			/**
			 * Set a sprite's source rectangle from index in spritesheet.
			 * 
			 * \param sprite Sprite to set.
			 * \param indexInSheet Index in spritesheet.
			 * \param sizeFactor Set the size of the sprite to be tilesheet sprite's size multiplied by this value.
			 *						If set to 0, will not change sprite size.
			 */
			void SetSprite(Sprite& sprite, framework::PointI indexInSheet, float sizeFactor = 1.0f) const;

			/**
			 * Set a sprite's source rectangle from index in spritesheet.
			 *
			 * \param sprite Sprite to set.
			 * \param bookmarkId Bookmark identifier to set sprite from.
			 * \param sizeFactor Set the size of the sprite to be tilesheet sprite's size multiplied by this value.
			 *						If set to 0, will not change sprite size.
			 */
			void SetSprite(Sprite& sprite, const char* bookmarkId, float sizeFactor = 1.0f) const;

			/**
			 * Animate a sprite using this animation.
			 *
			 * \param sprite Sprite object to animate.
			 * \param animationId Animation identifier.
			 * \param progress Animation total progress. You need to keep this value unchanged between Animate() calls, and zero it when switching animation.
			 * \param deltaTime Current animation step's delta time, ie how much to advance progress.
			 * \param currStep If provided, will contain step index when done.
			 * \param didFinish If provided, will contain true if animation finished.
			 *					Note: if Repeats = true, will be set to true every time animation resets, for a single frame.
			 *						  if Repeats = false, will remain 'true' once animation finished its final step.
			 * \param sizeFactor Set the size of the sprite to be tilesheet sprite's size multiplied by this value.
			 *						If set to 0, will not change sprite size.
			 */
			void Animate(Sprite& sprite, const char* animationId, double& progress, double deltaTime, int* currStep = nullptr, bool* didFinish = nullptr, float sizeFactor = 1.0f) const;

			/**
			 * Get animation from identifier.
			 * 
			 * \param identifier Animation identifier.
			 * \return Animation pointer.
			 */
			SpriteAnimationPtr GetAnimation(const char* identifier);

			/**
			 * Add animation to spritesheet.
			 * 
			 * \param animation Animation instance.
			 */
			void AddAnimation(SpriteAnimationPtr animation);
	
			/**
			 * Add a bookmark to spritesheet.
			 * 
			 * \param bookmarkId Bookmark unique id.
			 * \param spriteIndex Sprite index in spritesheet.
			 */
			void AddBookmark(const char* bookmarkId, framework::PointI spriteIndex);

			/**
			 * Get bookmark index value.
			 * 
			 * \param bookmarkId Bookmark id to get.
			 * \return Sprite index in spritesheet from bookmark.
			 */
			framework::PointI GetBookmark(const char* bookmarkId) const;

			/**
			 * Get if animation id exists.
			 * 
			 * \param animationId Animation id to check.
			 * \return True if animation exists.
			 */
			bool ContainsAnimation(const char* animationId) const;

			/**
			 * Get if bookmark id exists.
			 *
			 * \param bookmarkId Bookmark id to check.
			 * \return True if bookmark exists.
			 */
			bool ContainsBookmark(const char* bookmarkId) const;
		};
	}
}

#pragma warning (pop)