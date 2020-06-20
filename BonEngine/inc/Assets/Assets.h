/*****************************************************************//**
 * \file   Assets.h
 * \brief  The default assets manager implemented by BonEngine.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "IAssets.h"
#include <unordered_map>
#include <string>

namespace bon
{
	namespace assets
	{
		// forward declare internal helper class
		class AssetsLoaderCode;

		/**
		 * Default assets manager.
		 */
		class Assets : public IAssets
		{
			friend class AssetsLoaderCode;

		private:
			// per-type initializers
			AssetHandlers _initializers[(int)AssetTypes::_Count];

			// per-type counters
			size_t _counts[(int)AssetTypes::_Count] = { 0 };

			// assets cache
			std::unordered_map<std::string, AssetPtr> _cache;

		protected:

			/**
			 * Initialize manager when engine starts.
			 */
			virtual void _Initialize() override;

			/**
			 * Clear / free this manager's resources.
			 */
			virtual void _Dispose() override;

			/**
			 * Called every frame.
			 */
			virtual void _Update(double deltaTime) override;

			/**
			 * Called when main loop starts.
			 */
			virtual void _Start() override;

		public:

			/**
			 * Load and return an Image asset.
			 *
			 * \param filename Image file path.
			 * \param filter Image filtering mode.
			 * \param useCache If true, will try to get asset from cache first. If not found in cache will add to cache after load.
			 * \return Image asset.
			 */
			virtual ImageAsset LoadImage(const char* filename, ImageFilterMode filter = ImageFilterMode::Nearest, bool useCache = true) override;

			/**
			 * Load and return a music asset.
			 *
			 * \param filename Music file path.
			 * \param useCache If true, will try to get asset from cache first. If not found in cache will add to cache after load.
			 * \return Image asset.
			 */
			virtual MusicAsset LoadMusic(const char* filename, bool useCache = true) override;

			/**
			 * Load and return a sound effect asset.
			 *
			 * \param filename Sound file path.
			 * \param useCache If true, will try to get asset from cache first. If not found in cache will add to cache after load.
			 * \return Image asset.
			 */
			virtual SoundAsset LoadSound(const char* filename, bool useCache = true) override;

			/**
			 * Load and return a configuration asset.
			 *
			 * \param filename Config file path.
			 * \param useCache If true, will try to get asset from cache first. If not found in cache will add to cache after load.
			 * \return Config asset.
			 */
			virtual ConfigAsset LoadConfig(const char* filename, bool useCache = true) override;

			/**
			 * Create and return an empty configuration file.
			 *
			 * \return Empty config asset.
			 */
			virtual ConfigAsset CreateEmptyConfig() override;

			/**
			 * Load and return a font asset.
			 *
			 * \param filename Font file path.
			 * \param fontSize Loaded font base size.
			 * \param useCache If true, will try to get asset from cache first. If not found in cache will add to cache after load.
			 * \return Font asset.
			 */
			virtual FontAsset LoadFont(const char* filename, int fontSize = 32, bool useCache = true) override;

			/**
			 * Save configuration file.
			 *
			 * \param config Config file to save.
			 * \param filename config file path.
			 * \return True if succeed, false otherwise.
			 */
			virtual bool SaveConfig(ConfigAsset config, const char* filename) override;

			/**
			 * Clear all assets in cache.
			 * Note: this won't necessarily dispose all assets - assets that are still held in external code will survive.
			 * To free all assets, you need to release all pointers to them.
			 */
			virtual void ClearCache() override;

			/**
			 * Creates and return an empty image asset.
			 * 
			 * \param size Image size.
			 * \param filter Image filtering mode.
			 * \return Empty image.
			 */
			virtual ImageAsset CreateEmptyImage(const framework::PointI& size, ImageFilterMode filter = ImageFilterMode::Nearest) override;

			/**
			 * Get loaded assets count by type.
			 *
			 * \param type Asset type to get counter for.
			 * \return How many loaded assets we have of this type
			 */
			virtual size_t _GetLoadedAssetsCount(AssetTypes type) const override;

			/**
			 * Register custom initializer and disposer to handle asset type.
			 *
			 * \param type Asset type to add initializer to.
			 * \param initializer Initializer method.
			 * \param disposer Disposer method.
			 * \param context Optional context to attach to initialize / dispose calls.
			 */
			virtual void _SetAssetsInitializer(AssetTypes type, AssetInitializer initializer, AssetDisposer disposer, void* context) override;

		private:

			/**
			 * Put value in cache.
			 */
			void PutInCache(AssetPtr asset, const char* key);

			/**
			 * Get asset from cache.
			 *
			 * \return asset instance if found, or nullptr if not.
			 */
			AssetPtr GetFromCache(const char* id);

			/**
			 * Called to initialize every new asset we create.
			 * 
			 * \param asset Asset to initialize.
			 * \param extraData Any additional data required for the creation of the asset. For example, when creating an empty image this will be image size.
			 */
			void InitNewAsset(IAsset* asset, void* extraData = nullptr);

			/**
			 * Dispose an asset. Called automatically when asset destructor is called.
			 *
			 * \param asset
			 */
			void Dispose(IAsset* asset);
		};
	}
}
