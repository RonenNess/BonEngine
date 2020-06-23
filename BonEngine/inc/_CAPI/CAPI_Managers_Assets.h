/*****************************************************************//**
 * \file   CAPI_Managers_Assets.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for assets manager.
 *
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "../BonEngine.h"
#include "CAPI_Assets.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* Load and return an Image asset.
	*/
	BON_DLLEXPORT bon::ImageAsset* BON_Assets_LoadImage(const char* filename, BON_ImageFilterMode filter, bool useCache);

	/**
	* Creates and return an empty image asset.
	*/
	BON_DLLEXPORT bon::ImageAsset* BON_Assets_CreateEmptyImage(int x, int y, BON_ImageFilterMode filter);

	/**
	* Load and return a music asset.
	*/
	BON_DLLEXPORT bon::MusicAsset* BON_Assets_LoadMusic(const char* filename, bool useCache);

	/**
	* Load and return a sound effect asset.
	*/
	BON_DLLEXPORT bon::SoundAsset* BON_Assets_LoadSound(const char* filename, bool useCache);

	/**
	* Load and return a font asset.
	*/
	BON_DLLEXPORT bon::FontAsset* BON_Assets_LoadFont(const char* filename, int fontSize, bool useCache);

	/**
	* Load and return a configuration asset.
	*/
	BON_DLLEXPORT bon::ConfigAsset* BON_Assets_LoadConfig(const char* filename, bool useCache);

	/**
	* Create and return an empty configuration file.
	*/
	BON_DLLEXPORT bon::ConfigAsset* BON_Assets_CreateEmptyConfig();

	/**
	* Release an asset pointer, created by one of the getter methods.
	*/
	BON_DLLEXPORT void BON_Assets_FreeAssetPointer(bon::AssetPtr* asset);

	/**
	* Save configuration file.
	*/
	BON_DLLEXPORT bool BON_Assets_SaveConfig(bon::ConfigAsset* config, const char* filename);

	/**
	* Clear all assets from cache.
	*/
	BON_DLLEXPORT void BON_Assets_ClearCache();

#ifdef __cplusplus
}
#endif