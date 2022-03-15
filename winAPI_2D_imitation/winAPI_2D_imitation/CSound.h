#pragma once
#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")
#include "CResource.h"

using namespace FMOD;

class CSound : public CResource
{
private:

	Sound* m_pSound;
	Channel* m_pChannel;

public:
	CSound();
	~CSound();

	void Play();
	void Stop();
	void Pause();
	void Resume();

	bool IsPlay();
	bool IsPause();	

	void SetLoop(bool loop);

	void Load(const wstring& strFilePath);	
};

