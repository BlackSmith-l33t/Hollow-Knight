#include "framework.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
{
	m_mapAni = {};
	m_pCurAni = nullptr;
	m_pNextAni = nullptr;
	m_pOwner = nullptr;
	m_bRepeat = false;	
	m_iFrameIndex = 0;
}

CAnimator::CAnimator(const CAnimator& pOther)
{
	for (map<wstring, CAnimation*>::const_iterator iter = pOther.m_mapAni.begin(); iter != pOther.m_mapAni.end(); iter++)
	{
		CAnimation* newAni = new CAnimation(*iter->second);
		m_mapAni.insert(make_pair(newAni->GetName(), newAni));
		newAni->m_pAnimator = this;
	}
	m_pCurAni = FindAnimation(pOther.m_pCurAni->GetName());
	m_pOwner = nullptr;
}

CAnimator::~CAnimator()
{
	for (map<wstring, CAnimation*>::iterator iter = m_mapAni.begin(); iter != m_mapAni.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapAni.clear();
}

CGameObject* CAnimator::GetObj()
{
	return m_pOwner;
}

void CAnimator::update()
{
	if (nullptr != m_pCurAni)
	{
		m_pCurAni->update();

		if (m_bRepeat && m_pCurAni->IsFinish())
		{
			m_pCurAni->SetFrame(0);
		}
		else if (!m_bRepeat && m_pCurAni->IsFinish() && nullptr != m_pNextAni)
		{
			m_pCurAni->SetFrame(0);
			m_pCurAni = m_pNextAni;
			m_pNextAni = nullptr;
			m_pCurAni->SetFrame(0);
			m_bRepeat = false;
		}
	}
}

void CAnimator::render()
{
	if (nullptr != m_pCurAni)
	{
		m_pCurAni->render();
	}
}

void CAnimator::CreateAnimation(const wstring& strName, CD2DImage* tex, fPoint lt, fPoint slice, fPoint step, float duration, UINT frmCount, bool reverse)
{
	CAnimation* pAni = FindAnimation(strName);
	assert(nullptr == pAni);

	pAni = new CAnimation;

	pAni->SetName(strName);
	pAni->m_pAnimator = this;
	pAni->Create(tex, lt, slice, step, duration, frmCount);
	pAni->m_bReverse = reverse;

	m_mapAni.insert(make_pair(strName, pAni));
}

CAnimation* CAnimator::FindAnimation(const wstring& strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAni.find(strName);

	if (iter == m_mapAni.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CAnimator::Play(const wstring& strName, bool bRepeat)
{
	if (m_pCurAni == FindAnimation(strName))
	{
		return;
	}
	m_pCurAni = FindAnimation(strName);
	m_pCurAni->m_iCurFrm = 0;
	m_bRepeat = bRepeat;
}

void CAnimator::PlayNextAnimation(const wstring& strName, bool bRepeat, const wstring& strNextName)
{
	if (m_pCurAni == FindAnimation(strName))
	{
		return;
	}
	m_pCurAni = FindAnimation(strName);
	m_pNextAni = FindAnimation(strNextName);
	m_pCurAni->m_iCurFrm = 0;
	m_bRepeat = bRepeat;
}
