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
	m_fvVelocity = { 0.f, 0.f };
	m_sCurDir = 1;
	m_sPrevDir = 0;
	m_fGravity = 1000.f;
	m_fGAccel = 0.f;
	m_fJump = -800.f;
	m_MaxVelocity = 500.f;
	m_bAlive = true;
	m_bLeft = false;
	m_bAttack = false;


	m_eCurState = PLAYER_STATE::START;

	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KnightImg", L"texture\\Animation\\Knight\\Knight.png");
	SetName(L"Knight");
	SetScale(fPoint(125.f, 125.f));

	CreateGravity();
	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 90.f));
	//GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Start_Pose", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.8f, 3);
	GetAnimator()->CreateAnimation(L"Dead_Pose_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.8f, 3, true);
	GetAnimator()->CreateAnimation(L"Dead_Pose_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.8f, 3);

	GetAnimator()->CreateAnimation(L"Idle_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.8f, 3);
	GetAnimator()->CreateAnimation(L"Idle_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.5f, 4, true);

	GetAnimator()->CreateAnimation(L"LookUP_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.5f, 4, true);
	GetAnimator()->CreateAnimation(L"LookUP_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.5f, 4);
	GetAnimator()->CreateAnimation(L"LookDown_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.5f, 4, true);
	GetAnimator()->CreateAnimation(L"LookDown_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.5f, 4);

	GetAnimator()->CreateAnimation(L"Move_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 3, true);
	GetAnimator()->CreateAnimation(L"Move_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"Jump_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1, true);
	GetAnimator()->CreateAnimation(L"Jump_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"Fall_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1, true);
	GetAnimator()->CreateAnimation(L"Fall_Rgith", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"Demaged_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1, true);
	GetAnimator()->CreateAnimation(L"Demaged_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);

	GetAnimator()->CreateAnimation(L"Attack_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1, true);
	GetAnimator()->CreateAnimation(L"Attack_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"SoulMissile_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1, true);
	GetAnimator()->CreateAnimation(L"SoulMissile_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"AttackUp_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1, true);
	GetAnimator()->CreateAnimation(L"AttackUP_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"AttackDown_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1, true);
	GetAnimator()->CreateAnimation(L"AttackDown_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"HP_Charge_Left", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1, true);
	GetAnimator()->CreateAnimation(L"HP_Charge_Right", m_pImg, fPoint(0.f, 0.f), fPoint(125.f, 125.f), fPoint(125.f, 0.f), 0.25f, 1);

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

	if (Key(VK_LBUTTON)) // 테스트용 재시작 버튼
	{
		m_fptPos = (fPoint(3130, 2090));
		m_bWallLeft = false;
		m_bWallRight = false;
		m_bWallBottom = false;
	}

	//CCameraManager::getInst()->SetLookAt(GetPos());

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

#pragma region Update State
void CKnight::update_state()
{
	if (m_fvVelocity.x == 0 && m_bCurGround && m_ePrevState == PLAYER_STATE::JUMP)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

	if (!m_bCurGround && m_ePrevState == PLAYER_STATE::MOVE)
	{
		m_eCurState = PLAYER_STATE::FALL;
	}

	if (Key(VK_LEFT))
	{
		m_bLeft = true;
		if (m_eCurState != PLAYER_STATE::JUMP)
		{
			m_eCurState = PLAYER_STATE::MOVE;
		}		
	}
	if (Key(VK_RIGHT))
	{
		m_bLeft = false;
		if (m_eCurState != PLAYER_STATE::JUMP)
		{
			m_eCurState = PLAYER_STATE::MOVE;
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
		m_eCurState = PLAYER_STATE::JUMP;
		//m_fvVelocity.x = -300.f;
	}

	if (KeyDown('X') && m_bCurGround)
	{
		m_eCurState = PLAYER_STATE::ATTACK;
	}

	if (KeyDown('A') && m_bCurGround)
	{
		m_eCurState = PLAYER_STATE::SOULCHARGE;
	}

	if (KeyDown(VK_SPACE))
	{
		m_eCurState = PLAYER_STATE::SOULMISSILE;
		CreateSoulMissile();
	}

	if (KeyDown('B'))
	{
		// TODO : 인벤토리 UI
	}

	if (KeyDown(VK_ESCAPE))
	{
		// TODO : 종료 ButtonUI
	}

	m_ePrevState = m_eCurState;
}
#pragma endregion

#pragma region Update Move
void CKnight::update_move()
{
	fPoint pos = GetPos();

	m_fvVelocity = { 0.f, 0.f };

	// TODO : 맵프레임을 벗어나지 않게 설정해야함.
	CCameraManager::getInst()->SetLookAt(fPoint(this->GetPos().x, this->GetPos().y));

	m_fptCurView = CCameraManager::getInst()->GetLookAt();

	// 몬스터에게 가격을 받았을 때
	if (m_eCurState == PLAYER_STATE::DAMAGED)
	{
		if (m_bLeft)
		{
			m_fvVelocity.x -= 100.f;
			m_sCurDir = -1;
		}
		else
		{
			m_fvVelocity.x += 100.f;
			m_sCurDir = 1;
		}
	}

	if (Key(VK_LEFT))
	{		
		if (!m_bWallRight)
		{
			m_fvVelocity.x += 400.f;
			m_sCurDir = -1;
			m_bLeft = true;
		}	
	}
	if (Key(VK_RIGHT))
	{
		if (!m_bWallLeft)
		{
			m_fvVelocity.x += 400.f;
			m_sCurDir = 1;
			m_bLeft = false;
		}
	}
	if (Key(VK_UP) && !m_bAttack && m_bCurGround)
	{
		// TODO : 카메라 시점을 위로 (시점 이동이 좀더 느리고 부드럽게)
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
		// TODO : 카메라 시점을 아래로 (시점 이동이 좀더 느리고 부드럽게)
		m_fptCurView.y += 10.f;
		CCameraManager::getInst()->SetLookAt(fPoint(this->GetPos().x, this->GetPos().y + m_fptCurView.y));

		if (KeyUp(VK_DOWN) && !m_bAttack)
		{
			m_fptCurView.y -= 10.f;
			CCameraManager::getInst()->SetLookAt(fPoint(m_fptCurView.x, m_fptCurView.y - m_fptCurView.y));
		}
	}
	// JUMP 
	if (KeyDown('Z') && m_bCurGround)
	{
		m_fptPos.y -= 1.f;
		m_fvVelocity.y = -800.f;
		m_fGAccel += m_fvVelocity.y;
		pos.y += m_fGAccel * fDT;
		m_bJump = true;
		Logger::debug(L"Jump");		
	}

	// FALL
	if (m_eCurState == PLAYER_STATE::FALL && m_bWallBottom)
	{	
		m_fGAccel = 400.f;
		Logger::debug(L"Fall");
	}

	pos.x += m_sCurDir* m_fvVelocity.x * fDT;
	pos.y += m_fGAccel * fDT;

	SetPos(pos);

	m_fGAccel += Gravity * fDT;

	if (m_fGAccel >= 2000.f)
	{
		m_fGAccel = 2000.f;
	}
	if (m_MaxVelocity <= m_fvVelocity.x || m_MaxVelocity <= m_fvVelocity.y)
	{
		m_fvVelocity.x = m_MaxVelocity;
		m_fvVelocity.y = m_MaxVelocity;
	}

	m_sPrevDir = m_sCurDir;
}

#pragma endregion

#pragma region Update Ainmation
void CKnight::update_animation()
{
	if (m_ePrevState == m_eCurState && m_sPrevDir == m_sCurDir)
	{
		return;
	}

	switch (m_eCurState)
	{
	case PLAYER_STATE::START:
		GetAnimator()->Play(L"Start_Pose");
		break;
	case PLAYER_STATE::IDLE:
		if (m_fvVelocity.x == 0 && m_eCurState != PLAYER_STATE::JUMP)
		{
			if (m_sCurDir == -1)
			{
				GetAnimator()->Play(L"Idle_Left");
			}
			else
			{
				GetAnimator()->Play(L"Idle_Right");
			}
		}
		break;
	case PLAYER_STATE::MOVE:
		if (m_sCurDir == -1)
		{
			if (m_fvVelocity.x > 0)
			{
				GetAnimator()->Play(L"Move_Left");
			}
			else
			{
				GetAnimator()->Play(L"Idle_Left");
			}
		}
		else
		{
			if (m_fvVelocity.x > 0)
			{
				GetAnimator()->Play(L"Move_Right");
			}
			else
			{
				GetAnimator()->Play(L"Idle_Right");
			}
		}
		break;
	case PLAYER_STATE::JUMP:	
		if (m_sCurDir == -1)
		{
			GetAnimator()->Play(L"Jump_Left");
		}
		else
		{
			GetAnimator()->Play(L"Jump_Right");
		}
		break;
	case PLAYER_STATE::FALL:
		if (m_sCurDir == -1)
		{
			GetAnimator()->Play(L"Fall_Left");
		}
		else
		{
			GetAnimator()->Play(L"Fall_Right");
		}
		break;
	case PLAYER_STATE::ATTACK:
		if (m_sCurDir == -1)
		{
			GetAnimator()->Play(L"Attack_Left");

			if (Key(VK_UP) && !m_bCurGround)
			{
				GetAnimator()->Play(L"AttackUp_Left");
			}

			if (Key(VK_DOWN) && !m_bCurGround)
			{
				GetAnimator()->Play(L"AttackDown_Left");
			}			
		}
		else
		{
			GetAnimator()->Play(L"Attack_Right");

			if (Key(VK_UP) && !m_bCurGround)
			{
				GetAnimator()->Play(L"AttackUp_Right");
			}

			if (Key(VK_DOWN) && !m_bCurGround)
			{
				GetAnimator()->Play(L"AttackDown_Right");
			}
		}
		break;
	case PLAYER_STATE::DAMAGED:
		if (m_sCurDir == -1 && m_bDamaged)
		{
			GetAnimator()->Play(L"Demaged_Left");
		}
		else if (m_sCurDir == 1 && m_bDamaged)
		{
			GetAnimator()->Play(L"Demaged_Right");
		}
		break;
	case PLAYER_STATE::SOULMISSILE:
		if (m_sCurDir == -1)
		{
			GetAnimator()->Play(L"SoulMissile_Left");
		}
		else 
		{
			GetAnimator()->Play(L"SoulMissile_Right");
		}
		break;
	case PLAYER_STATE::LOOKUP:
		if (m_sCurDir == -1)
		{
			GetAnimator()->Play(L"LookUP_Left");
		}
		else
		{
			GetAnimator()->Play(L"LookUP_Right");
		}
		break;
	case PLAYER_STATE::LOOKDOWN:
		if (m_sCurDir == -1)
		{
			GetAnimator()->Play(L"LookDown_Left");
		}
		else
		{
			GetAnimator()->Play(L"LookDown_Right");
		}
		break;
	case PLAYER_STATE::SOULCHARGE:
		if (m_sCurDir == -1)
		{
			GetAnimator()->Play(L"HP_Charge_Left");
		}
		else 
		{
			GetAnimator()->Play(L"HP_Charge_Right");
		}
		break;
	case PLAYER_STATE::DEAD:
		if (m_sCurDir == -1)
		{
			GetAnimator()->Play(L"Dead_Pose_Left");
		}
		else
		{
			GetAnimator()->Play(L"Dead_Pose_Right");
		}
		break;

	default:
		break;
	}	
}

void CKnight::OnCollision(CCollider* _pOther)
{
	Logger::debug(L"OnCollision_Knight");
}

void CKnight::OnCollisionEnter(CCollider* _pOther)
{
	Logger::debug(L"OnCollisionEnter_Knight");
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

	Logger::debug(L"Player_OnCollisionExit");
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

void CKnight::CreateSoulMissile()
{
	fPoint fpMissilePos = GetPos();
	fpMissilePos.x += GetScale().x / 2.f;

	// Misiile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(fpMissilePos);
	pMissile->SetDir(fVec2(1, 0));
	pMissile->SetName(L"Missile_Player");

	CreateObj(pMissile, GROUP_GAMEOBJ::SOUL_MISSILE);
}


