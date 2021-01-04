/*****************************************************************//**
 * \file   CAPI.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This is main entry point, and a single header for all.
 *
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "BonEngine.h"
#include "CAPI_Scene.h"
#include "CAPI_Engine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * Initialize the engine with a special scene designed to accept callbacks from external sources.
	 */
	BON_DLLEXPORT void BON_Start(bon::engine::Scene* scene);

	/**
	 * Initialize the engine with a special scene designed to accept callbacks from external sources + feature flags.
	 */
	BON_DLLEXPORT void BON_StartEx(bon::engine::Scene* scene, bool enableLogs, bool registerToSignals);

	/**
	 * Stop and exit the engine.
	 */
	BON_DLLEXPORT void BON_Stop();

	/**
	 * Get the engine instance.
	 */
	BON_DLLEXPORT bon::engine::Engine* BON_GetEngine();

#ifdef __cplusplus
}
#endif