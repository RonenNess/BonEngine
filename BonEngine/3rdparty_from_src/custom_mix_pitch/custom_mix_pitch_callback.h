/*
 * custom_mix_pitch_callback.h
 *
 *  Created on: 10 jan 2018
 *      Author: Carlos Faruolo
 */

#pragma warning(push, 0)   

// Mix_EffectFunc_t callback that redirects to handler method (handler passed via userData)
// Processing function to be able to change chunk speed/pitch.
// AudioFormatType depends on the current audio format (queryable via Mix_QuerySpec)
void Custom_Mix_PlaybackSpeedEffectFuncCallback(int mixChannel, void* stream, int length, void* userData)
{
	int frequency, channelCount;
	Mix_QuerySpec(&frequency, NULL, &channelCount);

	Custom_Mix_PlaybackSpeedEffectHandler* handler = (Custom_Mix_PlaybackSpeedEffectHandler*) userData;

	// take a "snapshot" of these values
	const float speedFactor = (handler->speed);

	const AudioFormatType* chunkData = (AudioFormatType*) handler->chunk->abuf;

	AudioFormatType* buffer = (AudioFormatType*) stream;

	const int bufferSize = length / sizeof(AudioFormatType);  // buffer size (as array)
	const int bufferDuration = Custom_Mix_ComputeChunkLengthMillisec(length);  // buffer time duration

	if(!handler->touched)  // if playback is still untouched
	{
		// if playback is still untouched and no pitch is requested this time, skip pitch routine and leave stream untouched.
		if(speedFactor == 1.0f)
		{
			// if there is still sound to be played
			if(handler->position < handler->duration or handler->loop)
			{
				// just update position
				handler->position += bufferDuration;

				// reset position if looping
				if (handler->loop) while (handler->position > handler->duration) {
					handler->position -= handler->duration;
				}
			}
			else  // if we already played the whole sound, halt channel
			{
				// set silence on the buffer since Mix_HaltChannel() poops out some of it for a few ms.
				for (int i = 0; i < bufferSize; i++) {
					buffer[i] = 0;
				}

				Mix_HaltChannel(mixChannel);
			}

			return;  // skipping pitch routine
		}
		// if pitch is required for the first time
		else
			handler->touched = 1;  // mark as touched and proceed to the pitch routine.
	}

	// if there is still sound to be played
	if(handler->position < handler->duration or handler->loop)
	{
		const float delta = 1000.0/frequency,   // normal duration of each sample
					delta2 = delta*speedFactor; // virtual stretched duration, scaled by 'speedFactor'

		for(int i = 0; i < bufferSize; i += channelCount)
		{
			const int j = i/channelCount; // j goes from 0 to size/channelCount, incremented 1 by 1
			const float x = handler->position + j*delta2;  // get "virtual" index. its corresponding value will be interpolated.
			const int k = floor(x / delta);  // get left index to interpolate from original chunk data (right index will be this plus 1)
			const float proportion = (x / delta) - k;  // get the proportion of the right value (left will be 1.0 minus this)

			// usually just 2 channels: 0 (left) and 1 (right), but who knows...
			for(int c = 0; c < channelCount; c++)
			{
				// check if k will be within bounds
				if(k*channelCount + channelCount - 1 < handler->chunkSize or handler->loop)
				{
					AudioFormatType  leftValue =  chunkData[(  k   * channelCount + c) % handler->chunkSize],
									 rightValue = chunkData[((k+1) * channelCount + c) % handler->chunkSize];

					// put interpolated value on 'data' (linear interpolation)
					buffer[i + c] = (1-proportion)*leftValue + proportion*rightValue;
				}
				else  // if k will be out of bounds (chunk bounds), it means we already finished; thus, we'll pass silence
				{
					buffer[i + c] = 0;
				}
			}
		}

		// update position
		handler->position += bufferDuration * speedFactor; // this is not exact since a frame may play less than its duration when finished playing, but its simpler

		// reset position if looping
		if (handler->loop) while (handler->position > handler->duration) {
			handler->position -= handler->duration;
		}
	}

	else  // if we already played the whole sound but finished earlier than expected by SDL_mixer (due to faster playback speed)
	{
		// set silence on the buffer since Mix_HaltChannel() poops out some of it for a few ms.
		for (int i = 0; i < bufferSize; i++) {
			buffer[i] = 0;
		}

		Mix_HaltChannel(mixChannel);
	}
}


#pragma warning(pop)