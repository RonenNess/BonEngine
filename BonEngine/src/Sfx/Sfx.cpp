#include <Sfx/Sfx.h>
#include <Diagnostics/IDiagnostics.h>
#include <BonEngine.h>

namespace bon
{
	namespace sfx
	{
		// init sfx manager
		void Sfx::_Initialize()
		{
			_Implementor.Initialize();
		}

		// dispose sfx resources
		void Sfx::_Dispose()
		{
			_Implementor.Dispose();
		}

		// do updates
		void Sfx::_Update(double deltaTime)
		{
		}

		// called on main loop start
		void Sfx::_Start()
		{
			if (!_Implementor.IsInit()) {
				_Implementor.InitAudio();
			}
		}

		// set audio properties
		void Sfx::SetAudioProperties(int frequency, AudioFormats format, bool stereo, int audio_chunk_size)
		{
			_Implementor.SetAudioProperties(frequency, format, stereo ? 2 : 1, audio_chunk_size);
			if (_Implementor.IsInit()) {
				_Implementor.InitAudio();
			}
		}

		// start playing a music track
		void Sfx::PlayMusic(assets::MusicAsset music, int volume, int loops)
		{
			_Implementor.PlayMusic(music, loops);
			SetMusicVolume(volume);
		}

		// pause / resume music
		void Sfx::PauseMusic(bool pause)
		{
			_Implementor.PauseMusic(pause);
		}

		// set music volume
		void Sfx::SetMusicVolume(int volume)
		{
			_musicVolume = volume;
			_Implementor.SetMusicVolume((int)((float)volume * _masterMusicVolume));
		}

		// play a sound effect
		SoundChannelId Sfx::PlaySound(assets::SoundAsset sound, int volume, int loops, float pitch)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::PlaySoundCalls);
			volume = (int)((float)volume * _masterVolume);
			SoundChannelId ret = _Implementor.PlaySound(sound, volume, loops, pitch);
			return ret != AllChannels ? ret : InvalidSoundChannel;
		}

		// play a sound effect
		SoundChannelId Sfx::PlaySound(assets::SoundAsset sound, int volume, int loops, float pitch, float panLeft, float panRight, float distance)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::PlaySoundCalls);
			volume = (int)((float)volume * _masterVolume);
			SoundChannelId ret = _Implementor.PlaySound(sound, volume, loops, pitch);
			if (ret >= 0)
			{
				SetChannelPanning(ret, panLeft, panRight);
				SetChannelDistance(ret, distance);
			}
			return ret != AllChannels ? ret : InvalidSoundChannel;
		}

		// set channel panning
		void Sfx::SetChannelPanning(SoundChannelId channel, float panLeft, float panRight)
		{
			if (channel == InvalidSoundChannel) return;
			_Implementor.SetChannelPanning(channel, panLeft, panRight);
		}

		// set channel distance
		void Sfx::SetChannelDistance(SoundChannelId channel, float distance)
		{
			if (channel == InvalidSoundChannel) return;
			_Implementor.SetChannelDistance(channel, distance);
		}

		// set channel's volume
		void Sfx::SetChannelVolume(SoundChannelId channel, int volume)
		{
			if (channel == InvalidSoundChannel) return;
			volume = (int)((float)volume * _masterVolume);
			_Implementor.SetVolume(channel, volume);
		}

		// check if sound is playing
		bool Sfx::IsPlaying(assets::SoundAsset sound, SoundChannelId channel) const
		{
			if (channel == InvalidSoundChannel) return false;
			return _Implementor.IsPlaying(sound, channel);
		}

		// set master volumes
		void Sfx::SetMasterVolume(int soundEffectsVolume, int musicVolume)
		{
			_masterVolume = (float)soundEffectsVolume / 100.0f;
			_masterMusicVolume = (float)musicVolume / 100.0f;
			SetMusicVolume(_musicVolume);
		}
	}
}