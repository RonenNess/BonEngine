/*****************************************************************//**
 * \file   Exceptions.h
 * \brief  Define exceptions used by BonEngine.
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include <exception>
#include "../dllimport.h"
using namespace std;

namespace bon
{
	namespace framework
	{
		/**
		 * Invalid state exception - happens when user tries to do something he's not supposed to do at a given time.
		 * Can also happen due to internal errors, if something's state gets corrupted.
		 */
		class InvalidState : public exception
		{
			const char* _msg;

		public:
			InvalidState(const char* msg) : _msg(msg) { }
			virtual const char* what() const throw()
			{
				return _msg;
			}
		};

		/**
		 * Initialize error - happens when something during initialization don't work for unknown reason.
		 */
		class InitializeError : public exception
		{
			const char* _msg;

		public:
			InitializeError(const char* msg) : _msg(msg) { }
			virtual const char* what() const throw()
			{
				return _msg;
			}
		};

		/**
		 * Called when failing to load an asset for whatever reason.
		 */
		class AssetLoadError : public exception
		{
			const char* _msg;

		public:
			AssetLoadError(const char* msg) : _msg(msg) { }
			virtual const char* what() const throw()
			{
				return _msg;
			}
		};
	}
}