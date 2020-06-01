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
		class DLLEXPORT _ImageHandle
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
		};

		/**
		 * Image filtering modes.
		 */
		enum class DLLEXPORT ImageFilterMode
		{
			Nearest = 0,
			Linear = 1,
			Anisotropic = 2,
			_Count = 3,
		};
	}
}