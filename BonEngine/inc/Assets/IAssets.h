/*****************************************************************//**
 * \file   IAssets.h
 * \brief  Interface for the assets manager class.
 * 
 * \author Ronen
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "Types/Image.h"
#include "Types/Music.h"
#include "Types/Sound.h"
#include "Types/Config.h"
#include "Types/Font.h"
#include "../Framework/Point.h"
#include "../IManager.h"
#include "../Framework/Rectangle.h"
#include "../Gfx/Defs.h"

namespace bon
{
	namespace assets
	{
		/**
		 * Interface for the Assets manager.
		 * This manager responsible to load and hold assets cache.
		 */
		class DLLEXPORT IAssets : public IManager
		{
		public:

			/**
			 * Load and return an Image asset.
			 * 
			 * \param filename Image file path.
			 * \param filter Image filtering mode.
			 * \param useCache If true, will try to get asset from cache first. If not found in cache will add to cache after load.
			 * \return Image asset.
			 */
			virtual ImageAsset LoadImage(const char* filename, ImageFilterMode filter = ImageFilterMode::Nearest, bool useCache = true) = 0;

			/**
			 * Creates and return an empty image asset.
			 *
			 * \param size Image size.
			 * \param filter Image filtering mode.
			 * \return Empty image.
			 */
			virtual ImageAsset CreateEmptyImage(const framework::PointI& size, ImageFilterMode filter = ImageFilterMode::Nearest) = 0;

			/**
			 * Load and return a music asset.
			 *
			 * \param filename Music file path.
			 * \param useCache If true, will try to get asset from cache first. If not found in cache will add to cache after load.
			 * \return Image asset.
			 */
			virtual MusicAsset LoadMusic(const char* filename, bool useCache = true) = 0;

			/**
			 * Load and return a sound effect asset.
			 *
			 * \param filename Sound file path.
			 * \param useCache If true, will try to get asset from cache first. If not found in cache will add to cache after load.
			 * \return Image asset.
			 */
			virtual SoundAsset LoadSound(const char* filename, bool useCache = true) = 0;

			/**
			 * Load and return a font asset.
			 *
			 * \param filename Font file path.
			 * \param fontSize Loaded font base size.
			 * \param useCache If true, will try to get asset from cache first. If not found in cache will add to cache after load.
			 * \return Font asset.
			 */
			virtual FontAsset LoadFont(const char* filename, int fontSize = 32, bool useCache = true) = 0;

			/**
			 * Load and return a configuration asset.
			 *
			 * \param filename Config file path.
			 * \param useCache If true, will try to get asset from cache first. If not found in cache will add to cache after load.
			 * \return Config asset.
			 */
			virtual ConfigAsset LoadConfig(const char* filename, bool useCache = true) = 0;

			/**
			 * Create and return an empty configuration file.
			 *
			 * \return Empty config asset.
			 */
			virtual ConfigAsset CreateEmptyConfig() = 0;

			/**
			 * Save configuration file.
			 * 
			 * \param config Config file to save.
			 * \param filename config file path.
			 * \return True if succeed, false otherwise.
			 */
			virtual bool SaveConfig(ConfigAsset config, const char* filename) = 0;

			/**
			 * Clear all assets from cache.
			 * Note: this won't necessarily dispose all assets - assets that are still held in external code will survive.
			 * To free all assets, you need to release all pointers to them.
			 */
			virtual void ClearCache() = 0;

			/**
			 * Get loaded assets count by type.
			 * 
			 * \param type Asset type to get counter for.
			 * \return How many loaded assets we have of this type
			 */
			virtual size_t _GetLoadedAssetsCount(AssetTypes type) const = 0;

			/**
			 * Register custom initializer and disposer to handle asset type.
			 *
			 * \param type Asset type to add initializer to.
			 * \param initializer Initializer method.
			 * \param disposer Disposer method.
			 * \param context Optional context to attach to initialize / dispose calls.
			 */
			virtual void _SetAssetsInitializer(AssetTypes type, AssetInitializer initializer, AssetDisposer disposer, void* context) = 0;
		
		protected:

			/**
			 * Get manager identifier.
			 */
			virtual const char* _GetId() const override { return "assets"; }
		};
	}
}