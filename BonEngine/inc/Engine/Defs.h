/*****************************************************************//**
 * \file   Defs.h
 * \brief  Misc engine-related defs.
 *
 * \author Ronen Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"

namespace bon
{
	namespace engine
	{
		/**
		 * Different states the engine can be in.
		 */
		enum class BON_DLLEXPORT EngineStates
		{
			// Engine was not initialized yet.
			BeforeInitialize = 0,

			// engine is initializing now.
			Initialize = 1,

			// engine is doing managers updates.
			InternalUpdate = 2,

			// engine is doing fixed updates.
			FixedUpdate = 3,

			// engine is doing regular updates.
			Update = 4,

			// engine is drawing.
			Draw = 5,

			// engine is doing other main-loop code that isn't updates or drawing.
			MainLoopInBetweens = 6,

			// engine is handling events
			HandleEvents = 7,

			// engine is stopping
			Stopping = 8,

			// engine is completely stopped and destroyed
			Destroyed = 9,

			// engine is currently switching scenes (not set on first scene set).
			SwitchScene = 10,
		};
	}
}