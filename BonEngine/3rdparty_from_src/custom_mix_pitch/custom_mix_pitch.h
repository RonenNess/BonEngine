/*
 * custom_mix_pitch.h
 *
 *  Created on: 10 jan 2018
 *      Author: Carlos Faruolo
 */

#pragma once

// Register a proper playback speed effect handler for this channel according to the current audio format. Effect valid for the current (or next) playback only.
struct Mix_Chunk;
void Custom_Mix_RegisterPlaybackSpeedEffect(int channel, Mix_Chunk* chunk, float speed, int loop, Uint16 fmt);

// update sound specs after initializing sfx
void Custom_Mix_UpdateSpecs();