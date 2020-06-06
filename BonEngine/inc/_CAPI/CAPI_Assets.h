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

#ifdef __cplusplus
}
#endif