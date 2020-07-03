/*****************************************************************//**
 * \file   Image.h
 * \brief  Define an image asset. Used for rendering.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../../dllimport.h"
#include "../../Framework/Point.h"
#include "IAsset.h"
#include "../Defs.h"
#include "ImageHandle.h"


namespace bon
{
	namespace assets
	{
		/**
		 * An image asset.
		 * Used to draw sprites.
		 */
		class _Image : public IAsset
		{
		private:
			ImageFilterMode _filtering = ImageFilterMode::Nearest;

		public:

			/**
			 * Get image handle.
			 * 
			 * \return Image handle.
			 */
			inline _ImageHandle* Handle() { return (_ImageHandle*)_untypedHandle; }
			
			/**
			 * Get image handle.
			 *
			 * \return Image handle.
			 */
			inline const _ImageHandle* Handle() const { return (const _ImageHandle*)_untypedHandle; }
			
			/**
			 * Create the asset.
			 *
			 * \param path Asset's path.
			 */
			_Image(const char* path, ImageFilterMode filtering = ImageFilterMode::Nearest) : IAsset(path), _filtering(filtering) {
			}

			/**
			 * Create empty image with size.
			 * 
			 * \param size Image size.
			 */
			_Image(const framework::PointI& size, ImageFilterMode filtering = ImageFilterMode::Nearest) : IAsset(""), _filtering(filtering) {
			}

			/**
			 * Return if this asset is properly loaded / valid.
			 */
			virtual bool IsValid() const override
			{
				return _untypedHandle != nullptr && Handle()->IsValid();
			}

			/**
			 * Get asset type.
			 *
			 * \return Asset type identifier.
			 */
			virtual AssetTypes AssetType() const override { return AssetTypes::Image; }

			/**
			 * Get image filtering mode.
			 * 
			 * \return Image filtering mode.
			 */
			inline ImageFilterMode FilteringMode() const 
			{ 
				return _filtering; 
			}

			/**
			 * Save image asset to file.
			 * 
			 * \param filename Filename to save image to.
			 */
			inline void SaveToFile(const char* filename) const
			{
				if (IsValid())
				{
					Handle()->SaveToFile(filename);
				}
			}

			/**
			 * Get image width.
			 * 
			 * \return Image width.
			 */
			inline int Width() const 
			{
				return IsValid() ? Handle()->Width() : 0;
			}

			/**
			 * Get image height.
			 *
			 * \return Image height.
			 */
			inline int Height() const 
			{
				return IsValid() ? Handle()->Height() : 0;
			}
		};
	}
}