/*****************************************************************//**
 * \file   Music.h
 * \brief  Define a music track asset.
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../../dllimport.h"
#include "IAsset.h"
#include "../Defs.h"
#include "MusicHandle.h"


namespace bon
{
	namespace assets
	{
		/**
		 * A music track asset.
		 * Used to play background music.
		 */
		class _Music : public IAsset
		{
		public:

			/**
			 * Get music handle.
			 *
			 * \return Music handle.
			 */
			_MusicHandle* Handle() { return (_MusicHandle*)_untypedHandle; }

			/**
			 * Get music handle.
			 *
			 * \return Music handle.
			 */
			const _MusicHandle* Handle() const { return (const _MusicHandle*)_untypedHandle; }

			/**
			 * Create the asset.
			 *
			 * \param path Asset's path.
			 */
			_Music(const char* path) : IAsset(path) {
			}

			/**
			 * Return if this asset is properly loaded / valid.
			 */
			virtual bool IsValid() const override { return _untypedHandle != nullptr && Handle()->IsValid(); }

			/**
			 * Get asset type.
			 *
			 * \return Asset type identifier.
			 */
			virtual AssetTypes AssetType() const override { return AssetTypes::Music; }

			/**
			 * Get track length, in seconds.
			 *
			 * \return Music track length.
			 */
			float Length() const { return Handle()->Length(); }
		};
	}
}