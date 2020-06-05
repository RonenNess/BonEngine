/*****************************************************************//**
 * \file   CAPI_Managers_Game.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for game manager.
 *
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include <BonEngine.h>

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* Check if log level is valid.
	*/
	BON_DLLEXPORT bool BON_Log_IsValid(bon::LogLevel level);

	/**
	* Get log level.
	*/
	BON_DLLEXPORT bon::LogLevel BON_Log_GetLevel();

	/**
	* Set log level.
	*/
	BON_DLLEXPORT void BON_Log_SetLevel(bon::LogLevel level);
	
	/**
	* Write log.
	*/
	BON_DLLEXPORT void BON_Log_Write(bon::LogLevel level, const char* msg);

#ifdef __cplusplus
}
#endif