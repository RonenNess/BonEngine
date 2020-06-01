/*****************************************************************//**
 * \file   ConfigHandle.h
 * \brief  Define a config file handle.
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../../dllimport.h"
#include "IAsset.h"
#include "../Defs.h"
#include <string>
#include <set>

namespace bon
{
	namespace assets
	{
		/**
		 * Define the interface for a configuration internal handle.
		 * To create new config asset types, you must implement this API.
		 */
		class DLLEXPORT _ConfigHandle
		{
		public:
			/**
			 * Get if this config file is valid.
			 *
			 * \return If config is valid.
			 */
			virtual bool IsValid() const = 0;

			/**
			 * Get string value from config.
			 *
			 * \param section Config sectionname.
			 * \param name Config name.
			 * \param defaultVal Default value to retrieve if not found.
			 * \return Config value as string.
			 */
			virtual const char* GetStr(const char* section, const char* name, const char* defaultVal) const = 0;

			/**
			 * Get bool value from config.
			 *
			 * \param section Config section name.
			 * \param name Config name.
			 * \param defaultVal Default value to retrieve if not found.
			 * \return Config value as boolean.
			 */
			virtual bool GetBool(const char* section, const char* name, bool defaultVal) const = 0;

			/**
			 * Get integer value from config.
			 *
			 * \param section Config section name.
			 * \param name Config name.
			 * \param defaultVal Default value to retrieve if not found.
			 * \return Config value as integer.
			 */
			virtual long GetInt(const char* section, const char* name, int defaultVal) const = 0;

			/**
			 * Get float value from config.
			 *
			 * \param section Config section name.
			 * \param name Config name.
			 * \param defaultVal Default value to retrieve if not found.
			 * \return Config value as float.
			 */
			virtual float GetFloat(const char* section, const char* name, float defaultVal) const = 0;

			/**
			 * Get set with all section names.
			 */
			virtual const std::set<std::string>& Sections() const = 0;

			/**
			 * Get set with all keys in section.
			 */
			virtual const std::set<std::string>& Keys(const char* section) const = 0;

			/**
			 * Sets a value.
			 *
			 * \param section Section name.
			 * \param key Key name.
			 * \param value New value to set.
			 */
			virtual void UpdateValue(const char* section, const char* key, const char* value) = 0;

			/**
			 * Removes a key.
			 *
			 * \param section Section name.
			 * \param key Key name.
			 */
			virtual void RemoveKey(const char* section, const char* key) = 0;

			/**
			 * Save configuration to file.
			 *
			 * \param filename Config file path.
			 * \return True if succeed, false otherwise.
			 */
			virtual bool SaveConfig(const char* filename) const = 0;
		};
	}
}