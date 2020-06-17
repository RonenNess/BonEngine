#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"
#include <list>
#include <functional>
#include <memory>


namespace demo11_custom_manager
{
	// sprite pointer type
	typedef std::shared_ptr<bon::Sprite> SpritePtr;

	// predicate to remove empty sprites
	bool emptySprite(SpritePtr value)
	{
		return value->Size.X == 0;
	}

	/**
	 * A custom manager to detect collision between sprites.
	 * Note: implemented in a very naive way just for the demo.
	 */
	class CollisionManager : public bon::IManager
	{
	private:
		// collision detection handler
		std::function<void(SpritePtr, SpritePtr)> _handler = nullptr;

		// shapes to test collision
		std::list<SpritePtr> _objects;

	public:

		/**
		 * Get manager identifier.
		 */
		virtual const char* _GetId() const { return "collision"; }

		/**
		 * Set the collision detection handler.
		 */
		void SetCollisionHandler(std::function<void(SpritePtr, SpritePtr)> handler)
		{
			_handler = handler;
		}

		/**
		 * Add an object to the collision manager.
		 */
		void AddObject(SpritePtr object)
		{
			_objects.push_back(object);
		}

		/**
		 * Removes an object from the collision manager.
		 */
		void DeleteObject(SpritePtr object)
		{
			// removing objects don't remove them immediately, but only mark them for removal by setting size to 0.
			object->Size.Set(0, 0);
		}

		/**
		 * Called every time to update manager, aka test collision.
		 */
		virtual void _Update(double deltaTime) override
		{
			// remove all marked objects
			_objects.remove_if(emptySprite);

			// if there's no collision manager, skip
			if (!_handler) { return; }

			// iterate sprite for every other sprite
			for (auto a : _objects)
			{
				for (auto b : _objects)
				{
					// skip self
					if (a == b) { continue; }

					// get distance
					float distance = a->Position.DistanceTo(b->Position);

					// if distance < both objects radius, they collide
					if (distance < a->Size.X / 2 + b->Size.X / 2) {
						_handler(a, b);
					}
				}
			}
		}

		/**
		 * Get all objects in manager.
		 */
		const std::list<SpritePtr>& Objects() const
		{
			return _objects;
		}
	};

	/**
	 * Custom manager scene.
	 */
	class CustomManagerScene : public bon::engine::Scene
	{
	private:
		// cached collision manager instance
		CollisionManager* _collisionManager = nullptr;

		// default font
		bon::FontAsset _font;

		// cursor image
		bon::ImageAsset _cursorImage;

		// sprites to draw
		bon::ImageAsset _spriteImage;
		bon::ImageAsset _playerSpriteImage;

		// sound to play when collecting bonus
		bon::SoundAsset _sound;

		// player pointer
		SpritePtr _player;

	public:
		// on scene load
		virtual void _Load() override
		{
			if (IsFirstScene())
				Game().LoadConfig("../TestAssets/config.ini");
			_collisionManager = (CollisionManager*)GetManager("collision");
		}

		// on scene start
		virtual void _Start() override
		{
			// load assets
			_spriteImage = Assets().LoadImage("../TestAssets/gfx/tower.png");
			_playerSpriteImage = Assets().LoadImage("../TestAssets/gfx/tower_s.png");
			_sound = Assets().LoadSound("../TestAssets/sfx/phaserUp1.mp3");
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf");

			// create random sprites
			srand(0);
			for (int i = 0; i < 50; ++i)
			{
				bon::Sprite* sprite = new bon::Sprite;
				sprite->Image = _spriteImage;
				sprite->Origin.Set(0.5f, 0.5f);
				sprite->Color = bon::Color::Random();
				sprite->Position.Set((float)(rand() % 800), (float)(rand() % 600));
				int size = rand() % 32 + 32;
				sprite->Size.Set(size, size);
				_collisionManager->AddObject(std::shared_ptr<bon::Sprite>(sprite));
			}

			// set player 
			bon::Sprite* playerSprite = new bon::Sprite;
			playerSprite->Image = _playerSpriteImage;
			playerSprite->Origin.Set(0.5f, 0.5f);
			playerSprite->Position.Set(400, 300);
			int size = 42;
			playerSprite->Size.Set(size, size);
			_player = std::shared_ptr<bon::Sprite>(playerSprite);
			_collisionManager->AddObject(_player);

			// register collision handler
			_collisionManager->SetCollisionHandler([this, playerSprite](SpritePtr a, SpritePtr b) {
				
				// check if need to remove one of the sides
				bool playSound = false;
				if (&*a == playerSprite) {
					_collisionManager->DeleteObject(b);
					playSound = true;
				}
				else if (&*b == playerSprite) {
					_collisionManager->DeleteObject(a);
					playSound = true;
				}

				// play sound
				if (playSound && !_sound->IsPlaying()) {
					Sfx().PlaySound(_sound);
				}
			});
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			if (Input().Down("exit")) { Game().Exit(); }

			// move player
			float moveSpeed = (float)(deltaTime * 100);
			bool walking = false;
			if (Input().Down("left")) { _player->Position.X -= moveSpeed; }
			if (Input().Down("right")) { _player->Position.X += moveSpeed; }
			if (Input().Down("up")) { _player->Position.Y -= moveSpeed; }
			if (Input().Down("down")) { _player->Position.Y += moveSpeed; }
			if (Input().Down("exit")) { Game().Exit(); }
		}

		// drawing
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color::Cornflower);

			// draw example text and fps
			Gfx().DrawText(_font, "Demo #11: Custom Managers!", bon::PointF(100, 100));
			Gfx().DrawText(_font, "This demo illustrates custom managers in BonEngine.\n\
In this case, we register a collision manager. Use arrows / WASD to move.\n\
Hit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 20);
			Gfx().DrawText(_font, (std::string("FPS: ") + std::to_string(Diagnostics().FpsCount())).c_str(), bon::PointF(0, 0), &bon::Color(1, 1, 1, 1), 18);

			// draw sprites
			for (auto sprite : _collisionManager->Objects()) {
				if (sprite->Size.X == 0) { continue; }
				Gfx().DrawSprite(*sprite);
			}
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		// register custom collision manager
		CollisionManager collisionManager;
		bon::_GetEngine().RegisterCustomManager(&collisionManager);

		// start demo
		auto scene = CustomManagerScene();
		bon::Start(scene);
	}

}