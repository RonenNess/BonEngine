/*****************************************************************//**
 * \file   IDiagnostics.h
 * \brief  Interface for the diagnostics manager class.
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "../IManager.h"

namespace bon
{
	namespace diagnostics
	{
		/**
		 * Built in counters we keep track on in diagnostics manager.
		 */
		enum class BON_DLLEXPORT  DiagnosticsCounters
		{
			/**
			 * Draw calls during this frame.
			 */
			 DrawCalls,

			 /**
			  * Play sound calls during this frame.
			  */
			  PlaySoundCalls,

			  /**
			   * Currently loaded assets count.
			   */
			  LoadedAssets,

			  /**
			   * Last built-in counter value.
			   * If you want to add custom counters, start here and go up until 'MaxCounters'
			   */
			  _BuiltInCounterCount,

			  /**
			   * Max counters value.
			   */
			  _MaxCounters = 50,
		};

		/**
		 * Interface for the diagnostics manager.
		 * Used for FPS count and other debug methods.
		 */
		class BON_DLLEXPORT IDiagnostics : public IManager
		{
		public:

			/**
			 * Get FPS count based on last second.
			 * Note: this may not be completely accurate and should only be used for debug purposes.
			 *
			 * \return Current FPS count.
			 */
			virtual int FpsCount() const = 0;

			/**
			 * Get counter value.
			 *
			 * \param counterId Counter id to get.
			 * \return Counter value.
			 */
			inline long GetCounter(DiagnosticsCounters counterId) const { return _GetCounter((int)(counterId)); }

			/**
			 * Increase counter value.
			 *
			 * \param counterId Counter id to get.
			 * \param increaseBy How much to increase counter.
			 */
			inline void IncreaseCounter(DiagnosticsCounters counterId, int increaseBy = 1) { _IncreaseCounter((int)(counterId)); }

			/**
			 * Reset counter value.
			 *
			 * \param counterId Counter id to reset.
			 */
			inline void ResetCounter(DiagnosticsCounters counterId) { _ResetCounter((int)(counterId)); }

			/**
			 * Get counter value.
			 * 
			 * \param counterId Counter id to get.
			 * \return Counter value.
			 */
			virtual long _GetCounter(int counterId) const = 0;

			/**
			 * Increase counter value.
			 *
			 * \param counterId Counter id to get.
			 * \param increaseBy How much to increase counter.
			 */
			virtual void _IncreaseCounter(int counterId, long increaseBy = 1) = 0;

			/**
			 * Reset counter value.
			 *
			 * \param counterId Counter id to reset.
			 */
			virtual void _ResetCounter(int counterId) = 0;

		protected:
			/**
			 * Get manager identifier.
			 */
			virtual const char* _GetId() const override { return "diagnostics"; }
		};
	}
}