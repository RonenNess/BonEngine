/*****************************************************************//**
 * \file   Game.h
 * \brief  The default game manager implemented by BonEngine.
 * 
 * \author Ronen Ness
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

			// current delta time
			double _deltaTime = 0.0;

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
			 * \param path Config (ini file) path.
			 *				* config may contain the following section:
			 *				*	[gfx]
			 *				*		- title = Window title.
			 *				*		- resolution = Window resolution (x,y). Use 0 values to take fullscreen.
			 *				*		- window_mode = How window starts: windowed / windowed_borderless / fullscreen.
			 *				*		- cursor = Show / hide cursor (true/false).
			 *				*	[sfx]
			 *				*		- frequency = Sound frequency. Use 22050 for a nice balanced default.
			 *				*		- format = Sound tracks format: U8 / S8 / U16LSB / S16LSB / U16MSB / S16MSB.
			 *				*		- stereo = Enable stereo (true/false).
			 *				*		- audio_chunk_size = Size of chunks to divide sound tracks into. Smaller value = more responsive sound at the price of CPU. 2048 or 4096 are good defaults.
			 *				*	[input]
			 *				*		- list of key = action binds to set input keys. For example:
			 *				*				KeyLeft=left                    ; will map left key to action "left"
			 *				*				KeyA=left                       ; will map 'a' key to action "left"
			 *				*				KeyRight=right                  ; will map right key to action "right"
			 *				*				KeyD=right                      ; will map 'd' key to action "right"
			 */
			virtual void LoadConfig(const char* path) override;

			/**
			 * Get total elapsed time, in seconds.
			 *
			 * \return Total elapsed time.
			 */
			virtual double ElapsedTime() const override { return _elapsedTime; }

			/**
			 * Get current frame delta time, in seconds.
			 *
			 * \return Delta time.
			 */
			virtual double DeltaTime() const override { return _deltaTime; }
		};
	}
}