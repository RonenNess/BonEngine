/*****************************************************************//**
 * \file   Diagnostics.h
 * \brief  The default diagnostics manager implemented by BonEngine.
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "IDiagnostics.h"
#include <stdio.h>


namespace bon
{
	namespace diagnostics
	{
		/**
		 * Default diagnostics manager.
		 */
		class Diagnostics : public IDiagnostics
		{
		private:
			// to count fps
			int _currFpsCount = 0;
			int _lastFpsCount = 0;

			// for counters
			long _counters[(int)DiagnosticsCounters::_MaxCounters] = { 0 };

		protected:
			/**
			 * Called every frame.
			 */
			virtual void _Update(double deltaTime) override;

		public:

			/**
			 * Get FPS count based on last second.
			 * Note: this may not be completely accurate and should only be used for debug purposes.
			 *
			 * \return Current FPS count.
			 */
			virtual int FpsCount() const { return _lastFpsCount; }

			/**
			 * Get counter value.
			 *
			 * \param counterId Counter id to get.
			 * \return Counter value.
			 */
			virtual long _GetCounter(int counterId) const override;

			/**
			 * Increase counter value.
			 *
			 * \param counterId Counter id to get.
			 * \param increaseBy How much to increase counter.
			 */
			virtual void _IncreaseCounter(int counterId, long increaseBy = 1) override;

			/**
			 * Reset counter value.
			 *
			 * \param counterId Counter id to reset.
			 */
			virtual void _ResetCounter(int counterId) override;
		};
	}
}