/*****************************************************************//**
 * \file   ManagerGetters.h
 * \brief  Provide access to all engine managers. 
 *			Used by the scene base class.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"

namespace bon
{
	// forward declare manager interfaces
	class IManager;
	namespace assets
	{
		class IAssets;
	}
	namespace game
	{
		class IGame;
	}
	namespace gfx
	{
		class IGfx;
	}
	namespace sfx
	{
		class ISfx;
	}
	namespace log
	{
		class ILog;
	}
	namespace input
	{
		class IInput;
	}
	namespace diagnostics
	{
		class IDiagnostics;
	}

	namespace engine
	{
		/**
		 * Provide getter access to all engine managers.
		 * Used by the scene class.
		 */
		class DLLEXPORT ManagerGetters
		{
		protected:

			/**
			 * Get game manager from active engine.
			 */
			inline game::IGame& Game();

			/**
			 * Get assets manager from active engine.
			 */
			inline assets::IAssets& Assets();

			/**
			 * Get gfx manager from active engine.
			 */
			inline gfx::IGfx& Gfx();

			/**
			 * Get sfx manager from active engine.
			 */
			inline sfx::ISfx& Sfx();

			/**
			 * Get input manager from active engine.
			 */
			inline input::IInput& Input();

			/**
			 * Get log manager from active engine.
			 */
			inline log::ILog& Log();

			/**
			 * Get diagnostics manager from active engine.
			 */
			inline diagnostics::IDiagnostics& Diagnostics();

			/**
			 * Get manager by id.
			 * This method is slow, only use it for custom managers and cache the result.
			 * 
			 * \param id Manager id to get.
			 * \return Manager instance, or null if not found.
			 */
			inline IManager* GetManager(const char* id);
		};
	}
}