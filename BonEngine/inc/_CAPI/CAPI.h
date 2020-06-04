/*****************************************************************//**
 * \file   CAPI.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "BonEngine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * Define callback without arguments.
	 */
	BON_DLLEXPORT typedef void (*BON_CallbackNoArgs)();

	/**
	 * Define callback with double argument.
	 */
	BON_DLLEXPORT typedef void (*BON_CallbackDoubleArg)(double);
	
	/**
	 * Create and return a special scene composed of callbacks.
	 * This is in order to bind a scene from another language.
	 * Note: must call BON_DestroyScene() when done.
	 */
	BON_DLLEXPORT bon::engine::Scene* BON_CreateScene(BON_CallbackNoArgs onLoad, BON_CallbackNoArgs onUnload, BON_CallbackNoArgs onStart, BON_CallbackNoArgs onDraw, BON_CallbackDoubleArg onUpdate, BON_CallbackDoubleArg onFixedUpdate);

	/**
	 * Destroys a scene created with 'BON_CreateScene'.
	 */
	BON_DLLEXPORT void BON_DestroyScene(bon::engine::Scene* scene);

	/**
	 * Initialize the engine with a special scene designed to accept callbacks from external sources.
	 */
	BON_DLLEXPORT void BON_Start(bon::engine::Scene* scene);


#ifdef __cplusplus
}
#endif