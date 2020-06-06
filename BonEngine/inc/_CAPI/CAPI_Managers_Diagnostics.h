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

	// CAPI export of diagnostic counters
	BON_DLLEXPORT enum BON_DiagnosticCounters
	{
		BON_Counters_DrawCalls = bon::DiagnosticsCounters::DrawCalls,
		BON_Counters_PlaySoundCalls = bon::DiagnosticsCounters::PlaySoundCalls,
		BON_Counters_LoadedAssets = bon::DiagnosticsCounters::LoadedAssets,
		BON_Counters__BuiltInCounterCount = bon::DiagnosticsCounters::_BuiltInCounterCount,
		BON_Counters__MaxCounters = bon::DiagnosticsCounters::_MaxCounters,
	};

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

#ifdef __cplusplus
}
#endif