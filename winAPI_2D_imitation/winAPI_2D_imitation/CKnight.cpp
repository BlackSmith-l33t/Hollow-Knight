#include "framework.h"
#include "CKnight.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTile.h"
#include "CMissile.h"

CKnight* CKnight::instance = nullptr;

CKnight::CKnight()
{
	m_fSpeed		= 300.f;
	m_fvVelocity	= { 0.f, 0.f };
	m_fGravity		= 1000.f;
	m_fAccel		= 0.f;
	m_fGAccel		= 0.f;
	m_fFriction		= 200.f;
	m_fJump			= 700.f;
	m_bAlive		= true;
	m_bLeft			= false;
	m_bAttack		= false;

	m_fptCurView = CCameraManager::getInst()->GetLookAt();

	m_eCurState = PLAYER_STATE::IDLE;

	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KnightImg", L"texture\\Animation\\Knight\\Knight.png");
	SetName(L"Knight");
	SetScale(fPoint(125.f, 125.f));

	CreateGravity();
	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 90.f));
	//GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Start_Pose",      m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.8f, 3);
	GetAnimator()->CreateAnimation(L"RightNone",       m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.8f, 3);
	GetAnimator()->CreateAnimation(L"LeftNone",		   m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.5f, 4);

	GetAnimator()->CreateAnimation(L"LeftMove",		   m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"RightMove",	   m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"Jump",			   m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"LongJump",		   m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"Fall",			   m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"Be_hit",		   m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);

	GetAnimator()->CreateAnimation(L"LeftHit",		   m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"RightHit",		   m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);	
	GetAnimator()->CreateAnimation(L"SoulMissile",	   m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"JumpAttack",      m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"JumpDownAttack",  m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"HP_Charge",       m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);

	GetAnimator()->Play(L"Start_Pose");

	/*CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"LeftMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
	pAni = GetAnimator()->FindAnimation(L"RightMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);*/
}

CKnight::~CKnight()
{
	instance = nullptr;

	if (nullptr != CCameraManager::getInst()->GetTarget())
	{
		CCameraManager::getInst()->SetTargetObj(nullptr);
	}
}

CKnight* CKnight::Clone()
{
	return new CKnight(*this);
}

void CKnight::update()
{	
	update_state();
	update_move();
	update_animation();
		
	CCameraManager::getInst()->SetLookAt(GetPos());

	GetAnimator()->update();		
}

void CKnight::render()
{
	component_render();
}

void CKnight::RegisterPlayer()
{
	instance = this;
}

CKnight* CKnight::GetPlayer()
{
	return instance;
}

void CKnight::update_state()
{
  /*IDle,
	WAIK,
	JUMP,
	FALL,
	ATTACK,
	DEAD,*/

	if (Key(VK_LEFT) && m_bGround)
	{
		m_eCurState = PLAYER_STATE::WAIK;		
		m_bLeft = true;
	}
	if (Key(VK_RIGHT))
	{
		m_eCurState = PLAYER_STATE::WAIK;
		m_bLeft = false;
	}
	if (Key(VK_UP) && !m_bAttack)
	{	

	}
	if (Key(VK_DOWN) && !m_bAttack)
	{
		
	}

	if (KeyDown('Z') && m_bGround)
	{
		
	}


}

void CKnight::update_move()
{
	fPoint pos = GetPos();
	

	if (Key(VK_LEFT))
	{
		pos.x -= m_fSpeed * fDT;
		m_bLeft = true;
	
	}
	if (Key(VK_RIGHT))
	{
		pos.x += m_fSpeed * fDT;
		m_bLeft = false;
		
	}
	if (Key(VK_UP) && !m_bAttack)
	{		
		// TODO : 카메라 시점을 위로 
		//CCameraManager::getInst()->SetLookAt(fPoint(this->GetPos().x, this->GetPos().y - 500));	
		
	}
	if (Key(VK_DOWN)&& !m_bAttack)
	{
		// TODO : 카메라 시점을 아래로
		//::getInst()->SetLookAt(fPoint(this->GetPos().x, this->GetPos().y + 500));	
	}

	if (KeyDown('Z') && m_bGround)
	{		
		if (Key(VK_LEFT))
		{
			pos.x -= m_fSpeed * fDT;
			m_bLeft = true;
		}
		if (Key(VK_RIGHT))
		{
			pos.x += m_fSpeed * fDT;
			m_bLeft = false;
		}

		m_bGround = false;
		m_fGAccel -= m_fJump;
		Logger::debug(L"Jump");
	}

	pos.y += m_fGAccel * fDT;

	SetPos(pos);

	m_fGAccel += Gravity * fDT;

	if (m_fGAccel >= 800.f)
	{
		m_fGAccel = 800.f;
	}
}

void CKnight::update_animation()
{

}

void CKnight::OnCollisionExit(CCollider* _pOther)
{	

}

void CKnight::CreateMissile()
{
	fPoint fpMissilePos = GetPos();
	fpMissilePos.x += GetScale().x / 2.f;

	// Misiile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(fpMissilePos);
	pMissile->SetDir(fVec2(1, 0));
	pMissile->SetName(L"Missile_Player");

	CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
}


