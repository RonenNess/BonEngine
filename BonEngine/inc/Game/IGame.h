/*****************************************************************//**
 * \file   IGame.h
 * \brief  Interface for the game manager class.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "../IManager.h"

// forward declare engine and scene base class
namespace bon
{
	namespace engine
	{
		class Scene;
		class Engine;
	}
}

namespace bon
{
	namespace game
	{
		/**
		 * Interface for the Game manager.
		 * This manager responsible for general game control methods, like changing scene, exit game, ect.
		 * Note: unlike the other managers, this manager actually wraps Engine and is positioned above it, despite being accessed from it.
		 */
		class BON_DLLEXPORT IGame : public IManager
		{
		public:

			/**
			 * Exit game.
			 */
			virtual void Exit() = 0;

			/**
			 * Change active scene.
			 */
			virtual void ChangeScene(engine::Scene& scene) = 0;

			/**
			 * Load game config from ini file and setup everything accordingly.
			 * Note: should be called before main loop starts.
			 * 
			 * \param path ini file path.
			 */
			virtual void LoadConfig(const char* path) = 0;

			/**
			 * Get total elapsed time, in seconds.
			 *
			 * \return Total elapsed time.
			 */
			virtual double ElapsedTime() const = 0;

			/**
			 * Get current frame delta time, in seconds.
			 *
			 * \return Delta time.
			 */
			virtual double DeltaTime() const = 0;

		protected:

			/**
			 * Get manager identifier.
			 */
			virtual const char* _GetId() const override { return "game"; }
		};
	}
}