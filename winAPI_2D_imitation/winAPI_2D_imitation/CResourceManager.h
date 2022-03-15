#pragma once

class CTexture;
class CSound;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	map<wstring, CTexture*> m_mapTex;		// Texture 리소스의 저장 자료구조
	map<wstring, CSound*> m_mapSound;
	CSound* m_pBGM;

public:
	CTexture* FindTexture(const wstring& strKey);	// 저장된 Texture 탐색
	CTexture* LoadTextrue(const wstring& strKey, const wstring& strRelativePath);	// Texture 불러오기 이미 있는 경우 있던 Texture 반환
	CTexture* CreateTexture(const wstring& strKey, UINT width, UINT height);

	CSound* FindSound(const wstring& strKey);  // 8시 강의 8시 27분
	CSound* LoadSound(const wstring& strKey, const wstring& strRelativePath);
};

