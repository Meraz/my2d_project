#include <TestGame/Include/Sound/SoundHandler.h>


SoundHandler::SoundHandler()
{
	mSource = std::vector<SoundSource*>();
}


SoundHandler::~SoundHandler()
{
	
}


void SoundHandler::Initialize()
{
	
}


void SoundHandler::AddSource(char* lPath)
{
	SoundSource* lSource = new SoundSource();
	lSource->Initialize(lPath);
	mSource.push_back(lSource);
}


void SoundHandler::PlaySoundCustom()
{
	for(int i = 0; i < mSource.size(); i++)
	{
		mSource.at(i)->PlaySoundCustom();
	}
}

void SoundHandler::Update()
{
	for(int i = 0; i < mSource.size(); i++)
	{
	//	mSource.at(i)->Update();
	}
}