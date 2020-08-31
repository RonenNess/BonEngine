/*****************************************************************//**
 * \file   CAPI_Managers_Log.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for log manager.
 *
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "CAPI_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* Check if log level is valid.
	*/
	BON_DLLEXPORT bool BON_Log_IsValid(BON_LogLevel level);

	/**
	* Get log level.
	*/
	BON_DLLEXPORT BON_LogLevel BON_Log_GetLevel();

	/**
	* Set log level.
	*/
	BON_DLLEXPORT void BON_Log_SetLevel(BON_LogLevel level);
	
	/**
	* Write log.
	*/
	BON_DLLEXPORT void BON_Log_Write(BON_LogLevel level, const char* msg);

	/**
	* Flush log.
	*/
	BON_DLLEXPORT void BON_Log_Flush();

#ifdef __cplusplus
}
#endif