#include "framework.h"
#include "CKnight.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTile.h"

CKnight::CKnight()
{
	m_fVelocity = 400.f;
	m_fGravity = 1000.f;
	m_fAccel = 0.f;
	m_fAccelA = 0.f;
	m_bGround = true;

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KnightImg", L"texture\\Animation\\Knight\\Knight.png");
	SetName(L"Knight");
	SetPos(fPoint(200, 700));
	SetScale(fPoint(125.f, 125.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 90.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"None", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(0, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"LeftNone", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.5f, 4);
	GetAnimator()->CreateAnimation(L"RightNone", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.8f, 3);
	GetAnimator()->CreateAnimation(L"LeftMove", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"RightMove", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"LeftHit", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"RightHit", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"Jump", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);

	GetAnimator()->Play(L"None");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"LeftMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
	pAni = GetAnimator()->FindAnimation(L"RightMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
}

CKnight::~CKnight()
{
}

CKnight* CKnight::Clone()
{
	return new CKnight(*this);
}

void CKnight::update()
{	
	CCameraManager::getInst()->SetLookAt(GetPos());

	fPoint pos = GetPos();

	if (Key(VK_LEFT))
	{
		pos.x -= m_fVelocity * fDT;
		GetAnimator()->Play(L"LeftMove");
	}
	if (Key(VK_RIGHT))
	{
		pos.x += m_fVelocity * fDT;
		GetAnimator()->Play(L"RightNone");
	}
	if (Key(VK_UP))
	{
		pos.y -= m_fVelocity * fDT;
	}
	if (Key(VK_DOWN))
	{
		if (!m_bGround)
		{
			pos.y += m_fVelocity * fDT;
		}
	}

	if (KeyDown('Z'))
	{
		// TODO : 점프 구현
		GetAnimator()->Play(L"Jump");
	}

	pos.y += m_fAccelA * fDT;

	m_fAccelA += m_fGravity * fDT;

	GetAnimator()->update();
	SetPos(pos);
}

void CKnight::render()
{
	component_render();
}

void CKnight::OnCollision(CCollider* _pOther)
{
	if (GROUP_GAMEOBJ::TILE == _pOther->GetObj()->GetObjType())
	{
		CTile* pTile = (CTile*)_pOther->GetObj();
		CKnight* pKnight = (CKnight*)this;
		if (pTile->GetGroup() == GROUP_TILE::GROUND) return;

		if (GROUP_TILE::GROUND == pTile->GetGroup())
		{			
			fVec2 vPos = GetCollider()->GetFinalPos();
			fVec2 vScale = GetCollider()->GetScale();

			fVec2 vObjPos = _pOther->GetFinalPos();
			fVec2 vObjScale = _pOther->GetScale();

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vScale.y / 2.f + vObjScale.y / 2.f) - fLen;

			if ((vObjPos.y - vPos.y <= vScale.y / 2.f + vObjScale.y / 2.f))
			{
				m_fptPos.y -= fValue;
				SetPos(m_fptPos);				
			}
		}				
	}
}


void CKnight::OnCollisionEnter(CCollider* _pOther)
{	
	if (GROUP_GAMEOBJ::TILE == _pOther->GetObj()->GetObjType())
	{		
		CTile* pTile = (CTile*)_pOther->GetObj();
		CKnight* pKnight = (CKnight*)this;
	
		if (GROUP_TILE::GROUND == pTile->GetGroup())
		{
			m_bGround = true;
			fVec2 vPos = GetCollider()->GetFinalPos();
			fVec2 vScale = GetCollider()->GetScale();

			fVec2 vObjPos = _pOther->GetFinalPos();
			fVec2 vObjScale = _pOther->GetScale();

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vScale.y / 2.f + vObjScale.y / 2.f) - fLen;

			if ((vObjPos.y - vPos.y <= (vScale.y / 2.f + vObjScale.y / 2.f)))
			{			
				m_bGround = true;
				m_fptPos.y -= fValue;
				m_fAccelA = 0.f;
				SetPos(m_fptPos);
			}	
		}		
	}
}

void CKnight::OnCollisionExit(CCollider* _pOther)
{	
	CKnight* pKnight = (CKnight*)this;

	if (GROUP_GAMEOBJ::TILE == _pOther->GetObj()->GetObjType())
	{
		m_bGround = false;		
	}
}

