#pragma once

/**
 * Write debug log in an efficient way (will only evaluate arguments if log level is active).
 */
#define BON_DLOG(msg, ...) if (bon::_GetEngine().Log().IsValid(bon::LogLevel::Debug)) bon::_GetEngine().Log().Write(bon::LogLevel::Debug, msg, __VA_ARGS__)

/**
* Write info log in an efficient way (will only evaluate arguments if log level is active).
*/
#define BON_ILOG(msg, ...) if (bon::_GetEngine().Log().IsValid(bon::LogLevel::Info)) bon::_GetEngine().Log().Write(bon::LogLevel::Info, msg, __VA_ARGS__)

/**
* Write warning log in an efficient way (will only evaluate arguments if log level is active).
*/
#define BON_WLOG(msg, ...) if (bon::_GetEngine().Log().IsValid(bon::LogLevel::Warn)) bon::_GetEngine().Log().Write(bon::LogLevel::Warn, msg, __VA_ARGS__)

/**
* Write error log in an efficient way (will only evaluate arguments if log level is active).
*/
#define BON_ELOG(msg, ...) if (bon::_GetEngine().Log().IsValid(bon::LogLevel::Error)) bon::_GetEngine().Log().Write(bon::LogLevel::Error, msg, __VA_ARGS__)

/**
* Write critical log in an efficient way (will only evaluate arguments if log level is active).
*/
#define BON_CLOG(msg, ...) if (bon::_GetEngine().Log().IsValid(bon::LogLevel::Critical)) bon::_GetEngine().Log().Write(bon::LogLevel::Critical, msg, __VA_ARGS__)