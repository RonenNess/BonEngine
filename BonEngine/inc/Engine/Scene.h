/*****************************************************************//**
 * \file   Scene.h
 * \brief  Implement the scene API - the main class the user implements
 *			his logic in.
 * 
 * \author Ronen
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "ManagerGetters.h"


namespace bon
{
	namespace engine
	{
		/**
		 * Scene API - this is the main class the user have to implement.
		 * It contains all the main functions to run BonEngine for a specific level or game mode.
		 */
		class DLLEXPORT Scene : public ManagerGetters
		{
		public:

			/**
			 * Called when scene loads.
			 * Note: this is called as soon as scene is set, and may occur before one or more managers are ready.
			 * This means you can't fully relay on everything being setup, but it also mean you can set some things before engine starts.
			 * If you need a proper init only when everything has started, use _Start();
			 */
			virtual void _Load()
			{
			}

			/**
			 * Called when scene unloads.
			 */
			virtual void _Unload()
			{
			}

			/**
			 * Called once when the scene load and about to be updated by the main loop.
			 * This method guarantees that everything is up and ready, and all managers got started.
			 */
			virtual void _Start()
			{
			}

			/**
			 * Called every frame to do main updates.
			 * Note: called before Draw().
			 * 
			 * \param deltaTime Time passed since last update call.
			 */
			virtual void _Update(double deltaTime)
			{
			}

			/**
			 * Called every frame to draw the scene.
			 * Note: called after Update().
			 */
			virtual void _Draw()
			{
			}

			/**
			 * Called every constant interval to do main updates. Used for physics-related updates.
			 * Note: this is not actually called in real-time constant intervals. instead, it just make sure
			 * to run number of times per second based on the desired fixed update interval. This method may
			 * run several time in a row before calling a single Update(), or alternatively, some Updates() may be
			 * called in a row without FixedUpdate(). It all depends on Update() and Draw() performance.
			 *
			 * \param deltaTime Will always be the Fixed Update Interval set in engine.
			 */
			virtual void _FixedUpdate(double deltaTime)
			{
			}

		protected:

			/**
			 * Get if current scene is the first loaded scene.
			 *
			 * \return If we are in first loaded scene.
			 */
			bool IsFirstScene() const;
		};
	}
}
