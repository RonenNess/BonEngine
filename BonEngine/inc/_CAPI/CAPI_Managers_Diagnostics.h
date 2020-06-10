/*****************************************************************//**
 * \file   CAPI_Managers_Diagnostics.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for diagnostics manager.
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
	* Get counter value.
	*/
	BON_DLLEXPORT int64_t BON_Diagnostics_GetCounter(int id);

	/**
	* Increase counter value.
	*/
	BON_DLLEXPORT void BON_Diagnostics_IncreaseCounter(int id, int amount);

	/**
	* Reset counter value.
	*/
	BON_DLLEXPORT void BON_Diagnostics_ResetCounter(int id);

	/**
	* Get FPS count.
	*/
	BON_DLLEXPORT void BON_Diagnostics_FpsCounter();

#ifdef __cplusplus
}
#endif