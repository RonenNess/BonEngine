#include <Assets/Assets.h>
#include <Assets/Types/IAsset.h>
#include <Diagnostics/IDiagnostics.h>
#include <functional>
#include <BonEngine.h>


namespace bon
{
	namespace assets
	{
		/**
		 * Internal helper class that implements generic loading code.
		 */
		class AssetsLoaderCode
		{
		public:
			
			/**
			 * Load asset.
			 * 
			 * \param assets Assets manager.
			 * \param path Asset path.
			 * \param useCache Should we use cache?
			 * \param extraData Optional extra data to pass to creation.
			 * \param instanceCreator Optional lambda to create a new instance, if needed. If not provided, will just create using default constructor.
			 * \return Asset instance.
			 */
			template <class AssetType>
			static shared_ptr<AssetType> LoadAssetT(Assets* assets, const char* path, bool useCache, void* extraData = nullptr, std::function<AssetType*()>&& instanceCreator = nullptr)
			{
				// assert
				if (path == nullptr || path[0] == '\0') {
					throw framework::AssetLoadError("Cannot load asset with empty path!");
				}

				// try to get from cache
				if (useCache) {
					AssetPtr fromCache = assets->GetFromCache(path);
					if (fromCache.get() != nullptr) {
						return std::static_pointer_cast<AssetType>(fromCache);
					}
				}

				// if got here it means we need to load.
				// create asset instance and init it (either use lambda we got, or just create a new instance
				AssetType* ret; 
				if (instanceCreator != nullptr) {
					ret = instanceCreator();
				}
				else {
					ret = new AssetType(path);
				}
				assets->InitNewAsset(ret, extraData);

				// convert to shared ptr with corresponding deleter
				auto assetPtr = std::shared_ptr<AssetType>(ret, [assets](IAsset* asset) {
					if (!bon::_GetEngine().Destroyed()) {
						assets->Dispose(asset);
						delete asset;
					}
					});
				
				// add to cache and return
				if (useCache) {
					assets->PutInCache(assetPtr);
				}
				return assetPtr;
			}
		};

		// init assets manager
		void Assets::_Initialize()
		{
		}

		// dispose assets resources
		void Assets::_Dispose()
		{
		}
		
		// do updates
		void Assets::_Update(double deltaTime)
		{
		}

		// called on main loop start
		void Assets::_Start()
		{
		}

		// load an image asset
		ImageAsset Assets::LoadImage(const char* filename, ImageFilterMode filter, bool useCache)
		{
			auto createImageLambda = [filename, filter]() { return new _Image(filename, filter); };
			return AssetsLoaderCode::LoadAssetT<_Image>(this, filename, useCache, nullptr, createImageLambda);
		}

		// load a music asset
		MusicAsset Assets::LoadMusic(const char* filename, bool useCache)
		{
			return AssetsLoaderCode::LoadAssetT<_Music>(this, filename, useCache);
		}
		
		// load a sound effect asset
		SoundAsset Assets::LoadSound(const char* filename, bool useCache)
		{
			return AssetsLoaderCode::LoadAssetT<_Sound>(this, filename, useCache);
		}

		// load a config asset
		ConfigAsset Assets::LoadConfig(const char* filename, bool useCache)
		{
			return AssetsLoaderCode::LoadAssetT<_Config>(this, filename, useCache);
		}

		// load a font asset
		FontAsset Assets::LoadFont(const char* filename, int fontSize, bool useCache)
		{
			return AssetsLoaderCode::LoadAssetT<_Font>(this, filename, useCache, &fontSize);
		}

		// create empty image asset
		ImageAsset Assets::CreateEmptyImage(const framework::PointI& size, ImageFilterMode filter)
		{
			// create empty image
			_Image* ret = new _Image(size, filter);
			InitNewAsset(ret, (void*)&size);

			// convert to shared ptr with corresponding deleter
			auto assetPtr = std::shared_ptr<_Image>(ret, [this](IAsset* asset) {
				if (!bon::_GetEngine().Destroyed()) {
					this->Dispose(asset);
					delete asset;
				}
				});
			return assetPtr;
		}
		
		// add asset to cache
		void Assets::PutInCache(AssetPtr asset)
		{
			BON_DLOG("Add asset '%s' to cache.", asset->Path());
			(_cache)[std::move(asset->Path())] = asset;
		}

		// get from cache
		AssetPtr Assets::GetFromCache(const char* cacheId)
		{
			return (_cache)[std::move(cacheId)];
		}

		// clear cache
		void Assets::ClearCache()
		{
			BON_DLOG("Clear assets cache.");
			_cache.clear();
		}

		// register initializer to handle asset type
		void Assets::_SetAssetsInitializer(AssetTypes type, AssetInitializer initializer, AssetDisposer disposer, void* context)
		{
			AssetHandlers data;
			data.InitializerFunc = initializer;
			data.DisposerFunc = disposer;
			data.Context = context;
			_initializers[(int)type] = data;
		}

		// get loaded assets count by type
		size_t Assets::_GetLoadedAssetsCount(AssetTypes type) const
		{
			return _counts[(int)type];
		}

		// create an empty config file
		ConfigAsset Assets::CreateEmptyConfig()
		{
			// create empty image
			_Config* ret = new _Config(nullptr);
			InitNewAsset(ret, nullptr);

			// convert to shared ptr with corresponding deleter
			auto assetPtr = std::shared_ptr<_Config>(ret, [this](IAsset* asset) {
				if (!bon::_GetEngine().Destroyed()) {
					this->Dispose(asset);
					delete asset;
				}
				});
			return assetPtr;
		}

		// init new assets
		void Assets::InitNewAsset(IAsset* asset, void* extraData)
		{
			// log
			const char* temp = asset->Path();
			BON_DLOG("Load asset '%s'", temp);

			// already initialized? error
			if (asset->IsValid()) {
				throw InvalidState("Asset to initialize is already in valid state!");
			}

			// call custom initializers
			auto initializerData = _initializers[(int)asset->AssetType()];
			if (initializerData.InitializerFunc) {
				initializerData.InitializerFunc(asset, initializerData.Context, extraData);
			}

			// update counters
			_counts[(int)asset->AssetType()]++;
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::LoadedAssets, 1);
		}

		// save config file
		bool Assets::SaveConfig(ConfigAsset config, const char* filename)
		{
			return config->_SaveToFile(filename);
		}

		// dispose an asset
		void Assets::Dispose(IAsset* asset)
		{
			// log
			BON_DLOG("Dispose asset '%s'", asset->Path());

			// already disposed? error
			if (!asset->IsValid()) {
				throw InvalidState("Asset to dispose is not valid!");
			}

			// call custom disposer
			auto initializerData = _initializers[(int)asset->AssetType()];
			if (initializerData.DisposerFunc) {
				initializerData.DisposerFunc(asset, initializerData.Context);
			}

			// update counters
			_counts[(int)asset->AssetType()]--;
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::LoadedAssets, -1);

			// clear handle
			asset->_SetHandle(nullptr);
		}
	}
}