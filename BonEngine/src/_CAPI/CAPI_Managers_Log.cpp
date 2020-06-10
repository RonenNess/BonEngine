#include <_CAPI/CAPI_Managers_Log.h>
#include <BonEngine.h>

// Check if log level is valid.
BON_DLLEXPORT bool BON_Log_IsValid(BON_LogLevel level)
{
	return bon::_GetEngine().Log().IsValid((bon::LogLevel)level);
}

// Get log level.
BON_DLLEXPORT BON_LogLevel BON_Log_GetLevel()
{
	return (BON_LogLevel)(bon::_GetEngine().Log().GetLevel());
}

// Set log level.
BON_DLLEXPORT void BON_Log_SetLevel(BON_LogLevel level)
{
	bon::_GetEngine().Log().SetLevel((bon::LogLevel)level);
}

// Write log.
BON_DLLEXPORT void BON_Log_Write(BON_LogLevel level, const char* msg)
{
	bon::_GetEngine().Log().Write((bon::LogLevel)level, msg);
}