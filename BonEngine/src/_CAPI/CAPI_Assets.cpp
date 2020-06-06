#include <_CAPI/CAPI_Assets.h>
#include <BonEngine.h>

// Check if an asset is valid.
bool BON_Asset_IsValid(bon::AssetPtr* asset)
{
	return (*asset)->IsValid();
}

// Get asset's path.
const char* BON_Asset_Path(bon::AssetPtr* asset)
{
	return (*asset)->Path();
}

// Get image filtering mode.
BON_ImageFilterMode BON_Image_FilteringMode(bon::ImageAsset* image)
{
	return (BON_ImageFilterMode)(*image)->FilteringMode();
}

// Get image width
int BON_Image_Width(bon::ImageAsset* image)
{
	return (*image)->Width();
}

// Get image height
int BON_Image_Height(bon::ImageAsset* image)
{
	return (*image)->Height();
}