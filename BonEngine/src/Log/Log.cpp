#include <Log/Log.h>
#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <Sysinfoapi.h>

namespace bon
{
	namespace log
	{
		// init log manager
		void Log::_Initialize()
		{
			// already init? skip
			if (_logFile) {
				return;
			}

			// open log file
			fopen_s(&_logFile, "_log.txt", "w");
		}

		// dispose log resources
		void Log::_Dispose()
		{
			Write(LogLevel::Info, "Destroying debug manager - there will be no more logs after this line.");
			FlushLogFile();
			CloseLogFile();
		}
		
		// do updates
		void Log::_Update(double deltaTime)
		{
			_timeForNextFlush -= deltaTime;
			if (_timeForNextFlush < 0) {
				_timeForNextFlush = 1.5;
				FlushLogFile();
			}
		}

		// called on main loop start
		void Log::_Start()
		{
		}

		// update timestamp text for log messages
		char curr_time_stamp[80];
		void Log::UpdateTimeStamp()
		{
			time_t rawtime;
			struct tm timeinfo;

			time(&rawtime);
			localtime_s(&timeinfo, &rawtime);

			strftime(curr_time_stamp, sizeof(curr_time_stamp), "%d-%m-%Y %H:%M:%S", &timeinfo);
		}

		// flush log file, if exists
		void Log::FlushLogFile()
		{
			if (_logFile) {
				fflush(_logFile);
			}
		}

		// close log file
		void Log::CloseLogFile()
		{
			if (_logFile) {
				fclose(_logFile);
				_logFile = nullptr;
			}
		}

		// check if given log lvel is valid
		bool Log::IsValid(LogLevel level) const
		{
			if (level == LogLevel::None || _level == LogLevel::None || _level > level) {
				return false;
			}
			return true;
		}

		// flush log file
		void Log::Flush()
		{
			FlushLogFile();
		}

		// write log
		void Log::Write(LogLevel level, const char* fmt, ...)
		{
			// convert log level to severity string
			static const char* severity_names[] = {
				"Debug",
				"Info",
				"Warn",
				"Error",
				"Critical"
			};

			// validate log level
			if (!IsValid(level)) {
				return;
			}

			// get current tick and check if need to update timestamp
			auto currTick = GetTickCount64();
			if (currTick != _lastTick) {
				_lastTick = currTick;
				UpdateTimeStamp();
			}

			// start iterating arguments
			va_list arg;
			va_start(arg, fmt);

			// write to log
			if (_logFile) {
				fprintf_s(_logFile, "%s %s>  ", curr_time_stamp, severity_names[(int)level]);
				vfprintf(_logFile, fmt, arg);
				fprintf_s(_logFile, "\n");
			}

			// write to console
			printf_s("%s %s>  ", curr_time_stamp, severity_names[(int)level]);
			vprintf(fmt, arg);
			printf_s("\n");

			// end iterating args
			va_end(arg);

			// in debug mode, flush immediately
			#ifdef _DEBUG
				FlushLogFile();
			#endif
		}
	}
}