/*****************************************************************//**
 * \file   Log.h
 * \brief  The default log manager implemented by BonEngine.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "ILog.h"
#include <stdio.h>


namespace bon
{
	namespace log
	{
		/**
		 * Default log manager.
		 */
		class Log : public ILog
		{
		private:
			// current log level
			LogLevel _level = LogLevel::Debug;

			// log file
			FILE* _logFile = nullptr;

			// last tick time, so we'll update time signature only when needed
			unsigned long long _lastTick = 0;

			// time until next time we force flushing log file, so we won't lose data due to crashes.
			double _timeForNextFlush = 1;

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
			 * Write log message.
			 *
			 * \param fmt Message text.
			 * \param Params for message text.
			 */
			virtual void Write(LogLevel level, const char* fmt, ...) override;

			/**
			 * Set logs level.
			 *
			 * \param level New logs level.
			 */
			virtual void SetLevel(LogLevel level) override { _level = level; }

			/**
			 * Get current log level.
			 *
			 * \return Current log level.
			 */
			virtual LogLevel GetLevel() const override { return _level; }

			/**
			 * Get if a given log level is valid and will be written to file / screen if set.
			 *
			 * \param level Log level to test.
			 * \return True if log level is valid for current log level.
			 */
			virtual bool IsValid(LogLevel level) const;

		private:

			/**
			 * Close log file, if opened.
			 */
			void CloseLogFile();

			/**
			 * Flush log file, if exists.
			 */
			void FlushLogFile();

			/**
			 * Update timestamp text.
			 */
			void UpdateTimeStamp();
		};
	}
}