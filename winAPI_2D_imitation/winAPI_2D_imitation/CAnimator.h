#pragma once

class CGameObject;
class CAnimation;
class CD2DImage;

class CAnimator
{
	friend class CGameObject;

private:
	map<wstring, CAnimation*>	m_mapAni;
	CAnimation* m_pCurAni;
	CAnimation* m_pNextAni;
	CGameObject* m_pOwner;

	bool		m_bRepeat;

public:
	CAnimator();
	CAnimator(const CAnimator& pOther);
	~CAnimator();

	CGameObject* GetObj();
	
	void update();
	void render();


	void CreateAnimation(const wstring& strName, CD2DImage* tex, fPoint lt, fPoint slice,
		fPoint step, float duration, UINT frmCount, bool reverse = false);
	CAnimation* FindAnimation(const wstring& strName);
	void Play(const wstring& strName, bool bRepeat);
	void PlayNextAnimation(const wstring& strName, bool bRepeat, const wstring& strNextName);
};

