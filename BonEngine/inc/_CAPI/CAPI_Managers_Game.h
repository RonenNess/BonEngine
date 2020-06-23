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
#include "../BonEngine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* Exit game.
	*/
	BON_DLLEXPORT void BON_Game_Exit();

	/**
	 * Change active scene.
	 */
	BON_DLLEXPORT void BON_Game_ChangeScene(bon::engine::Scene* scene);

	/**
	 * Load game config from ini file and setup everything accordingly.
	 */
	BON_DLLEXPORT void BON_Game_LoadConfig(const char* path);

	/**
	 * Get total elapsed time, in seconds.
	 */
	BON_DLLEXPORT double BON_Game_ElapsedTime();

	/**
	 * Get current frame delta time, in seconds.
	 */
	BON_DLLEXPORT double BON_Game_DeltaTime();

#ifdef __cplusplus
}
#endif