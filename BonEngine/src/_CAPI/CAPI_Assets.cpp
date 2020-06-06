#include <_CAPI/CAPI_Assets.h>
#include <BonEngine.h>
#include <set>

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


/**
* Get string value from config.
*/
const char* BON_Config_GetStr(bon::ConfigAsset* config, const char* section, const char* name, const char* defaultVal)
{
	return (*config)->GetStr(section, name, defaultVal);
}

/**
* Get bool value from config.
*/
bool BON_Config_GetBool(bon::ConfigAsset* config, const char* section, const char* name, bool defaultVal)
{
	return (*config)->GetBool(section, name, defaultVal);
}

/**
* Get integer value from config.
*/
long BON_Config_GetInt(bon::ConfigAsset* config, const char* section, const char* name, int defaultVal)
{
	return (*config)->GetInt(section, name, defaultVal);
}

/**
* Get float value from config.
*/
float BON_Config_GetFloat(bon::ConfigAsset* config, const char* section, const char* name, float defaultVal)
{
	return (*config)->GetFloat(section, name, defaultVal);
}

/**
* Get section name by index.
*/
const char* BON_Config_Section(bon::ConfigAsset* config, int index)
{
	const std::set<std::string>& sections = (*config)->Sections();
	return std::next(sections.begin(), index)->c_str();
}

/**
 * Get secions count. 
 */
int BON_Config_SectionsCount(bon::ConfigAsset* config)
{
	return (*config)->Sections().size();
}

/**
* Get set with all keys in section.
*/
const char* BON_Config_Key(bon::ConfigAsset* config, const char* section, int index)
{
	const std::set<std::string>& keys = (*config)->Keys(section);
	return std::next(keys.begin(), index)->c_str();
}

/**
 * Get config keys count.
 */
int BON_Config_KeysCount(bon::ConfigAsset* config, const char* section)
{
	return (*config)->Keys(section).size();
}

/**
* Set a value.
*/
void BON_Config_SetValue(bon::ConfigAsset* config, const char* section, const char* key, const char* value)
{
	(*config)->SetValue(section, key, value);
}

/**
* Removes a key.
*/
void BON_Config_RemoveKey(bon::ConfigAsset* config, const char* section, const char* key)
{
	(*config)->RemoveKey(section, key);
}