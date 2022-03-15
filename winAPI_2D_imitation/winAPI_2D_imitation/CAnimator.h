#pragma once

class CGameObject;
class CAnimation;
class CTexture;

class CAnimator
{
	friend class CGameObject;

private:
	map<wstring, CAnimation*>	m_mapAni;
	CAnimation*					m_pCurAni;
	CGameObject*				m_pOwner;

public:
	CAnimator();
	~CAnimator();

	CGameObject* GetObj();

	void update();
	void render(HDC hDC);

	void CreateAnimation(const wstring& strName, CTexture* tex, fPoint lt, fPoint slice,
						fPoint step, float duration, UINT frmCount);
	CAnimation* FindAnimation(const wstring& strName);
	void Play(const wstring& strName);
};

