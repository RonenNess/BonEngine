/*****************************************************************//**
 * \file   Music.h
 * \brief  Define a music track asset.
 *
 * \author Ronen
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../../dllimport.h"
#include "IAsset.h"
#include "../Defs.h"
#include "SoundHandle.h"


namespace bon
{
	namespace assets
	{
		/**
		 * A sound track asset.
		 * Used to play sound effects.
		 */
		class _Sound : public IAsset
		{
		public:

			/**
			 * Get sound handle.
			 *
			 * \return Sound handle.
			 */
			inline _SoundHandle* Handle() { return (_SoundHandle*)_untypedHandle; }

			/**
			 * Get sound handle.
			 *
			 * \return Sound handle.
			 */
			inline const _SoundHandle* Handle() const { return (const _SoundHandle*)_untypedHandle; }

			/**
			 * Create the asset.
			 *
			 * \param path Asset's path.
			 */
			_Sound(const char* path) : IAsset(path) {
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
			virtual AssetTypes AssetType() const override { return AssetTypes::Sound; }

			/**
			 * Get track length, in seconds.
			 *
			 * \return Sound track length.
			 */
			float Length() const { return Handle()->Length(); }

			/**
			* Get if this sound is currently playing.
			*/
			bool IsPlaying() const { return Handle()->IsPlaying(); }
		};
	}
}