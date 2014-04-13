#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H

#include "FMODHandler.h"

#define CLAMP(value, low, high) (((value)<(low))?(low):(((value)>(high))?(high):(value)))
class SoundSource
{
public:
	SoundSource();
	~SoundSource();

	void Initialize(char* lPath);
	void Update();	
	void PlaySoundCustom();

private:
	FMOD::Sound* mSound;
	FMOD::Channel* mChannel;

};

#endif