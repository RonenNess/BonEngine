#include <_CAPI/CAPI_Managers_Sfx.h>
#include <BonEngine.h>

/**
* Set audio device properties.
*/
void BON_Sfx_SetAudioProperties(int frequency, BON_AudioFormats format, bool stereo, int audio_chunk_size)
{
	bon::_GetEngine().Sfx().SetAudioProperties(frequency, (bon::AudioFormats)format, stereo, audio_chunk_size);
}

/**
* Play a music track.
*/
void BON_Sfx_PlayMusic(bon::assets::MusicAsset* music, int volume, int loops)
{
	return bon::_GetEngine().Sfx().PlayMusic(*music, volume, loops);
}

/**
* Pause / resume currently played track.
*/
void BON_Sfx_PauseMusic(bool pause)
{
	bon::_GetEngine().Sfx().PauseMusic(pause);
}

/**
* Set music volume, or stop it.
*/
void BON_Sfx_SetMusicVolume(int volume)
{
	bon::_GetEngine().Sfx().SetMusicVolume(volume);
}

/**
* Stop playing music.
*/
void BON_Sfx_StopMusic()
{
	bon::_GetEngine().Sfx().StopMusic();
}

/**
* Play a sound effect.
*/
int BON_Sfx_PlaySound(bon::assets::SoundAsset* sound, int volume, int loops, float pitch)
{
	return bon::_GetEngine().Sfx().PlaySound(*sound, volume, loops, pitch);
}

/**
* Play a sound effect.
*/
int BON_Sfx_PlaySoundEx(bon::assets::SoundAsset* sound, int volume, int loops, float pitch, float panLeft, float panRight, float distance)
{
	return bon::_GetEngine().Sfx().PlaySound(*sound, volume, loops, pitch, panLeft, panRight, distance);
}

/**
* Set channel distance from listener (affect volume).
*/
void BON_Sfx_SetChannelDistance(int channel, float distance)
{
	return bon::_GetEngine().Sfx().SetChannelDistance(channel, distance);
}

/**
* Set the volume of a currently playing sound channel, or stop it if volume is 0.
*/
void BON_Sfx_SetChannelVolume(int channel, int volume)
{
	return bon::_GetEngine().Sfx().SetChannelVolume(channel, volume);
}

/**
* Set channel panning.
*/
void BON_Sfx_SetChannelPanning(int channel, float panLeft, float panRight)
{
	return bon::_GetEngine().Sfx().SetChannelPanning(channel, panLeft, panRight);
}

/**
* Stop playing a channel.
*/
void BON_Sfx_StopChannel(int channel)
{
	return bon::_GetEngine().Sfx().StopChannel(channel);
}

/**
* Set the master volume of music and sound effects.
*/
void BON_Sfx_SetMasterVolume(int soundEffectsVolume, int musicVolume)
{
	return bon::_GetEngine().Sfx().SetMasterVolume(soundEffectsVolume, musicVolume);
}