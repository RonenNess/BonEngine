/*****************************************************************//**
 * \file   Music.h
 * \brief  Define a music handle.
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../../dllimport.h"
#include "IAsset.h"
#include "../Defs.h"

namespace bon
{
	namespace assets
	{
		/**
		 * Define the interface for a music internal handle.
		 * To create new music asset types, you must implement this API.
		 */
		class DLLEXPORT _MusicHandle
		{
		public:
			/**
			 * The music track (implementation dependent).
			 */
			void* Track = nullptr;

			/**
			 * Get if this handle is valid.
			 *
			 * \return If music track is valid.
			 */
			virtual bool IsValid() const { return Track != nullptr; }

			/**
			 * Get track length, in seconds.
			 *
			 * \return Music track length.
			 */
			virtual float Length() const = 0;
		};
	}
}