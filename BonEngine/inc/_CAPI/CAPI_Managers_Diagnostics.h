/*****************************************************************//**
 * \file   CAPI_Managers_Diagnostics.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for diagnostics manager.
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
	* Get counter value.
	*/
	BON_DLLEXPORT long BON_Diagnostics_GetCounter(int id);

	/**
	* Increase counter value.
	*/
	BON_DLLEXPORT void BON_Diagnostics_IncreaseCounter(int id, int amount);

	/**
	* Reset counter value.
	*/
	BON_DLLEXPORT void BON_Diagnostics_ResetCounter(int id);

#ifdef __cplusplus
}
#endif