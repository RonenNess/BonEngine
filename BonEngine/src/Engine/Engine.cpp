#include <Engine/Engine.h>
#include <Framework/Exceptions.h>
#include <Gfx/Gfx.h>
#include <Sfx/Sfx.h>
#include <Assets/Assets.h>
#include <Game/Game.h>
#include <Log/Log.h>
#include <Input/Input.h>
#include <Diagnostics/Diagnostics.h>
#include <UI/UI.h>
#include <Engine/Scene.h>
#include <BonEngine.h>
#include <Engine/SignalHandler.h>

#pragma warning(push, 0)
#include <SDL2-2.0.12/include/SDL.h>
#pragma warning(pop)

using namespace bon::framework;

namespace bon
{
	namespace engine
	{
		// start running
		void Engine::Start(Scene& startingScene)
		{
			// already running / init? error
			if (_isRunning || _state != EngineStates::BeforeInitialize) { throw InvalidState("Cannot start engine - engine is already running!"); }

			// update state to init
			_state = EngineStates::Initialize;

			// get features
			auto features = bon::Features();
			
			// create default debug manager
			if (!_logManager) {
				_logManager = new log::Log();
			}

			// disable logs if feature is disabled
			if (!features.Logging) {
				_logManager->SetLevel(LogLevel::None);
			}

			// init log manager before everyone else
			_logManager->_Initialize();
			_logManager->Write(log::LogLevel::Info, "Engine starts.");

			// create default diagnostics manager
			if (!_diagnosticsManager) {
				_diagnosticsManager = new diagnostics::Diagnostics();
				_logManager->Write(log::LogLevel::Debug, "Created default diagnostics manager.");
			}
			else {
				_logManager->Write(log::LogLevel::Debug, "Didn't create default diagnostics manager because user already registered a custom one.");
			}

			// create default assets manager
			if (!_assetsManager) {
				_assetsManager = new assets::Assets();
				_logManager->Write(log::LogLevel::Debug, "Created default assets manager.");
			} 
			else {
				_logManager->Write(log::LogLevel::Debug, "Didn't create default assets manager because user already registered a custom one.");
			}

			// create default gfx manager
			if (!_gfxManager) {
				_gfxManager = new gfx::Gfx();
				_logManager->Write(log::LogLevel::Debug, "Created default gfx manager.");
			}
			else {
				_logManager->Write(log::LogLevel::Debug, "Didn't create default gfx manager because user already registered a custom one.");
			}

			// create default sfx manager
			if (!_sfxManager) {
				_sfxManager = new sfx::Sfx();
				_logManager->Write(log::LogLevel::Debug, "Created default sfx manager.");
			}
			else {
				_logManager->Write(log::LogLevel::Debug, "Didn't create default sfx manager because user already registered a custom one.");
			}

			// create default input manager
			if (!_inputManager) {
				_inputManager = new input::Input();
				_logManager->Write(log::LogLevel::Debug, "Created default input manager.");
			}
			else {
				_logManager->Write(log::LogLevel::Debug, "Didn't create default input manager because user already registered a custom one.");
			}

			// create default game manager
			if (!_gameManager) {
				_gameManager = new game::Game();
				_logManager->Write(log::LogLevel::Debug, "Created default game manager.");
			}
			else {
				_logManager->Write(log::LogLevel::Debug, "Didn't create default game manager because user already registered a custom one.");
			}

			// create default ui manager
			if (!_uiManager) {
				_uiManager = new ui::UI();
				_logManager->Write(log::LogLevel::Debug, "Created default ui manager.");
			}
			else {
				_logManager->Write(log::LogLevel::Debug, "Didn't create default ui manager because user already registered a custom one.");
			}

			// register all built-in managers
			_managers.push_back(_logManager);
			_managers.push_back(_inputManager);
			_managers.push_back(_assetsManager);
			_managers.push_back(_gameManager);
			_managers.push_back(_gfxManager);
			_managers.push_back(_sfxManager);
			_managers.push_back(_diagnosticsManager);
			_managers.push_back(_uiManager);
			
			// initialize all managers
			_logManager->Write(log::LogLevel::Debug, "Initialize managers.");
			for (size_t i = 0; i < _managers.size(); ++i) {
				_logManager->Write(log::LogLevel::Debug, "Manager: '%s'.", (_managers)[i]->_GetId());
				(_managers)[i]->_Initialize();
			}

			// init custom managers
			if (!_customManagers.empty()) {
				_logManager->Write(log::LogLevel::Debug, "Initialize custom managers.");
				for (size_t i = 0; i < _customManagers.size(); ++i) {
					_logManager->Write(log::LogLevel::Debug, "Init manager: '%s'.", (_customManagers)[i]->_GetId());
					(_customManagers)[i]->_Initialize();
					_managers.push_back((_customManagers)[i]);
				}
				_customManagers.clear();
			}

			// set active scene
			_logManager->Write(log::LogLevel::Debug, "Engine ready, set starting scene.");
			_isRunning = true;
			SetScene(startingScene);

			// register signals handler
			if (features.RegisterSignalsHandler) {
				RegisterSignalsHandler();
			}

			// start main loop
			_logManager->Write(log::LogLevel::Debug, "Start main loop...");
			StartMainLoop();
		}

		// register a custom manager class
		void Engine::RegisterCustomManager(IManager* manager)
		{
			if (_isRunning) {
				_logManager->Write(log::LogLevel::Debug, "Register custom manager post-init: '%s'.", manager->_GetId());
				manager->_Start();
				_managers.push_back(manager);
			}
			else {
				_customManagers.push_back(manager);
			}
		}

		// get manager instance by id
		IManager* Engine::GetManagerById(const char* id)
		{
			for (size_t i = 0; i < _managers.size(); ++i) {
				if (strcmp(id, (_managers)[i]->_GetId()) == 0) {
					return (_managers)[i];
				}
			}
			return nullptr;
		}

		// start engine main loop
		void Engine::StartMainLoop()
		{
			_logManager->Write(log::LogLevel::Info, "Main loop start init.");

			// to measure delta time
			Uint64 NOW = SDL_GetPerformanceCounter();
			Uint64 LAST = 0;
			double deltaTime = 0;

			// count time for next fixed updates
			double timeForNextFixedUpdate = 0;

			// start all managers
			for (size_t i = 0; i < _managers.size(); ++i) {
				_logManager->Write(log::LogLevel::Info, "Start manager: '%s'.", (_managers)[i]->_GetId());
				(_managers)[i]->_Start();
			}
			_logManager->Write(log::LogLevel::Info, "All managers ready, game loop starting..");

			// call active scene's start
			_mainLoopStarted = true;
			if (_activeScene) {
				_activeScene->_Start();
			}

			// SDL event handler
			SDL_Event e;

#ifdef _DEBUG 
			try
			{
#endif
				// focus on window
				Gfx().FocusWindow();

				// main loop
				while (_isRunning)
				{
					// if we have a scene to switch to, do the switching
					if (_nextScene) {
						_state = EngineStates::SwitchScene;
						DoSceneSwitch();
					}

					// update state to in-between
					_state = EngineStates::MainLoopInBetweens;

					// no active scene? skip frame
					if (!_activeScene) {
						continue;
					}

					// calculates per-frame delta time
					LAST = NOW;
					NOW = SDL_GetPerformanceCounter();
					deltaTime = ((double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency())) / 1000.0;

					// update all managers
					_state = EngineStates::InternalUpdate;
					for (size_t i = 0; i < _managers.size(); ++i) {
						(_managers)[i]->_Update(deltaTime);
					}
					_state = EngineStates::MainLoopInBetweens;

					// handle events on queue
					_state = EngineStates::HandleEvents;
					while (SDL_PollEvent(&e) != 0)
					{
						// user requests quit
						if (e.type == SDL_QUIT)
						{
							_isRunning = false;
							break;
						}

						// send event to all managers
						for (size_t i = 0; i < _managers.size(); ++i) {
							(_managers)[i]->_HandleEvent(e);
						}
					}
					_state = EngineStates::MainLoopInBetweens;

					// update scene
					if (deltaTime > 0) 
					{
						// do fixed updates
						_state = EngineStates::FixedUpdate;
						if (FixedUpdatesInterval > 0)
						{
							timeForNextFixedUpdate += deltaTime;
							while (timeForNextFixedUpdate > FixedUpdatesInterval)
							{
								// do fixed update
								_activeScene->_FixedUpdate(FixedUpdatesInterval);

								// if need to switch scene skip here
								if (_nextScene) {
									break;
								}

								// update time until next fixed update and increase fixed updates count
								timeForNextFixedUpdate -= FixedUpdatesInterval;
								_fixedUpdatesCount++;
							}
						}
						_state = EngineStates::MainLoopInBetweens;

						// if need to switch scene skip here
						if (_nextScene) {
							continue;
						}

						// do per-frame update, unless need to switch scene
						_state = EngineStates::Update;
						_activeScene->_Update(deltaTime);
						_state = EngineStates::MainLoopInBetweens;

						// increase updates count
						_updatesCount++;

						// if need to switch scene skip here
						if (_nextScene) {
							continue;
						}
					}

					// draw scene
					_state = EngineStates::Draw;
					_activeScene->_Draw();
					_state = EngineStates::MainLoopInBetweens;
				}

#ifdef _DEBUG 
			}
			catch (exception& e)
			{
				BON_ELOG("Unexpected exception in main loop! Error: %s", e.what());
				throw e;
			}
#endif

			// when done, call cleanup
			_state = EngineStates::Stopping;
			_logManager->Write(log::LogLevel::Info, "Main loop ends.");
			CleanUp();
		}

		// cleanup when engine ends
		void Engine::CleanUp()
		{
			_logManager->Write(log::LogLevel::Info, "Cleanup called.");
			_destroyed = true;

			// dispose active scene
			if (_activeScene) {
				_activeScene->_Unload();
			}

			// destroy all managers (note: in reverse order of their creation / update)
			_logManager->Write(log::LogLevel::Info, "Destroy managers.");
			for (int i = (int)_managers.size() - 1; i >= 0; --i) {
				(_managers)[i]->_Dispose();
			}

			// set as destroyed
			_state = EngineStates::Destroyed;
		}

		// stop running
		void Engine::Stop()
		{
			if (_isRunning) {
				_logManager->Write(log::LogLevel::Debug, "Stop() called.");
				_isRunning = false;
			}
		}

		// set the new active scene
		void Engine::SetScene(Scene& scene)
		{
			// log and sanity check
			_logManager->Write(log::LogLevel::Debug, "Set next scene to switch to..");
			if (_destroyed) {
				throw InvalidState("Cannot set scene after engine was destroyed!");
			}

			// set next scene
			_nextScene = &scene;

			// if there's no current scene, switch now
			if (_activeScene == nullptr) {
				DoSceneSwitch();
			}
		}

		// do the actual scene switch
		void Engine::DoSceneSwitch()
		{
			// no scene to switch to? stop.
			if (_nextScene == nullptr) {
				return;
			}

			// increase scenes switch counter
			_scenesSwitchCount++;

			// log and sanity check
			_logManager->Write(log::LogLevel::Debug, "Change scene - beings..");
			if (_destroyed) {
				throw InvalidState("Cannot set scene after engine was destroyed!");
			}

			// dispose previous scene
			if (_activeScene) {
				_logManager->Write(log::LogLevel::Debug, "Unload previously active scene.");
				_activeScene->_Unload();
			}

			// set new scene
			_logManager->Write(log::LogLevel::Debug, "Set and load new active scene.");
			_previousScene = _activeScene;
			_activeScene = _nextScene;
			_activeScene->_Load();
			_nextScene = nullptr;

			// if already started main loop, trigger _Start() now
			if (_mainLoopStarted) {
				_logManager->Write(log::LogLevel::Debug, "Start new active scene.");
				_activeScene->_Start();
			}
		}
	}
}