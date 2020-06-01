/*****************************************************************//**
 * \file   ILog.h
 * \brief  Interface for the log manager class.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "../IManager.h"
#include "LogMacros.h"

namespace bon
{
	namespace log
	{
		/**
		 * Log levels.
		 */
		enum class DLLEXPORT LogLevel
		{
			None = -1,
			Debug = 0,
			Info = 1,
			Warn = 2,
			Error = 3,
			Critical = 4,
		};

		/**
		 * Interface for the log manager.
		 * Used basically for console prints and logging.
		 */
		class DLLEXPORT ILog : public IManager
		{
		public:
			/**
			 * Write log message.
			 * 
			 * \param fmt Message text.
			 * \param Params for message text.
			 */
			virtual void Write(LogLevel level, const char* fmt, ...) = 0;

			/**
			 * Set logs level.
			 * 
			 * \param level New logs level.
			 */
			virtual void SetLevel(LogLevel level) = 0;

			/**
			 * Get current log level.
			 * 
			 * \return Current log level.
			 */
			virtual LogLevel GetLevel() const = 0;

			/**
			 * Get if a given log level is valid and will be written to file / screen if set.
			 * 
			 * \param level Log level to test.
			 * \return True if log level is valid for current log level.
			 */
			virtual bool IsValid(LogLevel level) const = 0;
		
		protected:

			/**
			 * Get manager identifier.
			 */
			virtual const char* _GetId() const override { return "log"; }
		};
	}
}