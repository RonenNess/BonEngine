/*****************************************************************//**
 * \file   SfxSdlWrapper.h
 * \brief  SDL wrapper for the SFX manager.
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include <Assets/Defs.h>
#include <Assets/Types/Music.h>
#include <Framework/Point.h>
#include <Framework/Rectangle.h>
#include <Framework/Color.h>
#include <Sfx/Defs.h>

 // forward declare some SDL stuff
struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;

namespace bon
{
	namespace sfx
	{
		/**
		 * The sfx implementor class.
		 */
		class BON_DLLEXPORT SfxSdlWrapper
		{
		private:

			// was audio init?
			bool _wasInit = false;

		public:

			/**
			 * Initialize sfx.
			 */
			void Initialize();

			/**
			 * Actually init audio.
			 * Called after start, to allow initial scene to load different settings
			 */
			void InitAudio();

			/**
			 * Get if audio was initialized.
			 */
			inline bool IsInit() const { return _wasInit; }

			/**
			 * Play a music track.
			 * 
			 * \param music Music track to play.
			 * \param loops How many times to repeat the music track (-1 = endless loop).
			 * \param fadeInTime Fade in time in seconds.
			 */
			void PlayMusic(assets::MusicAsset music, int loops = -1, float fadeInTime = 0);

			/**
			 * Pause / resume currently played track.
			 * 
			 * \param pause If true, will pause track. If false, will resume it.
			 */
			void PauseMusic(bool pause);

			/**
			 * Set music volume, or stop it.
			 * 
			 * \param volume Volume to set, values should range from 1 to 100, or 0 to stop sound.
			 */
			void SetMusicVolume(int volume);

			/**
			 * Play a sound effect.
			 *
			 * \param sound Sound track to play.
			 * \param volume Playing sound volume (1-100 is recommanded range).
			 * \param loops How many times to repeat the sound track (-1 = endless loop).
			 * \param pitch Apply pitch effect on sound effect (1 = no pitch).
			 * \param fadeInTime If not 0, will fade sound in over this time period (in seconds).
			 * \return channel id to enable control over this sound play.
			 */
			SoundChannelId PlaySound(assets::SoundAsset sound, int volume = 100, int loops = 0, float pitch = 1.0f, float fadeInTime = 0);

			/**
			* Test if a given sound is currently playing on a channel.
			*
			* \param channel Channel id to test. If -1, will test all channels (a bit slow - not recommended).
			* \param sound Sound to check if playing.
			* \return If the given sound is currently playing.
			*/
			bool IsPlaying(assets::SoundAsset sound, SoundChannelId channel = -1) const;

			/**
			 * Set the volume of a currently playing sound channel, or stop it if volume is 0.
			 * 
			 * \param channel Channel id to set.
			 * \param volume Volume to set, values should range from 1 to 100, or 0 to stop sound.
			 */
			void SetVolume(SoundChannelId channel, int volume);

			/**
			 * Stop playing a channel.
			 * 
			 * \param channel Channel id to stop.
			 */
			void StopChannel(SoundChannelId channel);

			/**
			 * Stop playing music.
			 */
			void StopMusic();

			/**
			 * Fade out channel.
			 */
			void FadeOut(SoundChannelId channel, float fadeOutTime);

			/**
			 * Fade out music.
			 */
			void FadeOutMusic(float fadeOutTime);

			/**
			 * Set audio properties.
			 * If init was already called, need to call 'InitAudio()' again for it to take effect.
			 */
			void SetAudioProperties(int frequency, AudioFormats format, int channels, int audio_chunk_size);

			/**
			 * Set channel panning.
			 *
			 * \param channel Channel id to set
			 * \param panLeft Pan left side value (0.0 - 1.0)
			 * \param panRight Pan right side value (0.0 - 1.0)
			 */
			void SetChannelPanning(SoundChannelId channel, float panLeft, float panRight);

			/**
			 * Set channel distance from listener (affect volume).
			 *
			 * \param channel Channel id to set (or AllChannels for all channels).
			 * \param distance Distance from listener (0.0 - 1.0).
			 */
			void SetChannelDistance(SoundChannelId channel, float distance);

			/**
			 * Dispose sfx implementation.
			 */
			void Dispose();
		};
	}
}