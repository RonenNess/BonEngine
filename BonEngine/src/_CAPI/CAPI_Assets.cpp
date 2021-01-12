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

// get if image have alpha channels.
bool BON_Image_HaveAlphaChannel(bon::ImageAsset* image)
{
	return (*image)->HaveAlphaChannel();
}

// Save image to file.
void BON_Image_SaveToFile(bon::ImageAsset* image, const char* filename)
{
	(*image)->SaveToFile(filename);
}

// Prepare image for reading pixels from it.
void BON_Image_PrepareReadingBuffer(bon::ImageAsset* image, int x, int y, int w, int h)
{
	(*image)->PrepareReadingBuffer(bon::framework::RectangleI(x, y, w, h));
}

// Free reading buffer after PrepareReadingBuffer() was called.
void BON_Image_FreeReadingBuffer(bon::ImageAsset* image)
{
	(*image)->FreeReadingBuffer();
}

// Clear image to transparent pixels.
void BON_Image_Clear(bon::ImageAsset* image)
{
	(*image)->Clear();
}

// get pixel from image
void BON_Image_GetPixel(bon::ImageAsset* image, int x, int y, float* r, float* g, float* b, float* a)
{
	bon::Color ret = (*image)->GetPixel(bon::PointI(x, y));
	*r = ret.R;
	*g = ret.G;
	*b = ret.B;
	*a = ret.A;
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
* Get PointF value from config.
*/
void BON_Config_GetPointF(bon::ConfigAsset* config, const char* section, const char* name, float defaultValX, float defaultValY, float* outX, float* outY)
{
	bon::PointF ret = (*config)->GetPointF(section, name, bon::PointF(defaultValX, defaultValY));
	(*outX) = ret.X;
	(*outY) = ret.Y;
}

/**
* Get RectangleF value from config.
*/
void BON_Config_GetRectangleF(bon::ConfigAsset* config, const char* section, const char* name, float defaultValX, float defaultValY, float defaultValW, float defaultValH, float* outX, float* outY, float* outW, float* outH)
{
	bon::RectangleF ret = (*config)->GetRectangleF(section, name, bon::RectangleF(defaultValX, defaultValY, defaultValW, defaultValH));
	(*outX) = ret.X;
	(*outY) = ret.Y;
	(*outW) = ret.Width;
	(*outH) = ret.Height;
}

/**
* Get Color value from config.
*/
void BON_Config_GetColor(bon::ConfigAsset* config, const char* section, const char* name, float defaultR, float defaultG, float defaultB, float defaultA, float* outR, float* outG, float* outB, float* outA)
{
	bon::Color ret = (*config)->GetColor(section, name, bon::Color(defaultR, defaultG, defaultB, defaultA));
	(*outR) = ret.R;
	(*outG) = ret.G;
	(*outB) = ret.B;
	(*outA) = ret.A;
}

/**
* Get option index from config.
*/
BON_DLLEXPORT int BON_Config_GetOption(bon::ConfigAsset* config, const char* section, const char* name, const char** options, int optionsCount, int defaultVal)
{
	return (*config)->GetOption(section, name, options, optionsCount, defaultVal);
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
	return (int)((*config)->Sections().size());
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
	return (int)((*config)->Keys(section).size());
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

/**
* Checks if a section exists.
*/
bool BON_Config_SectionExists(bon::ConfigAsset* config, const char* section)
{
	return (*config)->Exists(section);
}

/**
* Checks if a key exists.
*/
bool BON_Config_KeyExists(bon::ConfigAsset* config, const char* section, const char* key)
{
	return (*config)->Exists(section, key);
}

// Get music track length.
float BON_Music_Length(bon::MusicAsset* music)
{
	return (*music)->Length();
}

// Get sound track length.
float BON_Sound_Length(bon::SoundAsset* sound)
{
	return (*sound)->Length();
}

// Get if a sound is playing.
bool BON_Sound_IsPlaying(bon::SoundAsset* sound)
{
	return (*sound)->IsPlaying();
}

/**
* Get font asset native size.
*/
int BON_Font_Size(bon::FontAsset* font)
{
	return (*font)->FontSize();
}

/**
 * Get if effect is valid
 */
bool BON_Effect_IsValid(bon::EffectAsset* effect)
{
	return (*effect)->IsValid();
}

/**
 * Return if this effect uses textures.
 */
bool BON_Effect_UseTextures(bon::EffectAsset* effect)
{
	return (*effect)->UseTextures();
}

/**
 * Return if this effect uses vertex color.
 */
bool BON_Effect_UseVertexColor(bon::EffectAsset* effect)
{
	return (*effect)->UseVertexColor();
}

/**
 * Set effect uniform.
 */
void BON_Effect_SetUniformFloat(bon::EffectAsset* effect, const char* name, float val)
{
	(*effect)->SetUniformFloat(name, val);
}

/**
 * Set effect uniform.
 */
void BON_Effect_SetUniformVector2(bon::EffectAsset* effect, const char* name, float x, float y)
{
	(*effect)->SetUniformVector2(name, x, y);
}

/**
 * Set effect uniform.
 */
void BON_Effect_SetUniformVector3(bon::EffectAsset* effect, const char* name, float x, float y, float z)
{
	(*effect)->SetUniformVector3(name, x, y, z);
}

/**
 * Set effect uniform.
 */
void BON_Effect_SetUniformVector4(bon::EffectAsset* effect, const char* name, float x, float y, float z, float w)
{
	(*effect)->SetUniformVector4(name, x, y, z, w);
}

/**
 * Set effect uniform.
 */
void BON_Effect_SetUniformInt(bon::EffectAsset* effect, const char* name, int val)
{
	(*effect)->SetUniformInt(name, val);
}

/**
 * Set effect uniform.
 */
void BON_Effect_SetUniformVector2i(bon::EffectAsset* effect, const char* name, int x, int y)
{
	(*effect)->SetUniformVector2(name, x, y);
}

/**
 * Set effect uniform.
 */
void BON_Effect_SetUniformVector3i(bon::EffectAsset* effect, const char* name, int x, int y, int z)
{
	(*effect)->SetUniformVector3(name, x, y, z);
}

/**
 * Set effect uniform.
 */
void BON_Effect_SetUniformVector4i(bon::EffectAsset* effect, const char* name, int x, int y, int z, int w)
{
	(*effect)->SetUniformVector4(name, x, y, z, w);
}

/**
 * Set effect uniform.
 */
void BON_Effect_SetUniformMatrix2(bon::EffectAsset* effect, const char* name, int count, bool transpose, const float* values)
{
	(*effect)->SetUniformMatrix2(name, count, transpose, values);
}

/**
 * Set effect uniform.
 */
void BON_Effect_SetUniformMatrix3(bon::EffectAsset* effect, const char* name, int count, bool transpose, const float* values)
{
	(*effect)->SetUniformMatrix3(name, count, transpose, values);
}

/**
 * Set effect uniform.
 */
void BON_Effect_SetUniformMatrix4(bon::EffectAsset* effect, const char* name, int count, bool transpose, const float* values)
{
	(*effect)->SetUniformMatrix4(name, count, transpose, values);
}