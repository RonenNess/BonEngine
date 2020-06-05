#include <_CAPI/CAPI_Managers_Game.h>
#include <BonEngine.h>

// Exit game.
BON_DLLEXPORT void BON_Game_Exit()
{
	bon::_GetEngine().Game().Exit();
}

// Change active scene.
BON_DLLEXPORT void BON_Game_ChangeScene(bon::engine::Scene* scene)
{
	bon::_GetEngine().Game().ChangeScene(*scene);
}

// Load game config from ini file and setup everything accordingly.
BON_DLLEXPORT void BON_Game_LoadConfig(const char* path)
{
	bon::_GetEngine().Game().LoadConfig(path);
}

// Get total elapsed time, in seconds.
BON_DLLEXPORT double BON_Game_ElapsedTime()
{
	return bon::_GetEngine().Game().ElapsedTime();
}

// Get current frame delta time, in seconds.
BON_DLLEXPORT double BON_Game_DeltaTime()
{
	return bon::_GetEngine().Game().DeltaTime();
}