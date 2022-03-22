#include "framework.h"
#include "CKnight.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTile.h"

CKnight::CKnight()
{
	m_fVelocity		= 500.f;
	m_fAccel		= 0.f;
	m_fGravity		= 1000.f;
	m_fAccel_G		= 0.f;
	m_bGround		= false;

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KnightImg", L"texture\\Animation\\Knight\\Knight.png");
	SetName(L"Knight");
	SetScale(fPoint(125.f, 125.f));

	CreateGravity();
	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 90.f));
	//GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));

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
	update_move();
	update_ani();

	CCameraManager::getInst()->SetLookAt(GetPos());

	GetAnimator()->update();		
}

void CKnight::render()
{
	component_render();
}

void CKnight::update_move()
{
	fPoint pos = GetPos();

	if (Key(VK_LEFT))
	{
		pos.x -= m_fVelocity * fDT;
	}
	if (Key(VK_RIGHT))
	{
		pos.x += m_fVelocity * fDT;

	}
	if (Key(VK_UP))
	{
		// TODO : 카메라 시점 상단 변경
	}
	if (Key(VK_DOWN))
	{
		// TODO : 카메라 시점 하단 변경
		pos.y += m_fVelocity * fDT;		
	}

	if (KeyDown('Z'))
	{
		// TODO : JUMP
	}

	pos.y += m_fAccel_G * fDT;

	SetPos(pos);

	m_fAccel_G += Gravity * fDT;
	if (m_fAccel_G >= 800.f)
	{
		m_fAccel_G = 800.f;
	}
}

void CKnight::update_ani()
{
}

void CKnight::OnCollision(CCollider* _pOther)
{
}


void CKnight::OnCollisionEnter(CCollider* _pOther)
{		
}

void CKnight::OnCollisionExit(CCollider* _pOther)
{	
	CKnight* pKnight = (CKnight*)this;

	if (GROUP_GAMEOBJ::TILE == _pOther->GetObj()->GetObjType())
	{
		m_fAccel_G = 0.f;
	}
}

