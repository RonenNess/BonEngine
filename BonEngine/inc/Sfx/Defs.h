/*****************************************************************//**
 * \file   Defs.h
 * \brief  Misc defs and enum related to SFX.
 *
 * \author Ronen
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"

namespace bon
{
	namespace sfx
	{
		/**
		 * Represent the handle of a playing sound channel.
		 * Used this to stop sounds that are currently playing.
		 */
		typedef DLLEXPORT int SoundChannelId;

		/**
		 * Define channel id to affect all channels.
		 */
		static const SoundChannelId AllChannels = -1;

		/**
		 * Define channel id for invalid channel / errors.
		 */
		static const SoundChannelId InvalidSoundChannel = -2;

		/**
		 * Format types for audio initialization.
		 */
		enum class DLLEXPORT AudioFormats
		{
			U8, S8, U16LSB, S16LSB, U16MSB, S16MSB
		};
	}
}