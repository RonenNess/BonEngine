#include <Engine/ManagerGetters.h>
#include <Engine/Engine.h>
#include <Game/IGame.h>
#include <Assets/IAssets.h>
#include <Gfx/IGfx.h>
#include <Input/IInput.h>
#include <Log/ILog.h>
#include <Diagnostics/IDiagnostics.h>
#include <BonEngine.h>

namespace bon
{
	namespace engine
	{
		// get game manager
		game::IGame& ManagerGetters::Game()
		{
			return _GetEngine().Game();
		}

		// get assets manager
		assets::IAssets& ManagerGetters::Assets()
		{
			return _GetEngine().Assets();
		}

		// get gfx manager
		gfx::IGfx& ManagerGetters::Gfx()
		{
			return _GetEngine().Gfx();
		}

		// get sfx manager
		sfx::ISfx& ManagerGetters::Sfx()
		{
			return _GetEngine().Sfx();
		}

		// get input manager
		input::IInput& ManagerGetters::Input()
		{
			return _GetEngine().Input();
		}

		// get log manager
		log::ILog& ManagerGetters::Log()
		{
			return _GetEngine().Log();
		}

		// get diagnostics manager
		diagnostics::IDiagnostics& ManagerGetters::Diagnostics()
		{
			return _GetEngine().Diagnostics();
		}

		// get manager by id
		IManager* ManagerGetters::GetManager(const char* id)
		{
			return _GetEngine().GetManagerById(id);
		}
	}
}