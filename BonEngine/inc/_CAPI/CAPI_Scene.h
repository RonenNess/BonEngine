/*****************************************************************//**
 * \file   CAPI_Scene.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for scene-related stuff.
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
	 * Create and return a special scene composed of callbacks.
	 * This is in order to bind a scene from another language.
	 * Note: must call BON_DestroyScene() when done.
	 */
	BON_DLLEXPORT bon::engine::Scene* BON_Scene_Create(BON_CallbackNoArgs onLoad, BON_CallbackNoArgs onUnload, BON_CallbackNoArgs onStart, BON_CallbackNoArgs onDraw, BON_CallbackDoubleArg onUpdate, BON_CallbackDoubleArg onFixedUpdate);

	/**
	 * Destroys a scene created with 'BON_CreateScene'.
	 */
	BON_DLLEXPORT void BON_Scene_Destroy(bon::engine::Scene* scene);

	/**
	 * Get if its the first scene loaded.
	 */
	BON_DLLEXPORT bool BON_Scene_IsFirstScene(bon::engine::Scene* scene);


#ifdef __cplusplus
}
#endif