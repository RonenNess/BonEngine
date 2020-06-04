/*****************************************************************//**
 * \file   Defs.h
 * \brief  Assets related defs.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include <memory>

namespace bon
{
	namespace assets
	{
		// forward declare asset base classes
		class IAsset;
		class _Image;
		class _Music;
		class _Sound;
		class _Config;
		class _Font;

		/**
		 * Method different managers can register to handle assets creation.
		 * \param asset The asset to initialize (contains Path()).
		 * \param context Can be used to pass internal context by the manager.
		 * \param extraData Extra creation data, used for special cases like creating empty image.
		 */
		typedef void (*AssetInitializer) (IAsset* asset, void* context, void* extraData);

		/**
		 * Method different managers can register to handle assets deletion.
		 * \param asset The asset to initialize (contains Path()).
		 * \param context Can be used to pass internal context by the manager.
		 */
		typedef void (*AssetDisposer) (IAsset* asset, void* context);

		// pointer to an asset types
		typedef BON_DLLEXPORT std::shared_ptr<IAsset>	AssetPtr;
		typedef BON_DLLEXPORT std::shared_ptr<_Image>	ImageAsset;
		typedef BON_DLLEXPORT std::shared_ptr<_Music>	MusicAsset;
		typedef BON_DLLEXPORT std::shared_ptr<_Sound>	SoundAsset;
		typedef BON_DLLEXPORT std::shared_ptr<_Config>	ConfigAsset;
		typedef BON_DLLEXPORT std::shared_ptr<_Font>	FontAsset;

		/**
		 * Struct used to hold initializer, disposer and context.
		 */
		struct BON_DLLEXPORT AssetHandlers
		{
			AssetInitializer InitializerFunc = nullptr;
			AssetDisposer DisposerFunc = nullptr;
			void* Context = nullptr;
		};

		/**
		 * All asset types.
		 */
		enum class BON_DLLEXPORT AssetTypes
		{
			Image,
			Sound,
			Music,
			Config,
			Font,
			_Count
		};
	}
}