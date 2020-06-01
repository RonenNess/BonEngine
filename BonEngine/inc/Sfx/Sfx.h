/*****************************************************************//**
 * \file   Sfx.h
 * \brief  The default sfx manager implemented by BonEngine.
 * 
 * \author Ronen
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "Defs.h"
#include "ISfx.h"
#include "SfxSdlWrapper.h"

namespace bon
{
	namespace sfx
	{
		/**
		 * Default sfx manager.
		 */
		class Sfx : public ISfx
		{
		private:
			// master volume factor
			float _masterVolume = 1.0f;

			// master music volume factor
			float _masterMusicVolume = 1.0f;

			// current music volume, before master volume factor
			int _musicVolume = 0;

		public:

			/**
			 * The sfx internal implementor class.
			 * Access this only if you must change something internal in the default Sfx manager.
			 */
			SfxSdlWrapper _Implementor;

			/**
			 * Set audio device properties.
			 *
			 * \param frequency Sound frequency.
			 * \param format Sound format.
			 * \param stereo Should we support stereo sound (false for mono).
			 * \param audio_chunk_size Audio chunk size (smaller values = more responsive sound, but higher CPU usage).
			 */
			virtual void SetAudioProperties(int frequency = 22050, AudioFormats format = AudioFormats::S16LSB, bool stereo = true, int audio_chunk_size = 4096) override;

			/**
			 * Play a music track.
			 *
			 * \param music Music track to play.
			 * \param volume Playing music volume (1-100 is recommanded range).
			 * \param loops How many times to repeat the music track (-1 = endless loop).
			 */
			virtual void PlayMusic(assets::MusicAsset music, int volume = 75, int loops = -1) override;

			/**
			 * Pause / resume currently played track.
			 *
			 * \param pause If true, will pause track. If false, will resume it.
			 */
			virtual void PauseMusic(bool pause) override;
			
			/**
			 * Stop playing music.
			 */
			virtual void StopMusic() override { SetMusicVolume(0); }

			/**
			 * Set music volume, or stop it.
			 *
			 * \param volume Volume to set, values should range from 1 to 100, or 0 to stop sound.
			 */
			virtual void SetMusicVolume(int volume) override;

			/**
			 * Play a sound effect.
			 *
			 * \param sound Sound track to play.
			 * \param volume Playing sound volume (1-100 is recommanded range).
			 * \param loops How many times to repeat the sound track (-1 = endless loop).
			 * \param pitch Apply pitch effect on sound effect (1 = no pitch).
			 * \return channel id to allow control over this sound while it plays. If fail to play sound, will return InvalidSoundChannel.
			 */
			virtual SoundChannelId PlaySound(assets::SoundAsset sound, int volume = 100, int loops = 0, float pitch = 1.0f) override;

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
			 * \return channel id to allow control over this sound while it plays.
			 */
			virtual SoundChannelId PlaySound(assets::SoundAsset sound, int volume, int loops, float pitch, float panLeft, float panRight, float distance) override;

			/**
			 * Set the volume of a currently playing sound channel, or stop it if volume is 0.
			 *
			 * \param channel Channel id to set.
			 * \param volume Volume to set, values should range from 1 to 100, or 0 to stop sound.
			 */
			virtual void SetChannelVolume(SoundChannelId channel, int volume) override;

			/**
			 * Set channel distance from listener (affect volume).
			 *
			 * \param channel Channel id to set (or AllChannels for all channels).
			 * \param distance Distance from listener (0.0 - 1.0).
			 */
			virtual void SetChannelDistance(SoundChannelId channel, float distance) override;

			/**
			 * Set channel panning.
			 *
			 * \param channel Channel id to set
			 * \param panLeft Pan left side value (0.0 - 1.0)
			 * \param panRight Pan right side value (0.0 - 1.0)
			 */
			virtual void SetChannelPanning(SoundChannelId channel, float panLeft, float panRight) override;

			/**
			 * Stop playing a channel.
			 *
			 * \param channel Channel id to stop (or affect AllChannels for all channels).
			 */
			virtual void StopChannel(SoundChannelId channel) override { SetChannelVolume(channel, 0); }

			/**
			* Test if a given sound is currently playing on a channel.
			*
			* \param channel Channel id to test. If -1, will test all channels (a bit slow - not recommended).
			* \param sound Sound to check if playing.
			* \return If the given sound is currently playing.
			*/
			virtual bool IsPlaying(assets::SoundAsset sound, SoundChannelId channel = -1) const;

			/**
			* Set the master volume of music and sound effects.
			* Note: affect music volume immediately, but does not affect currently playing sound effects.
			*
			* \param soundEffectsVolume Master volume for sound effects.
			* \param musicVolume musicVolume Master volume for music.
			*/
			virtual void SetMasterVolume(int soundEffectsVolume, int musicVolume) override;

		protected:

			/**
			 * Initialize manager when engine starts.
			 */
			virtual void _Initialize() override;

			/**
			 * Clear / free this manager's resources.
			 */
			virtual void _Dispose() override;

			/**
			 * Called every frame.
			 */
			virtual void _Update(double deltaTime) override;

			/**
			 * Called when main loop starts.
			 */
			virtual void _Start() override;
		};
	}
}