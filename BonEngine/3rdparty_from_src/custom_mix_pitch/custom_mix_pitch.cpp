/*
 * custom_mix_pitch.c
 *
 *  Created on: 10 jan 2018
 *      Author: Carlos Faruolo
 */
#include <../3rdparty/SDL2_mixer-2.0.4/include/SDL_mixer.h>
#include "custom_mix_pitch.h"

#include <iso646.h>
#include <stdio.h>
#include <math.h>

#define FORMAT_SAMPLE_SIZE(format) ((format & 0xFF) / 8)

// Get chunk time length (in ms) given its size and current audio format
int Custom_Mix_ComputeChunkLengthMillisec(int chunkSize)
{
	Uint16 fmt;
	int freq, chancnt;
	Mix_QuerySpec(&freq, &fmt, &chancnt);

	/* bytes / samplesize == sample points */
	const Uint32 points = chunkSize / FORMAT_SAMPLE_SIZE(fmt);

	/* sample points / channels == sample frames */
	const Uint32 frames = (points / chancnt);

	/* (sample frames * 1000) / frequency == play length, in ms */
	return ((frames * 1000) / freq);
}

/* Custom handler object to control which part of the Mix_Chunk's audio data will be played, with which pitch-related modifications. */
typedef struct Custom_Mix_PlaybackSpeedEffectHandler
{
	Mix_Chunk* chunk;
	float speed;  // ptr to the desired playback speed
	int position;  // current position of the sound, in ms
	int touched;  // false if this playback has never been pitched.

	// read-only!
	int loop;      // whether this is a looped playback
	int duration;  // the duration of the sound, in ms
	int chunkSize;  // the size of the sound, as a number of indexes (or sample points). thinks of this as a array size when using the proper array type (instead of just Uint8*).
}
Custom_Mix_PlaybackSpeedEffectHandler;

// "Constructor" for Custom_Mix_PlaybackSpeedEffectHandler
Custom_Mix_PlaybackSpeedEffectHandler* Custom_Mix_CreatePlaybackSpeedEffectHandler(float* speed, Mix_Chunk* chunk, int loop)
{
	Uint16 fmt;
	Mix_QuerySpec(NULL, &fmt, NULL);

	Custom_Mix_PlaybackSpeedEffectHandler* handler = new Custom_Mix_PlaybackSpeedEffectHandler();
	int duration = Custom_Mix_ComputeChunkLengthMillisec(chunk->alen);
	handler->chunk = chunk;
	handler->speed = *speed;
	handler->position = 0;
	handler->touched = 0;
	handler->loop = loop;
	handler->duration = duration;
	handler->chunkSize = chunk->alen / FORMAT_SAMPLE_SIZE(fmt);
	return handler;
}

// Playback speed altering function callbacks for different audio formats (fwd. declaring these just to prevent some IDE warnings...)
void Custom_Mix_PlaybackSpeedEffectFuncCallbackUint8 (int channel, void* stream, int length, void* userData);
void Custom_Mix_PlaybackSpeedEffectFuncCallbackSint8 (int channel, void* stream, int length, void* userData);
void Custom_Mix_PlaybackSpeedEffectFuncCallbackUint16(int channel, void* stream, int length, void* userData);
void Custom_Mix_PlaybackSpeedEffectFuncCallbackSint16(int channel, void* stream, int length, void* userData);
void Custom_Mix_PlaybackSpeedEffectFuncCallbackSint32(int channel, void* stream, int length, void* userData);
void Custom_Mix_PlaybackSpeedEffectFuncCallbackFloat (int channel, void* stream, int length, void* userData);

// implementation of Uint8 version of the callback
#define Custom_Mix_PlaybackSpeedEffectFuncCallback Custom_Mix_PlaybackSpeedEffectFuncCallbackUint8
#define AudioFormatType Uint8
#include "custom_mix_pitch_callback.h"
#undef Custom_Mix_PlaybackSpeedEffectFuncCallback
#undef AudioFormatType

// implementation of Sint8 version of the callback
#define Custom_Mix_PlaybackSpeedEffectFuncCallback Custom_Mix_PlaybackSpeedEffectFuncCallbackSint8
#define AudioFormatType Sint8
#include "custom_mix_pitch_callback.h"
#undef Custom_Mix_PlaybackSpeedEffectFuncCallback
#undef AudioFormatType

// implementation of Uint16 version of the callback
#define Custom_Mix_PlaybackSpeedEffectFuncCallback Custom_Mix_PlaybackSpeedEffectFuncCallbackUint16
#define AudioFormatType Uint16
#include "custom_mix_pitch_callback.h"
#undef Custom_Mix_PlaybackSpeedEffectFuncCallback
#undef AudioFormatType

// implementation of Sint16 version of the callback
#define Custom_Mix_PlaybackSpeedEffectFuncCallback Custom_Mix_PlaybackSpeedEffectFuncCallbackSint16
#define AudioFormatType Sint16
#include "custom_mix_pitch_callback.h"
#undef Custom_Mix_PlaybackSpeedEffectFuncCallback
#undef AudioFormatType

// implementation of Sint32 version of the callback
#define Custom_Mix_PlaybackSpeedEffectFuncCallback Custom_Mix_PlaybackSpeedEffectFuncCallbackSint32
#define AudioFormatType Sint32
#include "custom_mix_pitch_callback.h"
#undef Custom_Mix_PlaybackSpeedEffectFuncCallback
#undef AudioFormatType

// implementation of Float version of the callback
#define Custom_Mix_PlaybackSpeedEffectFuncCallback Custom_Mix_PlaybackSpeedEffectFuncCallbackFloat
#define AudioFormatType float
#include "custom_mix_pitch_callback.h"
#undef Custom_Mix_PlaybackSpeedEffectFuncCallback
#undef AudioFormatType

// Mix_EffectDone_t callback that deletes the handler at the end of the effect usage  (handler passed via userData)
void Custom_Mix_PlaybackSpeedEffectDoneCallback(int channel, void *userData)
{
	delete userData;
}

// Register a proper playback speed effect handler for this channel according to the current audio format. Effect valid for the current (or next) playback only.
void Custom_Mix_RegisterPlaybackSpeedEffect(int channel, Mix_Chunk* chunk, float* speed, int loop, Uint16 fmt)
{
	Mix_EffectFunc_t effect_func_callback;

	// select the register function for the current audio format and register the effect using the compatible handlers
	// xxx is it correct to behave the same way to all S16 and U16 formats? Should we create case statements for AUDIO_S16SYS, AUDIO_S16LSB, AUDIO_S16MSB, etc, individually?
	switch(fmt)
	{
		case AUDIO_U8:  effect_func_callback = Custom_Mix_PlaybackSpeedEffectFuncCallbackUint8;  break;
		case AUDIO_S8:  effect_func_callback = Custom_Mix_PlaybackSpeedEffectFuncCallbackSint8;  break;
		case AUDIO_U16: effect_func_callback = Custom_Mix_PlaybackSpeedEffectFuncCallbackUint16; break;
		default:
		case AUDIO_S16: effect_func_callback = Custom_Mix_PlaybackSpeedEffectFuncCallbackSint16; break;
		case AUDIO_S32: effect_func_callback = Custom_Mix_PlaybackSpeedEffectFuncCallbackSint32; break;
		case AUDIO_F32: effect_func_callback = Custom_Mix_PlaybackSpeedEffectFuncCallbackFloat;  break;
	}

	Mix_RegisterEffect(channel, effect_func_callback, Custom_Mix_PlaybackSpeedEffectDoneCallback, Custom_Mix_CreatePlaybackSpeedEffectHandler(speed, chunk, loop));
}
