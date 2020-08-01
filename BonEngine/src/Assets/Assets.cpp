#include <Assets/Assets.h>
#include <Assets/Types/IAsset.h>
#include <Framework/Exceptions.h>
#include <Diagnostics/IDiagnostics.h>
#include <functional>
#include <BonEngine.h>
#include <fstream>
#include <mutex>

// mutex for cache so we won't accidentally get a broken asset
std::mutex g_cache_mutex;

// make sure file exists
inline bool validate_file_exist(const std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}

namespace bon
{
	namespace assets
	{
		// queue of assets that we're supposed to delete next frame.
		// its important to dispose assets during 'update' and not on the actual moment they release, to prevent crashes in SDL.
		std::vector<IAsset*> _deleteQueue;

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
			 * \param cacheKey Key to use when putting / getting from cache
			 * \param useCache Should we use cache?
			 * \param extraData Optional extra data to pass to creation.
			 * \param instanceCreator Optional lambda to create a new instance, if needed. If not provided, will just create using default constructor.
			 * \return Asset instance.
			 */
			template <class AssetType>
			static shared_ptr<AssetType> LoadAssetT(Assets* assets, const char* path, const char* cacheKey, bool useCache, void* extraData = nullptr, std::function<AssetType*()>&& instanceCreator = nullptr)
			{
				// make sure path is valid
				if (path == nullptr || path[0] == '\0') {
					throw framework::AssetLoadError("Cannot load asset with empty path!");
				}

				// make sure file exists
				if (!validate_file_exist(path))
				{
					throw framework::AssetLoadError((std::string("File not found! Path: '" + std::string(path)).c_str()));
				}

				// try to get from cache
				if (useCache) {
					std::lock_guard<std::mutex> guard(g_cache_mutex);
					AssetPtr fromCache = assets->GetFromCache(cacheKey);
					if (fromCache.get() != nullptr) {
						BON_DLOG("Retrieved asset from cache: '%s'. Asset address: %x.", cacheKey, fromCache.get());
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
						_deleteQueue.push_back(asset);
					}
				});
				BON_DLOG("Created new asset with path: '%s'. Asset address: %x. Add to cache: %d", path, assetPtr.get(), useCache);

				// add to cache and return
				if (useCache) {
					assets->PutInCache(assetPtr, cacheKey);
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
			// clear assets on delete list
			if (!_deleteQueue.empty())
			{
				BON_DLOG("Got %d assets to destroy.", _deleteQueue.size());
				for (auto asset : _deleteQueue)
				{
					if (asset->IsValid())
					{
						this->Dispose(asset);
					}
				}
				for (auto asset : _deleteQueue)
				{
					delete asset;
				}
				_deleteQueue.clear();
			}
		}

		// called on main loop start
		void Assets::_Start()
		{
		}

		// load an image asset
		ImageAsset Assets::LoadImage(const char* filename, ImageFilterMode filter, bool useCache)
		{
			auto createImageLambda = [filename, filter]() { return new _Image(filename, filter); };
			std::string tempStringForCache;
			if (useCache) { tempStringForCache = (std::string(filename) + std::to_string((int)filter)); }
			const char* cacheKey = useCache ? tempStringForCache.c_str() : nullptr;
			return AssetsLoaderCode::LoadAssetT<_Image>(this, filename, cacheKey, useCache, nullptr, createImageLambda);
		}

		// load a music asset
		MusicAsset Assets::LoadMusic(const char* filename, bool useCache)
		{
			return AssetsLoaderCode::LoadAssetT<_Music>(this, filename, filename, useCache);
		}
		
		// load a sound effect asset
		SoundAsset Assets::LoadSound(const char* filename, bool useCache)
		{
			return AssetsLoaderCode::LoadAssetT<_Sound>(this, filename, filename, useCache);
		}

		// load a config asset
		ConfigAsset Assets::LoadConfig(const char* filename, bool useCache)
		{
			return AssetsLoaderCode::LoadAssetT<_Config>(this, filename, filename, useCache);
		}

		// load a font asset
		FontAsset Assets::LoadFont(const char* filename, int fontSize, bool useCache)
		{
			std::string tempStringForCache;
			if (useCache) { tempStringForCache = (std::string(filename) + std::to_string(fontSize)); }
			const char* cacheKey = useCache ? tempStringForCache.c_str() : nullptr;
			return AssetsLoaderCode::LoadAssetT<_Font>(this, filename, cacheKey, useCache, &fontSize);
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
					_deleteQueue.push_back(asset);
				}
			});
			return assetPtr;
		}
		
		// add asset to cache
		void Assets::PutInCache(AssetPtr asset, const char* key)
		{
			BON_DLOG("Add asset '%s' to cache (key = '%s').", asset->Path(), key);
			std::lock_guard<std::mutex> guard(g_cache_mutex);
			(_cache)[std::move(key)] = asset;
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
			std::lock_guard<std::mutex> guard(g_cache_mutex);
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
					_deleteQueue.push_back(asset);
				}
			});
			return assetPtr;
		}

		// init new assets
		void Assets::InitNewAsset(IAsset* asset, void* extraData)
		{
			// log
			const char* temp = asset->Path();
			BON_DLOG("Init new asset with path '%s' and address %x.", temp, asset);

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
			BON_DLOG("Dispose asset with path '%s' and address %x.", asset->Path(), asset);

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

			// sanity - if asset is somehow in cache, remove it
			for (auto it = _cache.begin(); it != _cache.end(); )
			{
				if (it->second.get() == asset) 
				{ 
					std::lock_guard<std::mutex> guard(g_cache_mutex);
					BON_ELOG("Warning! Disposed asset while its still in cache! Path: '%s', Address: %x.", asset->Path(), asset);
					_cache.erase(it++); 
				}
				else { ++it; }
			}
		}
	}
}