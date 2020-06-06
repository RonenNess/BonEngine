/*****************************************************************//**
 * \file   CAPI_Assets.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for assets.
 *
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include <BonEngine.h>

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* Check if an asset is valid.
	*/
	BON_DLLEXPORT bool BON_Asset_IsValid(bon::AssetPtr* asset);

	/**
	 * Get asset's path.
	 */
	BON_DLLEXPORT const char* BON_Asset_Path(bon::AssetPtr* asset);

	// CAPI export of image filters
	BON_DLLEXPORT enum BON_ImageFilterMode
	{
		BON_Filter_Nearest = bon::ImageFilterMode::Nearest,
		BON_Filter_Linear = bon::ImageFilterMode::Linear,
		BON_Filter_Anisotropic = bon::ImageFilterMode::Anisotropic,
		BON_Filter__Count = bon::ImageFilterMode::_Count,
	};

	/**
	 * Get image filtering mode.
	 */
	BON_DLLEXPORT BON_ImageFilterMode BON_Image_FilteringMode(bon::ImageAsset* image);

	/**
	 * Get image width.
	 */
	BON_DLLEXPORT int BON_Image_Width(bon::ImageAsset* image);

	/**
	 * Get image height.
	 */
	BON_DLLEXPORT int BON_Image_Height(bon::ImageAsset* image);

	/**
	* Get string value from config.
	*/
	BON_DLLEXPORT const char* BON_Config_GetStr(bon::ConfigAsset* config, const char* section, const char* name, const char* defaultVal);

	/**
	* Get bool value from config.
	*/
	BON_DLLEXPORT bool BON_Config_GetBool(bon::ConfigAsset* config, const char* section, const char* name, bool defaultVal);

	/**
	* Get integer value from config.
	*/
	BON_DLLEXPORT long BON_Config_GetInt(bon::ConfigAsset* config, const char* section, const char* name, int defaultVal);

	/**
	* Get float value from config.
	*/
	BON_DLLEXPORT float BON_Config_GetFloat(bon::ConfigAsset* config, const char* section, const char* name, float defaultVal);

	/**
	* Get section name by index.
	*/
	BON_DLLEXPORT const char* BON_Config_Section(bon::ConfigAsset* config, int index);

	/**
	 * Get config sections count.
	 */
	BON_DLLEXPORT int BON_Config_SectionsCount(bon::ConfigAsset* config);

	/**
	* Get a key name by index.
	*/
	BON_DLLEXPORT const char* BON_Config_Key(bon::ConfigAsset* config, const char* section, int index);

	/**
	* Get config keys count.
	*/
	BON_DLLEXPORT int BON_Config_KeysCount(bon::ConfigAsset* config, const char* section);

	/**
	* Set a value.
	*/
	BON_DLLEXPORT void BON_Config_SetValue(bon::ConfigAsset* config, const char* section, const char* key, const char* value);

	/**
	* Removes a key.
	*/
	BON_DLLEXPORT void BON_Config_RemoveKey(bon::ConfigAsset* config, const char* section, const char* key);

	/**
	* Get music track length.
	*/
	BON_DLLEXPORT float BON_Music_Length(bon::MusicAsset* music);

	/**
	* Get sound track length.
	*/
	BON_DLLEXPORT float BON_Sound_Length(bon::SoundAsset* sound);

	/**
	 * Get if a sound is playing..
	 */
	BON_DLLEXPORT bool BON_Sound_IsPlaying(bon::SoundAsset* sound);

#ifdef __cplusplus
}
#endif