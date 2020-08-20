#include <Game/Game.h>
#include <BonEngine.h>
#include <Engine/Engine.h>
#include <../3rdparty/INIReader/INIReader.h>


namespace bon
{
	namespace game
	{
		// defined later in this file
		void ConfigLoader(bon::assets::IAsset* asset, void* context, void* extraData = nullptr);
		void ConfigDisposer(bon::assets::IAsset* asset, void* context);

		// init game manager
		void Game::_Initialize()
		{
			// register the assets initializers for config files
			bon::_GetEngine().Assets()._SetAssetsInitializer(bon::assets::AssetTypes::Config, ConfigLoader, ConfigDisposer, this);
		}

		// dispose game resources
		void Game::_Dispose()
		{
		}
		
		// do updates
		void Game::_Update(double deltaTime)
		{
			// update total elapsed time
			int prevSecondCount = (int)floor(_elapsedTime);
			_elapsedTime += deltaTime;
			_deltaTime = deltaTime;
		}

		// called on main loop start
		void Game::_Start()
		{
		}

		// exit game
		void Game::Exit()
		{
			_GetEngine().Stop();
		}

		// change active scene
		void Game::ChangeScene(engine::Scene& scene)
		{
			_GetEngine().SetScene(scene);
		}

		// load config file
		void Game::LoadConfig(const char* path)
		{
			// logging
			BON_DLOG("-----------------------------------------------");
			BON_ILOG("Load game config from file: '%s'.", path);

			// load config
			ConfigAsset config = _GetEngine().Assets().LoadConfig(path, false);
			if (!config->IsValid()) {
				BON_ELOG("Config file not found or corrupted!");
				throw framework::AssetLoadError("Fail to load config file!");
			}

			// start by initializing graphics
			if (config->Exists("gfx"))
			{
				static const char* WindowModesOptions[] = { "windowed", "windowed_borderless", "fullscreen" };
				const char* title = config->GetStr("gfx", "title", "");
				framework::PointF resolution = config->GetPointF("gfx", "resolution", framework::PointF(800, 600));
				int mode = config->GetOption("gfx", "window_mode", WindowModesOptions, 0);
				bool cursor = config->GetBool("gfx", "cursor", true);
				BON_DLOG("Gfx config: title = %s, resolution = %dx%d, mode = %s, cursor = %d",
					title, (int)resolution.X, (int)resolution.Y, WindowModesOptions[mode], cursor);
				_GetEngine().Gfx().SetWindowProperties(title, (int)resolution.X, (int)resolution.Y, (WindowModes)mode, cursor);
			}

			// initialize sfx
			if (config->Exists("sfx"))
			{
				static const char* FormatOptions[] = { "U8", "S8", "U16LSB", "S16LSB", "U16MSB", "S16MSB" };
				int frequency = config->GetInt("sfx", "frequency", 22050);
				int format = config->GetOption("sfx", "format", FormatOptions, 3);
				if (format == -1) { format = (int)AudioFormats::S16LSB; }
				int stereo = config->GetBool("sfx", "stereo", true);
				int audio_chunk_size = config->GetInt("sfx", "audio_chunk_size", 4096);
				BON_DLOG("Sfx config: frequency = %d, format = %s, stereo = %d, audio_chunk_size = %d",
					frequency, FormatOptions[format], stereo, audio_chunk_size);
				_GetEngine().Sfx().SetAudioProperties(frequency, (AudioFormats)format, stereo, audio_chunk_size);
			}

			// initialize controls
			if (config->Exists("controls"))
			{
				BON_DLOG("Found %d key binds in config. Will set them now.");
				_GetEngine().Input().LoadControlsFromConfig(config, true);
			}

			BON_DLOG("Finished config loading.");
			BON_DLOG("-----------------------------------------------");
		}

		// config handler to load game config files
		class ConfigIniHandle : public _ConfigHandle
		{
		private:
			INIReader _reader;
		
		public:

			/**
			 * Create the handle without reading config file (empty config).
			 */
			ConfigIniHandle() : _reader()
			{
			}

			/**
			 * Create the handle from ini file.
			 */
			ConfigIniHandle(const char* path) : _reader(path)
			{
			}

			/**
			* Get if this config file is valid.
			*/
			virtual bool IsValid() const override { return _reader.ParseError() == 0; }

			/**
			 * Get string value from config.
			 */
			virtual const char* GetStr(const char* section, const char* name, const char* defaultVal) const override 
			{
				return _reader.GetRef(string(section), string(name), defaultVal);
			}

			/**
			 * Get bool value from config.
			 */
			virtual bool GetBool(const char* section, const char* name, bool defaultVal) const override 
			{
				return _reader.GetBoolean(string(section), string(name), defaultVal);
			}

			/**
			 * Get integer value from config.
			 */
			virtual long GetInt(const char* section, const char* name, int defaultVal) const override
			{
				return _reader.GetInteger(string(section), string(name), defaultVal);
			}

			/**
			 * Get float value from config.
			 */
			virtual float GetFloat(const char* section, const char* name, float defaultVal) const override
			{
				return _reader.GetFloat(string(section), string(name), defaultVal);
			}

			/**
			 * Get vector with all section names.
			 */
			virtual const std::set<std::string>& Sections() const override
			{
				return _reader.Sections();
			}

			/**
			 * Get vector with all keys in section.
			 */
			virtual const std::set<std::string>& Keys(const char* section) const override
			{
				return _reader.Keys(section);
			}

			/**
			 * Updates a value.
			 */
			virtual void UpdateValue(const char* section, const char* key, const char* value) override
			{
				_reader.SetValue(section, key, value, true);
			}

			/**
			 * Removes a key.
			 */
			virtual void RemoveKey(const char* section, const char* key) override
			{
				_reader.RemoveKey(section, key);
			}

			/**
			 * Save configuration to file.
			 */
			virtual bool SaveConfig(const char* filename) const override
			{
				try
				{
					_reader.Save(filename);
					return true;
				}
				catch (const std::exception&)
				{
					return false;
				}
			}
		};

		// config loader we set in the assets manager during initialize
		void ConfigLoader(bon::assets::IAsset* asset, void* context, void* extraData)
		{
			const char* path = asset->Path();
			ConfigIniHandle* handle = path != nullptr ? new ConfigIniHandle(path) : new ConfigIniHandle();
			asset->_SetHandle(handle);
		}

		// images disposer we set in the assets manager during asset disposal
		void ConfigDisposer(bon::assets::IAsset* asset, void* context)
		{
			asset->_DestroyHandle<ConfigIniHandle>();
		}
	}
}