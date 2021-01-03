#include <Sfx/SfxSdlWrapper.h>
#include <Log/ILog.h>
#include <Framework/Exceptions.h>
#include <Assets/Defs.h>
#include <Assets/Types/Music.h>
#include <Assets/Types/Sound.h>
#include <Framework/Point.h>
#include <Framework/Rectangle.h>
#include <Sfx/Defs.h>
#include <BonEngine.h>
#include <algorithm>

#pragma warning(push, 0)
#include <SDL2-2.0.12/include/SDL.h>
#include <SDL2_mixer-2.0.4/include/SDL_mixer.h>
#pragma warning(pop)

#include <../3rdparty_from_src/custom_mix_pitch/custom_mix_pitch.h>

using namespace bon::framework;
using namespace bon::assets;

namespace bon
{
	namespace sfx
	{
		// currently initialzed audio specs
		// useful info on settings: https://moddb.fandom.com/wiki/SDL_mixer:Tutorials:Playing_a_WAV_Sound_File
		namespace AudioSpec
		{
			int allocatedMixChannelsCount = 0;
			int frequency = MIX_DEFAULT_FREQUENCY;
			Uint16 format = MIX_DEFAULT_FORMAT;
			int channelCount = MIX_DEFAULT_CHANNELS;	
			int chunkSize = 4096; // 2048;
		}

		// this could be a macro as well
		static inline Uint16 formatSampleSize(Uint16 format)
		{
			return (format & 0xFF) / 8;
		}

		// Get chunk time length (in ms) given its size and current audio format
		static int computeChunkLengthMillisec(int chunkSize)
		{
			/* bytes / samplesize == sample points */
			const Uint32 points = chunkSize / formatSampleSize(AudioSpec::format);

			/* sample points / channels == sample frames */
			const Uint32 frames = (points / AudioSpec::channelCount);

			/* (sample frames * 1000) / frequency == play length, in ms */
			return ((frames * 1000) / AudioSpec::frequency);
		}

		// music handle for SDL
		class SDL_MusicHandle : public assets::_MusicHandle
		{
		public:

			/**
			 * Create SDL music handle.
			 */
			SDL_MusicHandle(Mix_Music* track)
			{
				Track = track;
			}

			/**
			 * Delete this music track.
			 */
			virtual ~SDL_MusicHandle()
			{
				if (Track) {
					Mix_FreeMusic((Mix_Music*)(Track));
				}
			}

			/**
			 * Get track length, in seconds.
			 *
			 * \return Music track length.
			 */
			virtual float Length() const override
			{
				BON_ELOG("Getting music track length is not supported! Returning -1.0 instead.");
				return -1.0f;
			}
		};

		// music loader we set in the assets manager during initialize
		void MusicLoader(bon::assets::IAsset* asset, void* context, void* extraData = nullptr)
		{
			// get asset path
			const char* path = asset->Path();
			BON_DLOG("Load music track from file: %s.", path);

			//Load music
			Mix_Music* music = Mix_LoadMUS(path);
			if (music == NULL)
			{
				BON_WLOG("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
				throw AssetLoadError(path);
			}
			
			// set handle
			SDL_MusicHandle* handle = new SDL_MusicHandle(music);
			asset->_SetHandle(handle);
		}

		// music disposer we set in the assets manager during asset disposal
		void MusicDisposer(bon::assets::IAsset* asset, void* context)
		{
			asset->_DestroyHandle<SDL_MusicHandle>();
		}

		// chunk (sound) handle for SDL
		class SDLChunkHandle : public assets::_SoundHandle
		{
		public:

			/**
			 * Create SDL chunk handle.
			 */
			SDLChunkHandle(Mix_Chunk* track)
			{
				Track = track;
			}

			/**
			 * Delete this chunk.
			 */
			virtual ~SDLChunkHandle()
			{
				if (Track) {
					Mix_FreeChunk((Mix_Chunk*)(Track));
				}
			}

			/**
			 * Get track length, in seconds.
			 *
			 * \return Sound track length.
			 */
			virtual float Length() const override
			{
				return (float)((float)computeChunkLengthMillisec(((Mix_Chunk*)Track)->alen) / 1000.0f);
			}

			/**
			* Get if this sound is currently playing.
			*/
			virtual bool IsPlaying() const override
			{
				for (int i = 0; i < AudioSpec::allocatedMixChannelsCount; ++i) {
					if (Mix_Playing(i) && Mix_GetChunk(i) == Track) {
						return true;
					}
				}
				return false;
			}
		};

		// sound loader we set in the assets manager during initialize
		void SoundLoader(bon::assets::IAsset* asset, void* context, void* extraData = nullptr)
		{
			// get asset path
			const char* path = asset->Path();
			BON_DLOG("Load sound effect from file: %s.", path);

			// load chunk
			Mix_Chunk* sound = Mix_LoadWAV(path);
			if (sound == NULL)
			{
				BON_ELOG("Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError());
				throw AssetLoadError(path);
			}

			// set handle
			SDLChunkHandle* handle = new SDLChunkHandle(sound);
			asset->_SetHandle(handle);
		}

		// sound disposer we set in the assets manager during asset disposal
		void SoundDisposer(bon::assets::IAsset* asset, void* context)
		{
			asset->_DestroyHandle<SDLChunkHandle>();
		}
		
		// set audio properties
		void SfxSdlWrapper::SetAudioProperties(int frequency, AudioFormats format, int channels, int audio_chunk_size)
		{
			int sdlformat = MIX_DEFAULT_FORMAT;
			switch (format){
				case AudioFormats::U8: sdlformat = AUDIO_U8; break;
				case AudioFormats::S8: sdlformat = AUDIO_S8; break;
				case AudioFormats::U16LSB: sdlformat = AUDIO_U16LSB; break;
				case AudioFormats::S16LSB: sdlformat = AUDIO_S16LSB; break;
				case AudioFormats::U16MSB: sdlformat = AUDIO_U16MSB; break;
				case AudioFormats::S16MSB: sdlformat = AUDIO_S16MSB; break;
			}
			AudioSpec::frequency = frequency;
			AudioSpec::format = sdlformat;
			AudioSpec::channelCount = channels;
			AudioSpec::chunkSize = audio_chunk_size;
		}

		// initialize sfx
		void SfxSdlWrapper::Initialize()
		{
			// initialize SDL and make sure succeed
			if (SDL_Init(SDL_INIT_AUDIO) < 0)
			{
				BON_ELOG("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
				throw InitializeError("Failed to initialize SDL sound drivers.");
			}

			// register the assets initializer for music
			bon::_GetEngine().Assets()._SetAssetsInitializer(bon::assets::AssetTypes::Music, MusicLoader, MusicDisposer, this);

			// register the assets initializer for sounds
			bon::_GetEngine().Assets()._SetAssetsInitializer(bon::assets::AssetTypes::Sound, SoundLoader, SoundDisposer, this);
		}

		// actually init audio device
		void SfxSdlWrapper::InitAudio()
		{
			// if was init, reset it
			if (_wasInit) {
			}

			// initialize SDL_mixer
			if (Mix_OpenAudio(AudioSpec::frequency, AudioSpec::format, AudioSpec::channelCount, AudioSpec::chunkSize) < 0)
			{
				BON_ELOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				throw InitializeError("SDL_mixer could not initialize!");
			}

			// allocate mix channels
			AudioSpec::allocatedMixChannelsCount = Mix_AllocateChannels(MIX_CHANNELS);

			// print spec and mark as initialized
			BON_DLOG("Initialize sfx: frequency=%d, format=%d, channels=%d, chunks_size=%d, mix_channels: %d.", AudioSpec::frequency, AudioSpec::format, AudioSpec::channelCount, AudioSpec::chunkSize, AudioSpec::allocatedMixChannelsCount);
			_wasInit = true;

			// update specs
			Custom_Mix_UpdateSpecs();
		}

		// play music track
		void SfxSdlWrapper::PlayMusic(MusicAsset music, int loops)
		{
			// get track and play it
			Mix_Music* sdlmusic = (Mix_Music*)(music->Handle()->Track);
			Mix_PlayMusic(sdlmusic, loops);
		}

		// set channel panning
		void SfxSdlWrapper::SetChannelPanning(SoundChannelId channel, float panLeft, float panRight)
		{
			Mix_SetPanning(channel, (Uint8)(std::min(panLeft, 1.0f) * 255), (Uint8)(std::min(panRight, 1.0f) * 255));
		}

		// set channel distance
		void SfxSdlWrapper::SetChannelDistance(SoundChannelId channel, float distance)
		{
			Mix_SetDistance(channel, (Uint8)(std::min(distance, 1.0f) * 255));
		}

		// pause / resume music
		void SfxSdlWrapper::PauseMusic(bool pause)
		{
			if (pause)
			{
				Mix_PauseMusic();
			}
			else
			{
				Mix_ResumeMusic();
			}
		}

		// set music volume
		void SfxSdlWrapper::SetMusicVolume(int volume)
		{
			Mix_VolumeMusic(max(volume, 0));
		}

		// make a passthru processor function that does nothing...
		void noEffect(int chan, void* stream, int len, void* udata)
		{
		}

		// start playing sound
		SoundChannelId SfxSdlWrapper::PlaySound(assets::SoundAsset sound, int volume, int loops, float pitch)
		{
			// get chunk and start playing
			Mix_Chunk* sdlchunk = (Mix_Chunk*)(sound->Handle()->Track);
			SoundChannelId channel = Mix_PlayChannel(-1, sdlchunk, loops);
			
			// if got a valid channel to play on (we might not get a channel if all are in use), set volume and pitch
			if (channel >= 0) {

				// set volume
				Mix_Volume(channel, volume);

				// set pitch
				if (pitch != 1.0f) {
					Custom_Mix_RegisterPlaybackSpeedEffect(channel, sdlchunk, pitch, loops, AudioSpec::format);
				}
				// disable previously set pitch
				else {
					Mix_RegisterEffect(channel, NULL, NULL, NULL);
				}
			}

			// return channel id
			return channel;
		}

		// set channel's volume
		void SfxSdlWrapper::SetVolume(SoundChannelId channel, int volume)
		{
			if (Mix_Playing(channel))
			{
				Mix_Volume(channel, max(volume, 0));
			}
		}

		// check if a given sound is playing on a channel
		bool SfxSdlWrapper::IsPlaying(SoundAsset sound, SoundChannelId channel) const
		{
			// get chunk
			Mix_Chunk* sdlchunk = (Mix_Chunk*)(sound->Handle()->Track);

			// check a single channel
			if (channel >= 0) 
			{
				return Mix_Playing(channel) && Mix_GetChunk(channel) == sdlchunk;
			}
			// check all channels
			else 
			{
				for (int i = 0; i < AudioSpec::allocatedMixChannelsCount; ++i) {
					if (IsPlaying(sound, i)) { return true; }
				}
			}

			// not playing
			return false;
		}

		// dispose sfx imp
		void SfxSdlWrapper::Dispose()
		{
			Mix_HaltChannel(-1);
			Mix_HaltMusic();
			Mix_CloseAudio();
			Mix_Quit();
		}
	}
}