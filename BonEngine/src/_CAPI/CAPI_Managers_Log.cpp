#include <_CAPI/CAPI_Managers_Log.h>
#include <BonEngine.h>

// Check if log level is valid.
BON_DLLEXPORT bool BON_Log_IsValid(bon::LogLevel level)
{
	return bon::_GetEngine().Log().IsValid(level);
}

// Get log level.
BON_DLLEXPORT bon::LogLevel BON_Log_GetLevel()
{
	return bon::_GetEngine().Log().GetLevel();
}

// Set log level.
BON_DLLEXPORT void BON_Log_SetLevel(bon::LogLevel level)
{
	bon::_GetEngine().Log().SetLevel(level);
}

// Write log.
BON_DLLEXPORT void BON_Log_Write(bon::LogLevel level, const char* msg)
{
	bon::_GetEngine().Log().Write(level, msg);
}