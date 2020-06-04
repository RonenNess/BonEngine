/*****************************************************************//**
 * \file   SoundHandle.h
 * \brief  Define a sound handle.
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
		 * Define the interface for a sound internal handle.
		 * To create new sound asset types, you must implement this API.
		 */
		class BON_DLLEXPORT _SoundHandle
		{
		public:
			/**
			 * The sound track (implementation dependent).
			 */
			void* Track = nullptr;

			/**
			 * Get if this handle is valid.
			 *
			 * \return If sound track is valid.
			 */
			virtual bool IsValid() const { return Track != nullptr; }

			/**
			 * Get track length, in seconds.
			 *
			 * \return Sound track length.
			 */
			virtual float Length() const = 0;

			/**
			* Get if this sound is currently playing.
			*/
			virtual bool IsPlaying() const = 0;
		};
	}
}