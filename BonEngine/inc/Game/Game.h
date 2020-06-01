/*****************************************************************//**
 * \file   Game.h
 * \brief  The default game manager implemented by BonEngine.
 * 
 * \author Ronen
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "IGame.h"

namespace bon
{
	namespace game
	{
		/**
		 * Default game manager.
		 */
		class Game : public IGame
		{
		private:
			// total game elapsed time
			double _elapsedTime = 0.0;

			// to count fps
			int _currFpsCount = 0;
			int _lastFpsCount = 0;

		protected:

			/**
			 * Initialize manager when engine starts.
			 */
			virtual void _Initialize() override;

			/**
			 * Clear / free this manager's resources.
			 */
			virtual void _Dispose() override;

			/**
			 * Called every frame.
			 */
			virtual void _Update(double deltaTime) override;

			/**
			 * Called when main loop starts.
			 */
			virtual void _Start() override;

		public:

			/**
			 * Exit game.
			 */
			virtual void Exit() override;

			/**
			 * Change active scene.
			 */
			virtual void ChangeScene(engine::Scene& scene) override;

			/**
			 * Load game config from ini file and setup everything accordingly.
			 * Note: should be called before main loop starts.
			 *
			 * \param path ini file path.
			 */
			virtual void LoadConfig(const char* path) override;

			/**
			 * Get total elapsed time, in seconds.
			 *
			 * \return Total elapsed time.
			 */
			virtual double ElapsedTime() const override { return _elapsedTime; }

			/**
			 * Get FPS count based on last second.
			 * Note: this may not be completely accurate and should only be used for debug purposes.
			 *
			 * \return Current FPS count.
			 */
			virtual int FpsCount() const { return _lastFpsCount; }
		};
	}
}