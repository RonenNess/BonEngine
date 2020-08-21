/*****************************************************************//**
 * \file   ImageHandle.h
 * \brief  Define an image handle.
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


namespace bon
{
	namespace assets
	{
		/**
		 * Define the interface for an image internal handle.
		 * To create new image asset types, you must implement this API.
		 */
		class BON_DLLEXPORT _ImageHandle
		{
		public:
			/**
			 * Image texture (implementation dependent).
			 */
			void* Texture = nullptr;

			/**
			 * Get if this handle is valid.
			 *
			 * \return If image is valid.
			 */
			virtual bool IsValid() const { return Texture != nullptr; }

			/**
			 * Get image width.
			 *
			 * \return Image width.
			 */
			virtual int Width() const = 0;

			/**
			 * Get image height.
			 *
			 * \return Image height.
			 */
			virtual int Height() const = 0;

			/**
			 * Save image asset to file.
			 *
			 * \param filename Filename to save image to.
			 */
			virtual void SaveToFile(const char* filename) const = 0;
		
			/**
			* Read pixels into internal buffer to allow querying pixels using `GetPixel()`.
			* You must call this before using GetPixel.
			* \param sourceRect Source rectangle to read from image, or empty to read everything.
			*/
			virtual void PrepareReadingBuffer(const framework::RectangleI& sourceRect) = 0;
			
			/**
			 * Free reading buffer previously set using `PrepareReadingBuffer()`.
			 * This happens automatically when asset is released.
			 */
			virtual void FreeReadingBuffer() = 0;

			/**
			 * Get pixel from image.
			 * You must first call 'ReadPixelsData' to prepare internal reading buffer.
			 * 
			 * \param position Pixel to read.
			 * \return Pixel color.
			 */
			virtual framework::Color GetPixel(const framework::PointI& position) = 0;

			/**
			 * Clear this image to transparent pixels.
			 */
			virtual void Clear() = 0;
		};

		/**
		 * Image filtering modes.
		 */
		enum class BON_DLLEXPORT ImageFilterMode
		{
			Nearest = 0,
			Linear = 1,
			Anisotropic = 2,
			_Count = 3,
		};
	}
}