/*****************************************************************//**
 * \file   CAPI_Assets.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for assets.
 *
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "CAPI_Defs.h"

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
	 * Save image to file.
	 */
	BON_DLLEXPORT void BON_Image_SaveToFile(bon::ImageAsset* image, const char* filename);

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
	* Get PointF value from config.
	*/
	BON_DLLEXPORT void BON_Config_GetPointF(bon::ConfigAsset* config, const char* section, const char* name, float defaultValX, float defaultValY, float* outX, float* outY);
	
	/**
	* Get RectangleF value from config.
	*/
	BON_DLLEXPORT void BON_Config_GetRectangleF(bon::ConfigAsset* config, const char* section, const char* name, float defaultValX, float defaultValY, float defaultValW, float defaultValH, float* outX, float* outY, float* outW, float* outH);
	
	/**
	* Get Color value from config.
	*/
	BON_DLLEXPORT void BON_Config_GetColor(bon::ConfigAsset* config, const char* section, const char* name, float defaultR, float defaultG, float defaultB, float defaultA, float* outR, float* outG, float* outB, float* outA);

	/**
	* Get option index from config.
	*/
	BON_DLLEXPORT int BON_Config_GetOption(bon::ConfigAsset* config, const char* section, const char* name, const char** options, int optionsCount, int defaultVal);

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
	 * Get if a sound is playing.
	 */
	BON_DLLEXPORT bool BON_Sound_IsPlaying(bon::SoundAsset* sound);

	/**
	 * Get font asset native size.
	 */
	BON_DLLEXPORT int BON_Font_Size(bon::FontAsset* font);

#ifdef __cplusplus
}
#endif