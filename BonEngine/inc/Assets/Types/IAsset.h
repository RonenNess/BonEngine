/*****************************************************************//**
 * \file   IAsset.h
 * \brief  Asset base class for all game assets (image, sound, ect.)
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include <string>
#include "../../dllimport.h"
#include "../Defs.h"


namespace bon
{
	namespace assets
	{
		/**
		 * Assets base class.
		 */
		class IAsset
		{
		private:
			// asset path
			std::string _path;

		public:

			/**
			 * The underlying asset handle.
			 * Different object depending on type and used internally by the managers implementation.
			 */
			void* _untypedHandle;

			/**
			 * Empty constructor.
			 */
			IAsset() : _path(), _untypedHandle(nullptr) {}

			/**
			 * Create the asset.
			 * 
			 * \param path Asset's path.
			 */
			IAsset(const char* path) : _path(path), _untypedHandle(nullptr) {
			}

			/**
			 * Asset destructor.
			 */
			virtual ~IAsset() { }

			/**
			 * Get asset path.
			 * 
			 * \return Asset path.
			 */
			const char* Path() const { return _path.c_str(); }

			/**
			 * Return if this asset is properly loaded / valid.
			 */
			virtual bool IsValid() const = 0;

			/**
			 * Get asset type.
			 * 
			 * \return Asset type identifier.
			 */
			virtual AssetTypes AssetType() const = 0;
		};
	}
}
