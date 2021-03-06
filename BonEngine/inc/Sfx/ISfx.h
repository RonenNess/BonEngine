/*****************************************************************//**
 * \file   ISfx.h
 * \brief  Define the API for the Sfx manager class.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "../IManager.h"
#include "../Assets/Types/Music.h"
#include "Defs.h"


namespace bon
{
	namespace sfx
	{
		/**
		 * Interface for the SFX sound & music manager.
		 * This manager responsible to playing sounds.
		 */
		class BON_DLLEXPORT ISfx : public IManager
		{
		public:

			/**
			 * Set audio device properties.
			 * 
			 * \param frequency Sound frequency.
			 * \param format Sound format.
			 * \param stereo Should we support stereo sound (false for mono).
			 * \param audio_chunk_size Audio chunk size (smaller values = more responsive sound, but higher CPU usage).
			 */
			virtual void SetAudioProperties(int frequency = 22050, AudioFormats format = AudioFormats::S16LSB, bool stereo = true, int audio_chunk_size = 4096) = 0;

			/**
			 * Play a music track.
			 *
			 * \param music Music track to play.
			 * \param volume Playing music volume (1-100 is recommanded range).
			 * \param loops How many times to repeat the music track (-1 = endless loop).
			 * \param fadeInTime If not 0, will fade music in over this time period (in seconds).
			 */
			virtual void PlayMusic(assets::MusicAsset music, int volume = 75, int loops = -1, float fadeInTime = 0) = 0;

			/**
			 * Pause / resume currently played track.
			 *
			 * \param pause If true, will pause track. If false, will resume it.
			 */
			virtual void PauseMusic(bool pause) = 0;

			/**
			 * Set music volume.
			 *
			 * \param volume Volume to set, values should range from 0 to 100.
			 */
			virtual void SetMusicVolume(int volume) = 0;

			/**
			 * Stop playing music.
			 */
			virtual void StopMusic() = 0;

			/**
			 * Play a sound effect.
			 *
			 * \param sound Sound track to play.
			 * \param volume Playing sound volume (1-100 is recommanded range).
			 * \param loops How many times to repeat the sound track (-1 = endless loop).
			 * \param pitch Apply pitch effect on sound effect (1 = no pitch).
			 * \param fadeInTime If not 0, will fade sound in over this time period (in seconds).
			 * \return channel id to allow control over this sound while it plays. If fail to play sound, will return InvalidSoundChannel.
			 */
			virtual SoundChannelId PlaySound(assets::SoundAsset sound, int volume = 100, int loops = 0, float pitch = 1.0f, float fadeInTime = 0) = 0;

			/**
			 * Play a sound effect.
			 *
			 * \param sound Sound track to play.
			 * \param volume Playing sound volume (1-100 is recommanded range).
			 * \param loops How many times to repeat the sound track (-1 = endless loop).
			 * \param pitch Apply pitch effect on sound effect (1 = no pitch).
			 * \param panLeft Sound pan left value (0.0 - 1.0).
			 * \param panRight Sound pan right value (0.0 - 1.0).
			 * \param distance Sound distance from listener - affects volume (0.0 - 1.0).
			 * \param fadeInTime If not 0, will fade sound in over this time period (in seconds).
			 * \return channel id to allow control over this sound while it plays.
			 */
			virtual SoundChannelId PlaySound(assets::SoundAsset sound, int volume, int loops, float pitch, float panLeft, float panRight, float distance, float fadeInTime) = 0;

			/**
			 * Set channel distance from listener (affect volume).
			 * 
			 * \param channel Channel id to set (or AllChannels for all channels).
			 * \param distance Distance from listener (0.0 - 1.0).
			 */
			virtual void SetChannelDistance(SoundChannelId channel, float distance) = 0;

			/**
			 * Set the volume of a currently playing sound channel.
			 *
			 * \param channel Channel id to set (or AllChannels for all channels).
			 * \param volume Volume to set, values should range from 0 to 100.
			 */
			virtual void SetChannelVolume(SoundChannelId channel, int volume) = 0;
			
			/**
			 * Fade out channel.
			 * 
			 * \param channel Channel to fade out.
			 * \param fadeOutTime Fade out time in seconds.
			 */
			virtual void FadeOutChannel(SoundChannelId channel, float fadeOutTime) = 0;

			/**
			 * Fade out music.
			 *
			 * \param fadeOutTime Fade out time in seconds.
			 */
			virtual void FadeOutMusic(float fadeOutTime) = 0;

			/**
			 * Set channel panning.
			 * 
			 * \param channel Channel id to set 
			 * \param panLeft Pan left side value (0.0 - 1.0)
			 * \param panRight Pan right side value (0.0 - 1.0)
			 */
			virtual void SetChannelPanning(SoundChannelId channel, float panLeft, float panRight) = 0;

			/**
			 * Stop playing a channel.
			 * 
			 * \param channel Channel id to stop (or AllChannels for all channels).
			 */
			virtual void StopChannel(SoundChannelId channel) = 0;

			/**
			* Set the master volume of music and sound effects.
			* Note: affect music volume immediately, but does not affect currently playing sound effects.
			*
			* \param soundEffectsVolume Master volume for sound effects.
			* \param musicVolume musicVolume Master volume for music.
			*/
			virtual void SetMasterVolume(int soundEffectsVolume, int musicVolume) = 0;

		protected:

			/**
			 * Get manager identifier.
			 */
			virtual const char* _GetId() const override { return "sfx"; }
		};
	}
}