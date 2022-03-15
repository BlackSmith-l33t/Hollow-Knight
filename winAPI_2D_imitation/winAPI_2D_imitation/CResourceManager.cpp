#include "framework.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CSound.h"

CResourceManager::CResourceManager()
{
	m_mapTex = {};
}

CResourceManager::~CResourceManager()
{
	// 자료구조에 저장된 모든 Texture 삭제
	for (map<wstring, CTexture*>::iterator iter = m_mapTex.begin(); iter != m_mapTex.end(); iter++)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
		}
	}
	m_mapTex.clear();

	for (map<wstring, CSound*>::iterator iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++)
	{
		// TODO : 사운드 삭제 진행
	}
}

CTexture* CResourceManager::FindTexture(const wstring& strKey)
{
	// Texture 키 값을 통해 탐색
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(strKey);
	
	if (m_mapTex.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

CTexture* CResourceManager::LoadTextrue(const wstring& strKey, const wstring& strRelativePath)
{
	// Texture를 불러오기 전 자료구조에 이미 Texture가 있는지 확인
	CTexture* pTex = FindTexture(strKey);
	if (nullptr != pTex)
	{
		return pTex;
	}
	
	// Texture 저장 경로 확인
	wstring strFilePath = CPathManager::getInst()->GetContentPath();
	strFilePath += strRelativePath;

	// Texture 생성 후 저장
	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(strKey);
	pTex->SetRelativePath(strRelativePath);

	m_mapTex.insert(make_pair(strKey, pTex));
	
	return pTex;
}

CTexture* CResourceManager::CreateTexture(const wstring& strKey, UINT width, UINT height)
{
	CTexture* pTex = FindTexture(strKey);
	if (nullptr != pTex)
	{
		return nullptr;
	}

	pTex = new CTexture();
	pTex->Create(width, height);
	pTex->SetKey(strKey);

	m_mapTex.insert(make_pair(strKey, pTex));
	return pTex;
}

CSound* CResourceManager::FindSound(const wstring& strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(strKey);

	if (m_mapSound.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

CSound* CResourceManager::LoadSound(const wstring& strKey, const wstring& strRelativePath)
{
	// Texture를 불러오기 전 자료구조에 이미 Texture가 있는지 확인
	CSound* pSound = FindSound(strKey);
	if (nullptr != pSound)
	{
		return pSound;
	}

	// Texture 저장 경로 확인
	wstring strFilePath = CPathManager::getInst()->GetContentRelativePath();
	strFilePath += strRelativePath;

	// Texture 생성 후 저장
	pSound = new CSound;
	pSound->Load(strFilePath);
	pSound->SetKey(strKey);
	pSound->SetRelativePath(strRelativePath);

	m_mapSound.insert(make_pair(strKey, pSound));

	return pSound;
}
