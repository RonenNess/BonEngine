/*****************************************************************//**
 * \file   BonEngine.h
 * \brief  Main header file to include when using BonEngine. 
 *			This file is all you need to include.
 * 
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once

#include "dllimport.h"

// include engine
#include "Engine/Engine.h"
#include "Engine/Scene.h"

#define _BON_VERSION_STR "1.5.4"
#define _BON_VERSION 1.54

namespace bon
{
	// flatten namespaces
	using namespace bon::gfx;
	using namespace bon::framework;
	using namespace bon::assets;
	using namespace bon::game;
	using namespace bon::log;
	using namespace bon::input;
	using namespace bon::sfx;
	using namespace bon::diagnostics;
	using namespace bon::ui;

	/**
	 * Initialization struct with features to enable in BonEngine.
	 */
	struct BonFeatures
	{
	public:

		/**
		 * If true, will register signals handler to finish logs before exiting.
		 */
		bool RegisterSignalsHandler = false;

		/**
		 * Enable logging by default.
		 */
		bool Logging = true;

		/**
		 * If true, will floor drawing positions, and ceiling drawing size.
		 */
		bool RoundPixels = true;
	};

	/**
	 * Get bon engine enabled features.
	 */
	BON_DLLEXPORT const BonFeatures& Features();

	/**
	 * Get engine instance.
	 * Use this only if you want to tweak with the engine itself, normally you don't need it.
	 */
	BON_DLLEXPORT engine::Engine& _GetEngine();

	/**
	 * Start running BonEngine with a given scene and features struct.
	 */
	BON_DLLEXPORT void Start(engine::Scene& startingScene, const BonFeatures& features);

	/**
	 * Start running BonEngine with a given scene and default features.
	 */
	BON_DLLEXPORT void Start(engine::Scene& startingScene);

	// credits and version
	extern const char* __author__;
	extern const char* __version__;
}
