/*****************************************************************//**
 * \file   IManager.h
 * \brief  Interface for a BonEngine subsystem / manager.
 *
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "dllimport.h"

// forward declare sdl event
union SDL_Event;

namespace bon
{
	// forward declare base asset class.
	namespace assets
	{
		class IAsset;
		class Assets;
	}

	// forward declare engine
	namespace engine
	{
		class Engine;
	}

	/**
	 * Base class for any BonEngine manager class.
	 */
	class DLLEXPORT IManager
	{
		// to allow engine to access our internals
		friend class engine::Engine;

	protected:
		/**
		 * Initialize manager when engine starts.
		 */
		virtual void _Initialize() {}

		/**
		 * Called when main loop starts.
		 */
		virtual void _Start() {}

		/**
		 * Clear / free this manager's resources.
		 */
		virtual void _Dispose() {}

		/**
		 * Called every frame.
		 */
		virtual void _Update(double deltaTime) {}

		/**
		 * Handles an event from OS.
		 */
		virtual void _HandleEvent(SDL_Event& event) {}

		/**
		 * Get manager identifier.
		 */
		virtual const char* _GetId() const = 0;
	};
}
