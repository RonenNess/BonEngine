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
#include "../../Framework/Color.h"
#include "../../Framework/Rectangle.h"
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
		class BON_DLLEXPORT _Image : public IAsset
		{
		private:

			// image filtering mode
			ImageFilterMode _filtering = ImageFilterMode::Nearest;

			// is this image loaded from file?
			bool _fromFile;

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
			 * Get if this image loaded from file.
			 */
			inline bool IsFromFile() const { return _fromFile; }
			
			/**
			 * Create the asset.
			 *
			 * \param path Asset's path.
			 */
			_Image(const char* path, ImageFilterMode filtering = ImageFilterMode::Nearest) : IAsset(path), _filtering(filtering), _fromFile(true) {
			}

			/**
			 * Create empty image with size.
			 * 
			 * \param size Image size.
			 */
			_Image(const framework::PointI& size, ImageFilterMode filtering = ImageFilterMode::Nearest) : IAsset(""), _filtering(filtering), _fromFile(false) {
			}

			/**
			 * Create image with handle.
			 *
			 * \param handle Image handle.
			 */
			_Image(_ImageHandle* handle) : IAsset(std::to_string((long long)handle).c_str()) {
				_SetHandle(handle);
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

			/**
			* Read pixels into internal buffer to allow querying pixels using `GetPixel()`.
			* You must call this before using GetPixel.
			* \param sourceRect Source rectangle to read from image, or empty to read everything.
			*/
			inline void PrepareReadingBuffer(const framework::RectangleI& sourceRect)
			{
				if (IsValid())
				{
					Handle()->PrepareReadingBuffer(sourceRect);
				}
			}

			/**
			 * Free reading buffer previously set using `PrepareReadingBuffer()`.
			 * This happens automatically when asset is released.
			 */
			inline void FreeReadingBuffer()
			{
				if (IsValid())
				{
					Handle()->FreeReadingBuffer();
				}
			}

			/**
			 * Get pixel from image.
			 * You must first call 'ReadPixelsData' to prepare internal reading buffer.
			 *
			 * \param position Pixel to read.
			 * \return Pixel color.
			 */
			framework::Color GetPixel(const framework::PointI& position)
			{
				if (IsValid())
				{
					return Handle()->GetPixel(position);
				}
				return framework::Color::TransparentBlack;
			}

			/**
			 * Clear image to transparent color.
			 */
			void Clear()
			{
				if (IsValid())
				{
					Handle()->Clear();
				}
			}
		};
	}
}