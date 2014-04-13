#include <TestGame/Include/Sound/SoundSource.h>

SoundSource::SoundSource()
{

}

SoundSource::~SoundSource()
{
	mSound->release();
}

void SoundSource::Initialize(char* lPath)
{
	mSound = FMODHandler::GetFMODHandler()->GetSound(lPath);
}

void SoundSource::Update()
{

}

void SoundSource::PlaySoundCustom()
{
	FMODHandler::GetFMODHandler()->GetFMODSystem()->playSound(mSound, 0, false, &mChannel);
	mChannel->setVolume(0.8);
	//FMODHandler::GetFMODHandler()->GetFMODSystem()->

	/*
	signed short* sptr = (signed short *)(void*)mSound; //Raw data ??
	for(int i = 0; i < 100; i++)
	{
		signed short b = sptr[i];
		int c = 5;
	}
	*/
}