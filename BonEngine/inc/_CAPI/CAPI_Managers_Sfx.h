/*****************************************************************//**
 * \file   CAPI_Managers_Sfx.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for sfx manager.
 *
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "CAPI_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* Set audio device properties.
	*/
	BON_DLLEXPORT void BON_Sfx_SetAudioProperties(int frequency, BON_AudioFormats format, bool stereo, int audio_chunk_size);

	/**
	* Play a music track.
	*/
	BON_DLLEXPORT void BON_Sfx_PlayMusic(bon::assets::MusicAsset* music, int volume, int loops);

	/**
	* Pause / resume currently played track.
	*/
	BON_DLLEXPORT void BON_Sfx_PauseMusic(bool pause);

	/**
	* Set music volume, or stop it.
	*/
	BON_DLLEXPORT void BON_Sfx_SetMusicVolume(int volume);

	/**
	* Stop playing music.
	*/
	BON_DLLEXPORT void BON_Sfx_StopMusic();

	/**
	* Play a sound effect.
	*/
	BON_DLLEXPORT int BON_Sfx_PlaySound(bon::assets::SoundAsset* sound, int volume, int loops, float pitch);

	/**
	* Play a sound effect.
	*/
	BON_DLLEXPORT int BON_Sfx_PlaySoundEx(bon::assets::SoundAsset* sound, int volume, int loops, float pitch, float panLeft, float panRight, float distance);

	/**
	* Set channel distance from listener (affect volume).
	*/
	BON_DLLEXPORT void BON_Sfx_SetChannelDistance(int channel, float distance);

	/**
	* Set the volume of a currently playing sound channel, or stop it if volume is 0.
	*/
	BON_DLLEXPORT void BON_Sfx_SetChannelVolume(int channel, int volume);

	/**
	* Set channel panning.
	*/
	BON_DLLEXPORT void BON_Sfx_SetChannelPanning(int channel, float panLeft, float panRight);

	/**
	* Stop playing a channel.
	*/
	BON_DLLEXPORT void BON_Sfx_StopChannel(int channel);

	/**
	* Set the master volume of music and sound effects.
	*/
	BON_DLLEXPORT void BON_Sfx_SetMasterVolume(int soundEffectsVolume, int musicVolume);

#ifdef __cplusplus
}
#endif