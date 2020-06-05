#include <_CAPI/CAPI_Engine.h>
#include <BonEngine.h>

// get engine instance
bon::engine::Engine* BON_GetEngine()
{
	return &bon::_GetEngine();
}

// get Game manager.
bon::IGame* BON_Engine_Game()
{
	return &bon::_GetEngine().Game();
}

// get Assets manager.
bon::IAssets* BON_Engine_Assets()
{
	return &bon::_GetEngine().Assets();
}

// get Gfx manager.
bon::IGfx* BON_Engine_Gfx()
{
	return &bon::_GetEngine().Gfx();
}

// get Sfx manager.
bon::ISfx* BON_Engine_Sfx()
{
	return &bon::_GetEngine().Sfx();
}

// get Input manager.
bon::IInput* BON_Engine_Input()
{
	return &bon::_GetEngine().Input();
}

// get Log manager.
bon::ILog* BON_Engine_Log()
{
	return &bon::_GetEngine().Log();
}

// get Diagnostics manager.
bon::IDiagnostics* BON_Engine_Diagnostics()
{
	return &bon::_GetEngine().Diagnostics();
}

// get manager by name.
bon::IManager* BON_Engine_GetManager(const char* id)
{
	return bon::_GetEngine().GetManagerById(id);
}

// get engine current state
bon::engine::EngineStates BON_Engine_CurrentState()
{
	return bon::_GetEngine().CurrentState();
}