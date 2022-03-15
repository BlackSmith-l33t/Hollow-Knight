#include "framework.h"
#include "CSoundManager.h"
#include "CSound.h"


CSoundManager::CSoundManager()
{
	m_pSystem = nullptr;
}

CSoundManager::~ CSoundManager()
{
	m_pSystem->release();
	m_pSystem->close();
}

void CSoundManager::init()
{
	FMOD_RESULT result;
	result = System_Create(&m_pSystem);
	assert(!result);
	result = m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	assert(!result);
}

void CSoundManager::update()
{
	// Important!! update per frame
	m_pSystem->update();
}

System* CSoundManager::GetSystem()
{
	return m_pSystem;
}

void CSoundManager::AddSound(wstring keyName, wstring filePath, bool bgm)
{
	// TODO : 현재 다른 부분의 코드 구성들과 적용하여 아래 코드를 적용했을 시 m_mapSound는 항상 비어있음. 수정이 요구됨.
	/*if (m_mapSound.end() == m_mapSound.find(keyName))
	{
		return;
	}*/

	CSound* pSound = CResourceManager::getInst()->LoadSound(keyName, filePath);
	pSound->SetLoop(bgm);
	//m_pSystem->createStream
	m_mapSound.insert(make_pair(keyName, pSound));
}

void CSoundManager::Play(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter == m_mapSound.end())
	{
		return;
	}
	iter->second->Play();
}

void CSoundManager::Stop(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter == m_mapSound.end())
	{
		return;
	}
	iter->second->Stop();

}

void CSoundManager::Pause(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter == m_mapSound.end())
	{
		return;
	}
	iter->second->Pause();

}

void CSoundManager::Resume(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter == m_mapSound.end())
	{
		return;
	}
	iter->second->Resume();

}

bool CSoundManager::IsPlaySound(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter == m_mapSound.end())
	{
		assert(nullptr);
	}
	return iter->second->IsPlay();

}

bool CSoundManager::IsPauseSound(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter == m_mapSound.end())
	{
		assert(nullptr);
	}
	return iter->second->IsPause();
}
