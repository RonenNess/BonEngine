/*****************************************************************//**
 * \file   Config.h
 * \brief  Define a config file asset.
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../../dllimport.h"
#include "IAsset.h"
#include "../Defs.h"
#include "../../Framework/PointF.h"
#include "../../Framework/Color.h"
#include "../../Framework/RectangleF.h"
#include <string>
#include <set>
#include "ConfigHandle.h"


namespace bon
{
	namespace assets
	{
		/**
		 * A configuration asset.
		 * Used to read config from user.
		 */
		class _Config : public IAsset
		{
		public:

			/**
			 * Get configuration handle.
			 *
			 * \return Config handle.
			 */
			inline _ConfigHandle* Handle() { return (_ConfigHandle*)_untypedHandle; }

			/**
			 * Get configuration handle.
			 *
			 * \return Config handle.
			 */
			inline const _ConfigHandle* Handle() const { return (const _ConfigHandle*)_untypedHandle; }

			/**
			 * Create the asset.
			 *
			 * \param path Asset's path.
			 */
			_Config(const char* path) : IAsset(path) { }

			/**
			 * Return if this asset is properly loaded / valid.
			 */
			virtual bool IsValid() const override
			{
				return _untypedHandle != nullptr && Handle()->IsValid();
			}

			/**
			 * Get asset type.
			 *
			 * \return Asset type identifier.
			 */
			virtual AssetTypes AssetType() const override { return AssetTypes::Config; }

			/**
			 * Get string value from config.
			 *
			 * \param section Config sectionname.
			 * \param name Config name.
			 * \param defaultVal Default value to retrieve if not found.
			 * \return Config value as string.
			 */
			const char* GetStr(const char* section, const char* name, const char* defaultVal) const { return Handle()->GetStr(section, name, defaultVal); }

			/**
			 * Get bool value from config.
			 *
			 * \param section Config section name.
			 * \param name Config name.
			 * \param defaultVal Default value to retrieve if not found.
			 * \return Config value as boolean.
			 */
			bool GetBool(const char* section, const char* name, bool defaultVal) const { return Handle()->GetBool(section, name, defaultVal); }

			/**
			 * Get integer value from config.
			 *
			 * \param section Config section name.
			 * \param name Config name.
			 * \param defaultVal Default value to retrieve if not found.
			 * \return Config value as integer.
			 */
			long GetInt(const char* section, const char* name, int defaultVal) const { return Handle()->GetInt(section, name, defaultVal); }

			/**
			 * Get float value from config.
			 *
			 * \param section Config section name.
			 * \param name Config name.
			 * \param defaultVal Default value to retrieve if not found.
			 * \return Config value as float.
			 */
			float GetFloat(const char* section, const char* name, float defaultVal) const { return Handle()->GetFloat(section, name, defaultVal); }

			/**
			 * Get point value from config (format: "x,y").
			 * 
			 * \param section Config section name.
			 * \param name Config name.
			 * \param defaultVal Default value to retrieve if not found.
			 * \return Config value as PointF.
			 */
			framework::PointF GetPointF(const char* section, const char* name, const framework::PointF& defaultVal) const;

			/**
			 * Get rectanlge value from config (format: "x,y,w,h").
			 *
			 * \param section Config section name.
			 * \param name Config name.
			 * \param defaultVal Default value to retrieve if not found.
			 * \return Config value as RectangleF.
			 */
			framework::RectangleF GetRectangleF(const char* section, const char* name, const framework::RectangleF& defaultVal) const;

			/**
			 * Get color value from config (format: "r,g,b,a" where values range from 0 to 255).
			 *
			 * \param section Config section name.
			 * \param name Config name.
			 * \param defaultVal Default value to retrieve if not found.
			 * \return Config value as Color.
			 */
			framework::Color GetColor(const char* section, const char* name, const framework::Color& defaultVal) const;

			/**
			 * Get set with all section names.
			 */
			const std::set<std::string>& Sections() const { return Handle()->Sections(); }

			/**
			 * Get set with all keys in section.
			 */
			const std::set<std::string>& Keys(const char* section) const { return Handle()->Keys(section); }

			/**
			 * Set a value.
			 *
			 * \param section Section name.
			 * \param key Key name.
			 * \param value New value to set.
			 */
			void SetValue(const char* section, const char* key, const char* value) { Handle()->UpdateValue(section, key, value); }

			/**
			 * Removes a key.
			 *
			 * \param section Section name.
			 * \param key Key name.
			 */
			void RemoveKey(const char* section, const char* key) { Handle()->RemoveKey(section, key); }

			/**
			 * Save configuration to file.
			 * Note: don't call this directly, use Assets() method, as the asset manager may need to manipulate the path.
			 *
			 * \param filename Config file path.
			 * \return True if succeed, false otherwise.
			 */
			bool _SaveToFile(const char* filename) const { return Handle()->SaveConfig(filename); }
		};
	}
}