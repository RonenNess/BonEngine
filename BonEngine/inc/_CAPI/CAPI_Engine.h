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

	// CAPI export of engine states.
	BON_DLLEXPORT enum BON_Engine_States
	{
		BON_State_BeforeInitialize = bon::engine::EngineStates::BeforeInitialize,
		BON_State_Initialize = bon::engine::EngineStates::Initialize,
		BON_State_InternalUpdate = bon::engine::EngineStates::InternalUpdate,
		BON_State_FixedUpdate = bon::engine::EngineStates::FixedUpdate,
		BON_State_Update = bon::engine::EngineStates::Update,
		BON_State_Draw = bon::engine::EngineStates::Draw,
		BON_State_MainLoopInBetweens = bon::engine::EngineStates::MainLoopInBetweens,
		BON_State_HandleEvents = bon::engine::EngineStates::HandleEvents,
		BON_State_Stopping = bon::engine::EngineStates::Stopping,
		BON_State_Destroyed = bon::engine::EngineStates::Destroyed,
		BON_State_SwitchScene = bon::engine::EngineStates::SwitchScene
	};

	/**
	 * Get engine current state.
	 */
	BON_DLLEXPORT BON_Engine_States BON_Engine_CurrentState();

	/**
	 * Get updates count.
	 */
	BON_DLLEXPORT unsigned long long BON_Engine_UpdatesCount();

	/**
	 * Get fixed updates count.
	 */
	BON_DLLEXPORT unsigned long long BON_Engine_FixedUpdatesCount();
	
	/**
	 * Get if engine is destroyed.
	 */
	BON_DLLEXPORT bool BON_Engine_Destroyed();

	/**
	 * Get if engine is running.
	 */
	BON_DLLEXPORT bool BON_Engine_Running();

	/**
	 * Get fixed updates interval.
	 */
	BON_DLLEXPORT double BON_Engine_GetFixedUpdatesInterval();
	
	/**
	 * Set fixed updates interval.
	 */
	BON_DLLEXPORT void BON_Engine_SetFixedUpdatesInterval(double value);

#ifdef __cplusplus
}
#endif