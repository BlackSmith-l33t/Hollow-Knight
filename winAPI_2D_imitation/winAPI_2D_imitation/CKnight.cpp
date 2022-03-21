#include "framework.h"
#include "CKnight.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTile.h"

CKnight::CKnight()
{
	m_fVelocity = 400.f;
	m_fGravity = 200.f;

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KnightImg", L"texture\\Animation\\Knight\\Knight.png");
	SetName(L"Knight");
	//SetPos(fPoint(4000, 700));
	SetScale(fPoint(125.f, 125.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 100.f));
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

	/*CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"LeftMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
	pAni = GetAnimator()->FindAnimation(L"RightMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);*/
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
		pos.y += m_fVelocity * fDT;
	}

	SetPos(pos);

	if (KeyDown('Z'))
	{
		// TODO : 점프 구현
		GetAnimator()->Play(L"Jump");
	}

	/*	if (KeyUp(VK_RIGHT))
		{
			GetAnimator()->Play(L"None");
		}*/

	GetAnimator()->update();
}

void CKnight::render()
{
	component_render();
}

void CKnight::OnCollision(CCollider* _pOther)
{
	m_bGround = true;

	fPoint pos = GetPos();

	if (GROUP_GAMEOBJ::TILE == _pOther->GetObj()->GetObjType())
	{
		CTile* pTile = (CTile*)_pOther->GetObj();
		fVec2 vObjPos = pTile->GetPos();
		fVec2 vObjScale;

	}
}


void CKnight::OnCollisionEnter(CCollider* _pOther)
{
	m_bGround = true;
}

void CKnight::OnCollisionExit(CCollider* _pOther)
{

}

