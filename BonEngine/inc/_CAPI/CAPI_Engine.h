/*****************************************************************//**
 * \file   CAPI_Engine.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for engine-related stuff.
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
	 * Get Game manager.
	 */
	BON_DLLEXPORT bon::IGame* BON_Engine_Game();

	/**
	 * Get Assets manager.
	 */
	BON_DLLEXPORT bon::IAssets* BON_Engine_Assets();

	/**
	 * Get Gfx manager.
	 */
	BON_DLLEXPORT bon::IGfx* BON_Engine_Gfx();

	/**
	 * Get Sfx manager.
	 */
	BON_DLLEXPORT bon::ISfx* BON_Engine_Sfx();

	/**
	 * Get Input manager.
	 */
	BON_DLLEXPORT bon::IInput* BON_Engine_Input();

	/**
	 * Get Log manager.
	 */
	BON_DLLEXPORT bon::ILog* BON_Engine_Log();

	/**
	 * Get Diagnostics manager.
	 */
	BON_DLLEXPORT bon::IDiagnostics* BON_Engine_Diagnostics();

	/**
	 * Get manager by name.
	 */
	BON_DLLEXPORT bon::IManager* BON_Engine_GetManager(const char* id);

	/**
	 * Get engine current state.
	 */
	BON_DLLEXPORT bon::engine::EngineStates BON_Engine_CurrentState();

#ifdef __cplusplus
}
#endif