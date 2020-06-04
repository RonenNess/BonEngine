#include <Diagnostics/Diagnostics.h>
#include <BonEngine.h>
#include <Engine/Engine.h>


namespace bon
{
	namespace diagnostics
	{
		// do updates
		void Diagnostics::_Update(double deltaTime)
		{
			// reset counters
			ResetCounter(DiagnosticsCounters::DrawCalls);
			ResetCounter(DiagnosticsCounters::PlaySoundCalls);

			// to count seconds
			static double secondsCount = 0.0;
			secondsCount += deltaTime;

			// count fps
			_currFpsCount++;
			if (secondsCount >= 1.0) {
				_lastFpsCount = _currFpsCount;
				_currFpsCount = 0;
				secondsCount = 0.0;
			}
		}

		// get counter value
		long Diagnostics::_GetCounter(int counterId) const
		{
			return _counters[counterId];
		}

		// increase counter value
		void Diagnostics::_IncreaseCounter(int counterId, long increaseBy)
		{
			_counters[counterId] += increaseBy;
		}

		// reset counter value
		void Diagnostics::_ResetCounter(int counterId)
		{
			_counters[counterId] = 0;
		}
	}
}