#include "framework.h"
#include "CKnight.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTile.h"
#include "CMissile.h"
#include "CNail.h"

CKnight* CKnight::instance = nullptr;

CKnight::CKnight()
{
	// Init
	pNail = new CNail;

	m_fvVelocity = { 0.f, 0.f };

	m_iCurDir = 1;
	m_iPrevDir = 0;
	m_fAttackTimer = 0.f;
	m_fAttackTimeLimit = 450.f;
	m_fMissileAttackTimeLimit = 1700.f;
	m_fMissileStartCoolTime = 800.f;
	m_iMissileActionCount = 0;
	m_iMissileCount = 0;
	m_fGravity = 1000.f;
	m_fGAccel = 0.f;
	m_fJump = -800.f;
	m_fMaxVelocity = 500.f;	

	m_bAlive = true;
	m_bLeft = false;
	m_bAttack = false;

	m_eCurState = PLAYER_STATE::IDLE;

	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KnightImg", L"texture\\Animation\\Knight\\knight_animation3.png");
	SetName(L"Knight");
	SetScale(fPoint(130.f, 130.f));

	CreateGravity();
	CreateCollider();
	GetCollider()->SetScale(fPoint(35.f, 130.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Idle_Left", m_pImg, fPoint(0.f, 0.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.2f, 4, true);
	GetAnimator()->CreateAnimation(L"Idle_Right", m_pImg, fPoint(0.f, 0.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.2f, 4);

	GetAnimator()->CreateAnimation(L"Move_Left", m_pImg, fPoint(0.f, 130.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.09f, 6, true);
	GetAnimator()->CreateAnimation(L"Move_Right", m_pImg, fPoint(0.f, 130.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.09f, 6);

	GetAnimator()->CreateAnimation(L"Jump_Left", m_pImg, fPoint(0.f, 260.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.1f, 7, true);
	GetAnimator()->CreateAnimation(L"Jump_Right", m_pImg, fPoint(0.f, 260.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.1f, 7);

	GetAnimator()->CreateAnimation(L"Fall_Left", m_pImg, fPoint(0.f, 390.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.1f, 5, true);
	GetAnimator()->CreateAnimation(L"Fall_Right", m_pImg, fPoint(0.f, 390.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.1f, 5);

	GetAnimator()->CreateAnimation(L"Attack_Left", m_pImg, fPoint(0.f, 520.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.07f, 6, true);
	GetAnimator()->CreateAnimation(L"Attack_Right", m_pImg, fPoint(0.f, 520.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.07f, 6);

	GetAnimator()->CreateAnimation(L"MissileMotion_Left",  m_pImg, fPoint(0.f, 780.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.1f, 9, true);
	GetAnimator()->CreateAnimation(L"MissileMotion_Right", m_pImg, fPoint(0.f, 780.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.1f, 9);

	GetAnimator()->CreateAnimation(L"Dead_Pose_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(130.f, 0.f), 0.8f, 11, true);
	GetAnimator()->CreateAnimation(L"Dead_Pose_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.8f, 3);

	GetAnimator()->CreateAnimation(L"Demaged_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1, true);
	GetAnimator()->CreateAnimation(L"Demaged_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);

	GetAnimator()->CreateAnimation(L"HP_Charge_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1, true);
	GetAnimator()->CreateAnimation(L"HP_Charge_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);

	GetAnimator()->CreateAnimation(L"AttackUp_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1, true);
	GetAnimator()->CreateAnimation(L"AttackUP_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"AttackDown_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1, true);
	GetAnimator()->CreateAnimation(L"AttackDown_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);

	GetAnimator()->CreateAnimation(L"LookUP_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.5f, 4, true);
	GetAnimator()->CreateAnimation(L"LookUP_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.5f, 4);
	GetAnimator()->CreateAnimation(L"LookDown_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.5f, 4, true);
	GetAnimator()->CreateAnimation(L"LookDown_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.5f, 4);

	GetAnimator()->Play(L"Idle_Right", false);


	/*pAni = GetAnimator()->FindAnimation(L"Idle_Left");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
	pAni = GetAnimator()->FindAnimation(L"Idle_Right");
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

	if (Key(VK_SPACE)) // ???????? ?????? ????
	{
		this->SetPos(fPoint(3000, 1700.f));
		m_bWallLeft = false;
		m_bWallRight = false;
		m_bWallBottom = false;
	}

	//CCameraManager::getInst()->SetLookAt(GetPos());

	GetAnimator()->update();
	
	//m_ePrevState = m_eCurState;
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

#pragma region Update State
void CKnight::update_state()
{
	if (m_fvVelocity.x == 0 && m_bCurGround && 
		m_eCurState != PLAYER_STATE::ATTACK && 
		m_eCurState != PLAYER_STATE::JUMP   &&
		m_eCurState != PLAYER_STATE::SOULMISSILE)
	{
		m_eCurState = PLAYER_STATE::IDLE;
		m_bAttack = false;	
		m_fAttackTimer = 0;
		m_iMissileActionCount = 0;
		m_iMissileCount = 0;
	}

	if (m_eCurState == PLAYER_STATE::ATTACK && m_fAttackTimer >= m_fAttackTimeLimit)
	{		
		m_bAttack = false;
		m_eCurState = PLAYER_STATE::IDLE;
		m_fAttackTimer = 0;
	}

	if (m_eCurState == PLAYER_STATE::SOULMISSILE && m_fAttackTimer >= m_fMissileAttackTimeLimit)
	{
		m_bAttack = false;
		m_eCurState = PLAYER_STATE::IDLE;
		m_fAttackTimer = 0;
	}
	
	if (!m_bCurGround && m_eCurState != PLAYER_STATE::JUMP)
	{
		m_eCurState = PLAYER_STATE::FALL;
	}

	if (Key(VK_LEFT))
	{
		m_bLeft = true;
		if (m_eCurState != PLAYER_STATE::JUMP && m_eCurState != PLAYER_STATE::FALL && m_eCurState != PLAYER_STATE::ATTACK)
		{
			m_eCurState = PLAYER_STATE::MOVE;
		}

		if (KeyDown('X'))
		{
			m_eCurState = PLAYER_STATE::ATTACK;
			m_bAttack = true;
			Attack();
		}
	}
	if (Key(VK_RIGHT))
	{
		m_bLeft = false;
		if (m_eCurState != PLAYER_STATE::JUMP && m_eCurState != PLAYER_STATE::FALL && m_eCurState != PLAYER_STATE::ATTACK)
		{
			m_eCurState = PLAYER_STATE::MOVE;
		}

		if (Key(VK_RIGHT) && KeyDown('X'))
		{
			m_eCurState = PLAYER_STATE::ATTACK;
			m_bAttack = true;
			Attack();
		}
	}
	if (Key(VK_UP) && !m_bAttack)
	{
		m_eCurState = PLAYER_STATE::LOOKUP;
	}
	if (Key(VK_DOWN) && !m_bAttack)
	{
		m_eCurState = PLAYER_STATE::LOOKDOWN;
	}

	if (KeyDown('Z') && m_bCurGround)
	{
		if (m_eCurState != PLAYER_STATE::ATTACK)
		{
			m_eCurState = PLAYER_STATE::JUMP;
		}
	}

	if (KeyDown('X'))
	{	
		m_eCurState = PLAYER_STATE::ATTACK;
		m_bAttack = true;
		Attack(); 
	}	

	if (KeyDown('A') && m_bCurGround)
	{
		m_eCurState = PLAYER_STATE::SOULCHARGE;
	}

	if (KeyDown('C') && 0 == m_iMissileCount && 0 == m_iMissileActionCount)
	{
		m_eCurState = PLAYER_STATE::SOULMISSILE;
		m_bAttack = true;	
		m_iMissileActionCount++;
		

		//CreateSoulMissile();
	}

	if (KeyDown('B'))
	{
		// TODO : ???????? UI
	}

	if (KeyDown(VK_ESCAPE))
	{
		// TODO : ???? ButtonUI
	}

	m_ePrevState = m_eCurState;
}
#pragma endregion

#pragma region Update Move
void CKnight::update_move()
{
	fPoint pos = GetPos();

	m_fvVelocity = { 0.f, 0.f };

	// TODO : ?????????? ???????? ???? ??????????.
	CCameraManager::getInst()->SetLookAt(fPoint(this->GetPos().x, this->GetPos().y));

	m_fptCurView = CCameraManager::getInst()->GetLookAt();

	// ?????????? ?????? ?????? ??
	if (m_eCurState == PLAYER_STATE::DAMAGED)
	{
		if (m_bLeft)
		{
			m_fvVelocity.x -= 100.f;
			m_iCurDir = -1;
		}
		else
		{
			m_fvVelocity.x += 100.f;
			m_iCurDir = 1;
		}
	}

	if (Key(VK_LEFT))
	{
		if (!m_bWallRight)
		{
			m_fvVelocity.x += 400.f;
			m_iCurDir = -1;
			m_bLeft = true;
		}
	}
	if (Key(VK_RIGHT))
	{
		if (!m_bWallLeft)
		{
			m_fvVelocity.x += 400.f;
			m_iCurDir = 1;
			m_bLeft = false;
		}
	}
	if (Key(VK_UP) && !m_bAttack && m_bCurGround)
	{
		// TODO : ?????? ?????? ???? (???? ?????? ???? ?????? ????????)
		m_fptCurView.y -= 10.f;
		CCameraManager::getInst()->SetLookAt(fPoint(this->GetPos().x, this->GetPos().y - m_fptCurView.y));

		if (KeyUp(VK_UP) && !m_bAttack)
		{
			m_fptCurView.y += 10.f;
			CCameraManager::getInst()->SetLookAt(fPoint(this->GetPos().x, m_fptCurView.y + m_fptCurView.y));
		}
	}
	if (Key(VK_DOWN) && !m_bAttack && m_bCurGround)
	{
		// TODO : ?????? ?????? ?????? (???? ?????? ???? ?????? ????????)
		m_fptCurView.y += 10.f;
		CCameraManager::getInst()->SetLookAt(fPoint(this->GetPos().x, this->GetPos().y + m_fptCurView.y));

		if (KeyUp(VK_DOWN) && !m_bAttack)
		{
			m_fptCurView.y -= 10.f;
		}
	}
	// JUMP 
	if (KeyDown('Z') && m_bCurGround)
	{
		m_fptPos.y -= 1.f;
		m_fvVelocity.y = -900.f;
		m_fGAccel += m_fvVelocity.y;
		//pos.y += m_fGAccel * fDT;
		m_bJump = true;
		//Logger::debug(L"Jump");
	}

	//FALL
	if (m_ePrevState == PLAYER_STATE::JUMP && m_fGAccel > 0.f)
	{
		m_fGAccel = 400.f;
		m_bJump = false;
		m_eCurState = PLAYER_STATE::FALL;
		Logger::debug(L"Fall");

		if (Key(VK_LEFT))
		{
			if (!m_bWallRight)
			{
				m_fvVelocity.x += 400.f;
				m_iCurDir = -1;
				m_bLeft = true;
			}
		}
		if (Key(VK_RIGHT))
		{
			if (!m_bWallLeft)
			{
				m_fvVelocity.x += 400.f;
				m_iCurDir = 1;
				m_bLeft = false;
			}
		}
	}

	// Missile
	if (m_eCurState == PLAYER_STATE::SOULMISSILE && m_fAttackTimer >= m_fMissileStartCoolTime && 1 == m_iMissileActionCount)
	{
		CreateSoulMissile();	
		m_iMissileActionCount = 0;
		m_iMissileCount = 1;
	}
	pos.x += m_iCurDir * m_fvVelocity.x * fDT;
	pos.y += m_fGAccel * fDT;

	SetPos(pos);

	m_fGAccel += Gravity * fDT;	

	if (m_fGAccel >= 2000.f)
	{
		m_fGAccel = 2000.f;
	}
	if (m_fMaxVelocity <= m_fvVelocity.x || m_fMaxVelocity <= m_fvVelocity.y)
	{
		m_fvVelocity.x = m_fMaxVelocity;
		m_fvVelocity.y = m_fMaxVelocity;
	}

	//m_sPrevDir = m_sCurDir;
}

#pragma endregion

#pragma region Update Ainmation
void CKnight::update_animation()
{
	/*if (m_ePrevState == m_eCurState && m_sPrevDir == m_sCurDir)
	{
		return;
	}*/
	
	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
		if (m_fvVelocity.x == 0 && m_eCurState != PLAYER_STATE::JUMP)
		{
			if (m_iCurDir == -1)
			{
				GetAnimator()->Play(L"Idle_Left", true);
			}
			else
			{
				GetAnimator()->Play(L"Idle_Right", true);
			}
		}
		break;
	case PLAYER_STATE::MOVE:
		if (m_iCurDir == -1)
		{
			if (m_fvVelocity.x > 0)
			{
				GetAnimator()->Play(L"Move_Left", true);
			}
			else
			{
				GetAnimator()->Play(L"Idle_Left", true);
			}
		}
		else
		{
			if (m_fvVelocity.x > 0)
			{
				GetAnimator()->Play(L"Move_Right", true);
			}
			else
			{
				GetAnimator()->Play(L"Idle_Right", true);
			}
		}
		break;
	case PLAYER_STATE::JUMP:

		if (m_iCurDir == -1)
		{
			GetAnimator()->Play(L"Jump_Left", false);
		}
		else if (m_iCurDir == 1)
		{
			GetAnimator()->Play(L"Jump_Right", false);
		}
		break;
	case PLAYER_STATE::FALL:
		if (m_iCurDir == -1)
		{
			GetAnimator()->Play(L"Fall_Left", false);		
		}
		else
		{
			GetAnimator()->Play(L"Fall_Right", false);		
		}
		break;
	case PLAYER_STATE::ATTACK:
		if (m_iCurDir == -1)
		{
			GetAnimator()->Play(L"Attack_Left", false);		
			m_fAttackTimer++;
		}
		else
		{
			GetAnimator()->Play(L"Attack_Right", false);				
			m_fAttackTimer++;
		}
		break;
	case PLAYER_STATE::DAMAGED:
		if (m_iCurDir == -1 && m_bDamaged)
		{
			GetAnimator()->Play(L"Demaged_Left", false);
		}
		else if (m_iCurDir == 1 && m_bDamaged)
		{
			GetAnimator()->Play(L"Demaged_Right", false);
		}
		break;
	case PLAYER_STATE::SOULMISSILE:
		if (m_iCurDir == -1)
		{
			GetAnimator()->Play(L"MissileMotion_Left", false);
			m_fAttackTimer++;
		}
		else
		{
			GetAnimator()->Play(L"MissileMotion_Right", false);
			m_fAttackTimer++;
		}
		break;
	case PLAYER_STATE::LOOKUP:
		if (m_iCurDir == -1)
		{
			GetAnimator()->Play(L"LookUP_Left", false);
		}
		else
		{
			GetAnimator()->Play(L"LookUP_Right", false);
		}
		break;
	case PLAYER_STATE::LOOKDOWN:
		if (m_iCurDir == -1)
		{
			GetAnimator()->Play(L"LookDown_Left", false);
		}
		else
		{
			GetAnimator()->Play(L"LookDown_Right", false);
		}
		break;
	case PLAYER_STATE::SOULCHARGE:
		if (m_iCurDir == -1)
		{
			GetAnimator()->Play(L"HP_Charge_Left", false);
		}
		else
		{
			GetAnimator()->Play(L"HP_Charge_Right", false);
		}
		break;
	case PLAYER_STATE::DEAD:
		if (m_iCurDir == -1)
		{
			GetAnimator()->Play(L"Dead_Pose_Left", false);
		}
		else
		{
			GetAnimator()->Play(L"Dead_Pose_Right", false);
		}
		break;

	default:
		break;
	}
}

void CKnight::OnCollision(CCollider* _pOther)
{
	
}

void CKnight::OnCollisionEnter(CCollider* _pOther)
{	
	CGameObject* pOtherObj = _pOther->GetObj();

	if (GROUP_GAMEOBJ::GROUND == pOtherObj->GetObjType())
	{
		fVec2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}

		if (m_bWallBottom)
		{
			m_bFall = true;
			m_eCurState = PLAYER_STATE::FALL;
		}
	}
}



void CKnight::OnCollisionExit(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetObjType() == GROUP_GAMEOBJ::MONSTER ||
		_pOther->GetObj()->GetObjType() == GROUP_GAMEOBJ::MONSTER_MISSILE)
	{
		m_bDamaged = false;
	}
	
	CGameObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::GROUND)
	{
		m_bPrevGround = m_bCurGround;
		m_bCurGround = false;
	}

	m_bWallLeft = false;
	m_bWallRight = false;
	m_bWallBottom = false;
}

void CKnight::Attack()
{	
	fPoint fptNailPos = GetPos();
	fPoint fptHandPos = fPoint(m_fptPos.x, m_fptPos.y);

	// Nail Object		
	pNail = new CNail;
	if (1 == m_iCurDir)
	{
		pNail->SetPos(fPoint(fptHandPos.x + 40.f, fptHandPos.y + 25.f));
	}
	else
	{
		pNail->SetPos(fPoint(fptHandPos.x - 40.f, fptHandPos.y + 25.f));
	}

	pNail->SetName(L"Nail_Player");
	CreateObj(pNail, GROUP_GAMEOBJ::NAIL);
}

void CKnight::CreateSoulMissile()
{
	// TODO : ???????? ???????? ???????? ?????? ?????? ???? ????

	fPoint fpMissilePos = m_fptPos;
	int iMissileOffSetX = 150;
	int iMissileOffSetY = 20;

	// Misiile Object
	CMissile* pMissile = new CMissile;

	if (0 < m_iCurDir)
	{
		pMissile->SetPos(fPoint(fpMissilePos.x + iMissileOffSetX, fpMissilePos.y + iMissileOffSetY));
		pMissile->SetDir(fVec2(m_iCurDir, 0));
	}
	else
	{
		pMissile->SetPos(fPoint(fpMissilePos.x - iMissileOffSetX, fpMissilePos.y + iMissileOffSetY));
		pMissile->SetDir(fVec2(m_iCurDir, 0));
	}
	
	pMissile->SetName(L"Missile_Player");

	CreateObj(pMissile, GROUP_GAMEOBJ::SOUL_MISSILE);
	pMissile->SetObjType(GROUP_GAMEOBJ::SOUL_MISSILE);
}


