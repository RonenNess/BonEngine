#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"
#include "utils/Perlin.h"
#include <algorithm>

namespace demo13_a_walk_in_the_forest
{
	/**
	 * Game scene for the demo game
	 */
	class WalkInTheForestScene : public bon::engine::Scene
	{
	private:

		// tileset
		bon::ImageAsset _tileset;

		// player sprite and spritesheet
		bon::Sprite _player;
		bon::gfx::SpriteSheet _playerSheet;
		double _playerAnimationProgress = 0.0;

		// sound effects
		bon::MusicAsset _music;
		bon::SoundAsset _stepsSound[2];
		bon::SoundAsset _forestSound;

		// camera position
		bon::PointF _camera;

		// font
		bon::FontAsset _font;

		// after seeing ghost, time until game "crashes".
		double _timeToFakeCrash = 12.0;
		
		// did we meet ghost yet?
		bool _didSeeGhost = false;

		// should we show help text?
		bool _showHelpText = true;

		// map size, in tiles
		const int MapSize = 150;

		// ghost position
		bon::PointI GhostPosition = bon::PointI(118, 90);
		
		// tile types
		enum class TileTypes
		{
			Dirt = 0,
			Grass = 1,
			ThickGrass = 2,
			Water = 3
		};

		// object types
		enum class ObjectTypes
		{
			None = 0,
			TreeSmall = 1,
			TreeLarge = 2,
			Ghost = 3
		};

		// store level data
		struct LevelData
		{
			// offset in texture of every tile (layer 0 = base, layer 1 = sides merges, layer 2 = corner merges)
			bon::PointI SpritesOffset[150][150][3];

			// current tile type
			TileTypes TileTypes[150][150];

			// is blocking tile
			bool IsBlocking[150][150];

			// objects
			ObjectTypes Objects[150][150];
		};
		LevelData* _levelData = nullptr;

		// tile sizes consts
		int TileSize = 128;
		int TileSourceSize = 16;

		// player movement speed
		float PlayerSpeed = 335.0f;

	public:
		// on scene load
		virtual void _Load() override
		{
			// load configuration and set key to toggle text
			Game().LoadConfig("../TestAssets/config_fullscreen_windowed.ini");
			Input().SetKeyBind(bon::KeyCodes::KeySpace, "toggle_text");

			// create level data
			_levelData = new LevelData();

			
		}

		// on scene unload
		virtual void _Unload() override
		{
			delete _levelData;
		}

		// on scene start
		virtual void _Start() override
		{
			// load tileset
			_tileset = Assets().LoadImage("../TestAssets/gfx/forest_tilemap.png");

			// load player sheet
			_playerSheet.LoadFromConfig(Assets().LoadConfig("../TestAssets/gfx/player_spritesheet.ini"));
			_player.Image = Assets().LoadImage("../TestAssets/gfx/player.png");
			_player.Size.Set(256, 256);
			_player.Origin.Set(0.5f, 0.9f);
			_player.SourceRect.Set(0, 0, 32, 32);
			_player.Position.X = _player.Position.Y = 3500;

			// load music
			_music = Assets().LoadMusic("../TestAssets/sfx/old city theme.ogg");
			_stepsSound[0] = Assets().LoadSound("../TestAssets/sfx/stepdirt_1.wav");
			_stepsSound[1] = Assets().LoadSound("../TestAssets/sfx/stepdirt_2.wav");
			_forestSound = Assets().LoadSound("../TestAssets/sfx/Forest_Ambience.mp3");

			// load font
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf");

			// set master volumes
			Sfx().SetMasterVolume(100, 100);

			// start playing music
			Sfx().PlayMusic(_music);
			Sfx().PlaySound(_forestSound, 100, -1);

			// init level
			CreateLevel();
		}

		// create the level
		void CreateLevel()
		{
			// constant random seed
			srand(0);

			// create random map using perlin noise
			for (int i = 0; i < MapSize; ++i) {
				for (int j = 0; j < MapSize; ++j) {

					// randomize current tile type using noise
					float noise = (float)ValueNoise_2D(i, j) * 4.5f;
					TileTypes tiletype = TileTypes::Dirt;
					if (noise > 0.25f && noise < 0.85f) { tiletype = TileTypes::Grass; }
					else if (noise >= 0.85f && noise < 0.95f) { tiletype = TileTypes::ThickGrass; }
					else if (noise >= 0.95f) { tiletype = TileTypes::Water; }
					_levelData->TileTypes[i][j] = tiletype;

					// set blocking
					_levelData->IsBlocking[i][j] = (tiletype == TileTypes::Water);

					// set sprite offset based on type
					switch (tiletype)
					{
					// dirt (starts at 0,0, and have randomness)
					case TileTypes::Dirt:
						_levelData->SpritesOffset[i][j][0] = (rand() % 10) >= 9 ?
							bon::PointI((rand() % 2) * TileSourceSize, (rand() % 2) * TileSourceSize) :
							bon::PointI(0, 0);
						break;

					// grass (starts with offset of 2 and have randomness)
					case TileTypes::Grass:
						_levelData->SpritesOffset[i][j][0] = (rand() % 10) >= 9 ?
							bon::PointI((2 * TileSourceSize) + (rand() % 2) * TileSourceSize, (rand() % 2) * TileSourceSize) :
							bon::PointI((2 * TileSourceSize), 0);
						break;

					// thick grass (no randomness)
					case TileTypes::ThickGrass:
						_levelData->SpritesOffset[i][j][0] = bon::PointI(9 * TileSourceSize, 1 * TileSourceSize);
						break;

					// water (no randomness)
					case TileTypes::Water:
						_levelData->SpritesOffset[i][j][0] = bon::PointI(9 * TileSourceSize, 4 * TileSourceSize);
						break;
					}
				}
			}

			// merge parts offset in texture
			static bon::PointI mergePartsOffset[4] = {
				bon::PointI(0, 0) * TileSourceSize,
				bon::PointI(4, 0) * TileSourceSize,
				bon::PointI(8, 0) * TileSourceSize,
				bon::PointI(6, 4) * TileSourceSize
			};

			// calculate merging parts
			for (int i = 0; i < MapSize; ++i) {
				for (int j = 0; j < MapSize; ++j) {

					// get self type
					auto selfType = _levelData->TileTypes[i][j];
					bool upDiff = j > 0 && selfType > _levelData->TileTypes[i][j - 1];
					bool downDiff = j < MapSize - 1 && selfType > _levelData->TileTypes[i][j + 1];
					bool leftDiff = i > 0 && selfType > _levelData->TileTypes[i - 1][j];
					bool rightDiff = i < MapSize - 1 && selfType > _levelData->TileTypes[i + 1][j];
					bool upLeftDiff = j > 0 && i > 0 && selfType > _levelData->TileTypes[i - 1][j - 1];
					bool upRightDiff = j > 0 && i < MapSize - 1 && selfType > _levelData->TileTypes[i + 1][j - 1];
					bool downLeftDiff = j < MapSize - 1 && i > 0 && selfType > _levelData->TileTypes[i - 1][j + 1];
					bool downRightDiff = j < MapSize - 1 && i < MapSize - 1 && selfType > _levelData->TileTypes[i + 1][j + 1];
					bool isBlocking = (selfType == TileTypes::Water);

					// merge up
					if (upDiff && _levelData->SpritesOffset[i][j - 1][1].IsZero()) {
						_levelData->SpritesOffset[i][j - 1][1] = mergePartsOffset[(int)selfType] + bon::PointI(TileSourceSize, 0);
						if (isBlocking) { _levelData->IsBlocking[i][j - 1] = true; }
					}
					// merge down
					if (downDiff && _levelData->SpritesOffset[i][j + 1][1].IsZero()) {
						_levelData->SpritesOffset[i][j + 1][1] = mergePartsOffset[(int)selfType] + bon::PointI(TileSourceSize, TileSourceSize * 2);
						if (isBlocking) { _levelData->IsBlocking[i][j + 1] = true; }
					}
					// merge left
					if (leftDiff && _levelData->SpritesOffset[i - 1][j][1].IsZero()) {
						_levelData->SpritesOffset[i - 1][j][1] = mergePartsOffset[(int)selfType] + bon::PointI(0, TileSourceSize);
						if (isBlocking) { _levelData->IsBlocking[i - 1][j] = true; }
					}
					// merge right
					if (rightDiff && _levelData->SpritesOffset[i + 1][j][1].IsZero()) {
						_levelData->SpritesOffset[i + 1][j][1] = mergePartsOffset[(int)selfType] + bon::PointI(TileSourceSize * 2, TileSourceSize);
						if (isBlocking) { _levelData->IsBlocking[i + 1][j] = true; }
					}

					// merge up left
					if (upLeftDiff) {
						// external corner
						if (leftDiff && upDiff) {
							if (_levelData->SpritesOffset[i - 1][j - 1][1].IsZero()) { 
								_levelData->SpritesOffset[i - 1][j - 1][1] = mergePartsOffset[(int)selfType]; 
								if (isBlocking) { _levelData->IsBlocking[i - 1][j - 1] = true; }
							}
						}
						// internal corner
						else if(!leftDiff && !upDiff) {
							_levelData->SpritesOffset[i - 1][j - 1][2] = mergePartsOffset[(int)selfType] + bon::PointI(TileSourceSize * 2, TileSourceSize * 3);
							if (isBlocking) { _levelData->IsBlocking[i - 1][j - 1] = true; }
						}
					}
					// merge up right
					if (upRightDiff) {
						// external corner
						if (rightDiff && upDiff) {
							if (_levelData->SpritesOffset[i + 1][j - 1][1].IsZero()) {
								_levelData->SpritesOffset[i + 1][j - 1][1] = mergePartsOffset[(int)selfType] + bon::PointI(TileSourceSize * 2, 0);
								if (isBlocking) { _levelData->IsBlocking[i + 1][j - 1] = true; }
							}
						}
						// internal corner
						else if (!rightDiff && !upDiff) {
							_levelData->SpritesOffset[i + 1][j - 1][2] = mergePartsOffset[(int)selfType] + bon::PointI(TileSourceSize * 3, TileSourceSize * 3);
							if (isBlocking) { _levelData->IsBlocking[i + 1][j - 1] = true; }
						}
					}
					// merge down left
					if (downLeftDiff) {
						// external corner
						if (leftDiff && downDiff) {
							if (_levelData->SpritesOffset[i - 1][j + 1][1].IsZero()) {
								_levelData->SpritesOffset[i - 1][j + 1][1] = mergePartsOffset[(int)selfType] + bon::PointI(0, TileSourceSize * 2);
								if (isBlocking) { _levelData->IsBlocking[i - 1][j + 1] = true; }
							}
						}
						// internal corner
						else if (!leftDiff && !downDiff) {
							_levelData->SpritesOffset[i - 1][j + 1][2] = mergePartsOffset[(int)selfType] + bon::PointI(0, TileSourceSize * 3);
							if (isBlocking) { _levelData->IsBlocking[i - 1][j + 1] = true; }
						}
					}
					// merge down right
					if (downRightDiff) {
						// external corner
						if (rightDiff && downDiff) {
							if (_levelData->SpritesOffset[i + 1][j + 1][1].IsZero()) {
								_levelData->SpritesOffset[i + 1][j + 1][1] = mergePartsOffset[(int)selfType] + bon::PointI(TileSourceSize * 2, TileSourceSize * 2);
								if (isBlocking) { _levelData->IsBlocking[i + 1][j + 1] = true; }
							}
						}
						// internal corner
						else if (!rightDiff && !downDiff) {
							_levelData->SpritesOffset[i + 1][j + 1][2] = mergePartsOffset[(int)selfType] + bon::PointI(TileSourceSize, TileSourceSize * 3);
							if (isBlocking) { _levelData->IsBlocking[i + 1][j + 1] = true; }
						}
					}
				}
			}

			// generate random objects
			for (int i = 0; i < MapSize; ++i) {
				for (int j = 0; j < MapSize; ++j) {

					_levelData->Objects[i][j] = ObjectTypes::None;

					// can only create objects if tile and tile next to it are non-blocking
					if (_levelData->IsBlocking[i][j] || (i >= MapSize - 1) || _levelData->IsBlocking[i + 1][j]) {
						continue;
					}

					// get current random val
					int randVal = rand() % 20;

					// small tree
					if (randVal == 1) {
						_levelData->Objects[i][j] = ObjectTypes::TreeSmall;
						_levelData->IsBlocking[i+1][j] = _levelData->IsBlocking[i][j] = true;
						continue;
					}

					// large tree
					if (randVal == 2) {
						_levelData->Objects[i][j] = ObjectTypes::TreeLarge;
						_levelData->IsBlocking[i + 1][j] = _levelData->IsBlocking[i][j] = true;
						continue;
					}
				}
			}

			// put ghost
			_levelData->Objects[GhostPosition.X][GhostPosition.Y] = ObjectTypes::Ghost;
		}

		// get if a given position is a blocking tile
		bool IsBlocking(bon::PointF position)
		{
			// get tile index
			int i = (int)(position.X / TileSize);
			int j = (int)(position.Y / TileSize);

			// out of level range? block
			if (i <= 0 || j <= 0 || i >= MapSize || j >= MapSize) {
				return true;
			}

			// get if blocking tile
			return  _levelData->IsBlocking[i][j];
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			static bool flip = false;

			// count time until game "crashes"
			if (_didSeeGhost) {
				if (_timeToFakeCrash > 0.0) {
					_timeToFakeCrash -= deltaTime;
					if (_timeToFakeCrash <= 0.0) {
						Sfx().StopMusic();
						Sfx().StopChannel(bon::AllChannels);
					}
				}
				else
				{
					if (Input().Down("exit")) { Game().Exit(); }
					return;
				}
			}

			// move player
			float moveSpeed = (float)(deltaTime * PlayerSpeed);
			bool walking = false;
			if (Input().Down("exit")) { Game().Exit(); }
			if (Input().Down("left") && !IsBlocking(_player.Position + bon::PointF(-moveSpeed * 2, 0))) { _player.Position.X -= moveSpeed; walking = true; flip = true; }
			if (Input().Down("right") && !IsBlocking(_player.Position + bon::PointF(moveSpeed * 2, 0))) { _player.Position.X += moveSpeed; walking = true; flip = false; }
			if (Input().Down("up") && !IsBlocking(_player.Position + bon::PointF(0, -moveSpeed * 2))) { _player.Position.Y -= moveSpeed; walking = true; }
			if (Input().Down("down") && !IsBlocking(_player.Position + bon::PointF(0, moveSpeed * 2))) { _player.Position.Y += moveSpeed; walking = true; }

			// toggle text
			if (Input().PressedNow("toggle_text")) { _showHelpText = !_showHelpText; }

			// do walking animation / sound
			if (walking)
			{
				// play sound effect (but only if finished playing previous step)
				if (!_stepsSound[0]->IsPlaying() && !_stepsSound[1]->IsPlaying()) {
					Sfx().PlaySound(_stepsSound[rand() % 2], 30, 0, 0.8f + (float)(rand() % 40) / 100.0f);
				}

				// animate player walking
				_playerSheet.Animate(_player, "walk", _playerAnimationProgress, deltaTime, nullptr, nullptr, 0.0f);
			}
			// reset player animation to standing
			else
			{
				_playerSheet.SetSprite(_player, "stand", 0.0f);
				_playerAnimationProgress = 0.0;
			}

			// flip player sprite
			_player.Size.X = abs(_player.Size.X) * (flip ? -1 : 1);

			// update camera position
			auto windowSize = Gfx().WindowSize();
			_camera.Set((_player.Position.X - windowSize.X / 2.0f), (_player.Position.Y - windowSize.Y / 2.0f) - 32.0f);
			_camera.Clamp(0.0f, (MapSize * TileSize) - (float)windowSize.X, 0.0f, (MapSize * TileSize) - (float)windowSize.Y);
		}

		// drawing
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color::Black);

			// if game "crashed"
			if (_timeToFakeCrash <= 0.0)
			{
				static int count = 1;
				int screenHeight = Gfx().WindowSize().Y;
				for (int i = 0; i < count; ++i) {
					float ypos = (float)(-7 + i * 42);
					if (ypos > screenHeight - 120) {
						if (ypos > screenHeight - 60) {
							Gfx().DrawText(_font, "it's here. ", bon::PointF(100.0f, ypos), &bon::Color(1, 0, 0, 1), 26);
						}
						else {
							Gfx().DrawText(_font, "she's coming. she's coming. she's coming. she's coming. she's coming. she's coming. ", bon::PointF(100.0f, ypos), &bon::Color(1, 0, 0, 1), 26);
						}
					}
					else {
						Gfx().DrawText(_font, "ACCESS VIOLATION at address 0xdead00df02. Debug symbols not found.", bon::PointF(100.0f, ypos), &bon::Color(1, 0, 0, 1), 26);
					}
				}
				if (rand() % 5 == 0) 
				{ 
					count++; 
					if (count * 42 > screenHeight + 550) {
						Game().Exit();
					}
				}
				return;
			}

			// calc which part of the map to draw
			auto windowSize = Gfx().WindowSize();
			bon::PointI startIndex((int)(_camera.X / TileSize), (int)(_camera.Y / TileSize));
			bon::PointI endIndex(startIndex.X + windowSize.X / TileSize + 1, startIndex.Y + windowSize.Y / TileSize + 2);
			startIndex.Clamp(0, MapSize);
			endIndex.Clamp(0, MapSize);

			// draw tiles bottom layer
			bon::RectangleI sourceRect(0, 0, TileSourceSize, TileSourceSize);
			bon::PointI TileSizePoint(TileSize, TileSize);
			for (int i = startIndex.X; i < endIndex.X; ++i) {
				for (int j = startIndex.Y; j < endIndex.Y; ++j) {

					// get source rect
					sourceRect.X =  _levelData->SpritesOffset[i][j][0].X;
					sourceRect.Y = _levelData->SpritesOffset[i][j][0].Y;

					// animate water
					if (_levelData->TileTypes[i][j] == TileTypes::Water) {
						sourceRect.Y += (TileSourceSize * (((int)Game().ElapsedTime() + i * 71 + (j * 71) % 5) % 3));
					}

					// draw tile
					bon::PointF position(i * TileSize - _camera.X, j * TileSize - _camera.Y);
					Gfx().DrawImage(_tileset, position, &TileSizePoint, bon::BlendModes::AlphaBlend, &sourceRect, nullptr, 0.0f, nullptr);
				}
			}

			// draw tile merging layer
			for (int i = startIndex.X; i < endIndex.X; ++i) {
				for (int j = startIndex.Y; j < endIndex.Y; ++j) {
					for (int l = 1; l <= 2; ++l) {
						if (_levelData->SpritesOffset[i][j][l].IsZero()) { continue; }
						
						bon::PointF position(i * TileSize - _camera.X, j * TileSize - _camera.Y);
						sourceRect.X = _levelData->SpritesOffset[i][j][l].X;
						sourceRect.Y = _levelData->SpritesOffset[i][j][l].Y;
						Gfx().DrawImage(_tileset, position, &TileSizePoint, bon::BlendModes::AlphaBlend, &sourceRect, nullptr, 0.0f, nullptr);
					}
				}
			}

			// get player tile index
			int playerTileY = std::min((int)(_player.Position.Y + (TileSize / 2)) / TileSize, (int)MapSize - 1);

			// small tree properties
			static bon::PointI SmallTreeSize(2 * TileSize, 3 * TileSize);
			static bon::RectangleI SmallTreeSource(0, 2 * TileSourceSize, 2 * TileSourceSize, 3 * TileSourceSize);
			static bon::PointF SmallTreeOrigin(0.0f, 0.7f);

			// large tree properties
			static bon::PointI LargeTreeSize(4 * TileSize, 4 * TileSize);
			static bon::RectangleI LargeTreeSource(2 * TileSourceSize, 4 * TileSourceSize, 4 * TileSourceSize, 4 * TileSourceSize);
			static bon::PointF LargeTreeOrigin(0.25f, 0.7f);

			// ghost properties
			static bon::PointI GhostSize(TileSize, 2 * TileSize);
			static bon::RectangleI GhostSource(0, 6 * TileSourceSize, 1 * TileSourceSize, 2 * TileSourceSize);
			static bon::PointF GhostOrigin(0.5f, 0.9f);

			// once we see the ghost, level begins to vanish
			if (_didSeeGhost)
			{
				for (int x = 0; x < 12; ++x) {
					
					// set random broken parts
					int i = rand() % MapSize;
					int j = rand() % MapSize;
					_levelData->SpritesOffset[i][j][0].Set(32 + (rand() % 2) * 16, 32 + (rand() % 2) * 16);
					_levelData->SpritesOffset[i][j][1].Set(0, 0);
					_levelData->SpritesOffset[i][j][2].Set(0, 0);
					_levelData->IsBlocking[i][j] = true;
					_levelData->Objects[i][j] = ObjectTypes::None;

					// set random broken parts made of ghost
					if (rand() % 50 == 1) {
						_levelData->Objects[i][j] = ObjectTypes::Ghost;
					}
				}
			}

			// draw objects and player
			startIndex.X -= 2;
			startIndex.Y -= 1;
			endIndex.X += 2;
			endIndex.Y += 4;
			startIndex.Clamp(0, MapSize);
			endIndex.Clamp(0, MapSize);
			for (int j = startIndex.Y; j < endIndex.Y; ++j) {
				for (int i = startIndex.X; i < endIndex.X; ++i) {

					// draw player
					if (playerTileY == j) {
						bon::PointF playerCameraOffset = _camera * -1;
						Gfx().DrawSprite(_player, &playerCameraOffset);
						playerTileY = -1;
					}

					// get tile position
					bon::PointF position(i * TileSize - _camera.X, j * TileSize - _camera.Y);

					// draw objects
					switch (_levelData->Objects[i][j])
					{
						// small tree
						case ObjectTypes::TreeSmall:
							Gfx().DrawImage(_tileset, position, &SmallTreeSize, bon::BlendModes::AlphaBlend, &SmallTreeSource, &SmallTreeOrigin, 0.0f, nullptr);
							break;

						// large tree
						case ObjectTypes::TreeLarge:
							Gfx().DrawImage(_tileset, position, &LargeTreeSize, bon::BlendModes::AlphaBlend, &LargeTreeSource, &LargeTreeOrigin, 0.0f, nullptr);
							break;

						// spooky ghost
						case ObjectTypes::Ghost:
							bon::RectangleI source = GhostSource;
							if ((int)(Game().ElapsedTime() * 10) % 7 == 0 && rand() % 5 < 2) source.X += 16;
							Gfx().DrawImage(_tileset, position, &GhostSize, bon::BlendModes::AlphaBlend, &source, &GhostOrigin, 0.0f, nullptr);
					}
				}
			}

			// check if close enough to ghost
			if (!_didSeeGhost && (_player.Position / (float)TileSize).DistanceTo(GhostPosition) < 2) {

				// stop all sounds and music
				Sfx().StopMusic();
				Sfx().StopChannel(bon::AllChannels);

				// mark as seen ghost and increase player speed to running
				_didSeeGhost = true;
				PlayerSpeed += 75.0f;

				// remove ghost and play scary sounds
				_levelData->Objects[GhostPosition.X][GhostPosition.Y] = ObjectTypes::None;
				Sfx().PlaySound(Assets().LoadSound("../TestAssets/sfx/noise.mp3"));
				Sfx().PlaySound(Assets().LoadSound("../TestAssets/sfx/heartbeat.wav"), 150, -1);
			}

			// draw help text
			if (_showHelpText) {
				if (_didSeeGhost) {
					if (rand() % 4 < 2) {
						Gfx().DrawText(_font, "Demo #4: YOU WONDERED TOO FAR", bon::PointF(100, 100));
						Gfx().DrawText(_font, "Just a little game where you can ??? ????? ???? ??.\nUse arrows or WASD to RUN.\nPress Space to HIDE.\nThere is no escape.", bon::PointF(100, 200), &bon::Color(1, 0, 0, 1), 26);
					}
				}
				else
				{
					Gfx().DrawText(_font, "Demo #4: a Walk In The Forest", bon::PointF(100, 100));
					Gfx().DrawText(_font, "Just a little game where you can walk around in a forest.\nUse arrows or WASD to move around.\nPress Space to hide / show this text.\nHit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 26);

					// auto index = std::to_string((int)_player.Position.X / TileSize) + "," + std::to_string((int)_player.Position.Y / TileSize);
					// Gfx().DrawText(_font, index.c_str(), bon::PointF(100, 700));
				}
			}

			// draw fps
			Gfx().DrawText(_font, (std::string("FPS: ") + std::to_string(_didSeeGhost ? rand() : Diagnostics().FpsCount())).c_str(), bon::PointF(0, 0), &bon::Color(1, 1, 1, 1), 18);
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = WalkInTheForestScene();
		bon::Start(scene);
	}

}