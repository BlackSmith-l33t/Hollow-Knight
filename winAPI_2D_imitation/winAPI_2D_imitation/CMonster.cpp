#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CPatrolState.h"
#include "CAttackState.h"
#include "CMonsterMissile.h"
// TODO : �÷��̾� �⺻���ݿ� �ǰݽ� ���� ȿ�� ����

CMonster::CMonster()
{	
	m_iCurDir = -1;
	m_fptTargetPos = {};
	m_eMonsterType = MON_TYPE::NONE;
	m_pAI = nullptr;
	m_tInfo = {};
	m_eCurState = MON_STATE::NONE;
	m_bRangeAttack = false;
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}

CMonster* CMonster::Clone()
{
	CMonster* newMonster = new CMonster;
	if (nullptr != m_pAI)
	{
		newMonster->m_pAI = new AI;
	}
	return new CMonster(*newMonster);
}

CMonster* CMonster::Create(MON_TYPE type, fPoint pos)
{
	CMonster* pMon = nullptr;

	switch (type)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->m_eMonsterType = type;
		pMon->SetPos(pos);

		pMon->SetName(L"Monster_Normal");
		pMon->SetScale(fPoint(100, 100));

		pMon->CreateCollider();
		pMon->GetCollider()->SetScale(fPoint(50.f, 50.f));
		pMon->GetCollider()->SetOffsetPos(fPoint(0.f, 20.f));

		CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"MonsterTex", L"texture\\Animation\\Monsters\\monsters.png");
		
		pMon->CreateAnimator();
		pMon->GetAnimator()->CreateAnimation(L"NormalMonster_MoveLeft", m_pImg, fPoint(0, 0), fPoint(130, 130), fPoint(130, 0), 0.2f, 5, true);
		pMon->GetAnimator()->CreateAnimation(L"NormalMonster_MoveRight", m_pImg, fPoint(0, 0), fPoint(130, 130), fPoint(130, 0), 0.2f, 5);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange.x = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;		

		AI* pAI = new AI;
		pAI->AddState(new CPatrolState(MON_STATE::PATROL));
		pAI->SetCurState(MON_STATE::PATROL);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
		pMon->m_eCurState = MON_STATE::PATROL;
	}
	break;
	case MON_TYPE::TRACE:
	{
		// patrol -> trace -> patrol 
		pMon = new CMonster;
		pMon->m_eMonsterType = type;
		pMon->SetPos(pos);

		pMon->SetName(L"Monster_Trace");
		pMon->SetScale(fPoint(130, 130));

		pMon->CreateCollider();
		pMon->GetCollider()->SetScale(fPoint(100.f, 150.f));		

		CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"MonsterTex", L"texture\\Animation\\Monsters\\monsters.png");

		pMon->CreateAnimator();
		
		pMon->GetAnimator()->CreateAnimation(L"TraceMonster_MoveLeft", m_pImg, fPoint(0, 130), fPoint(130, 130), fPoint(130, 0), 0.2f, 6, true);
		pMon->GetAnimator()->CreateAnimation(L"TraceMonster_MoveRight", m_pImg, fPoint(0, 130), fPoint(130, 130), fPoint(130, 0), 0.2f, 6);

		pMon->GetAnimator()->CreateAnimation(L"TraceMonster_TraceLeft", m_pImg, fPoint(0, 130), fPoint(130, 130), fPoint(130, 0), 0.2f, 3, true);
		pMon->GetAnimator()->CreateAnimation(L"TraceMonster_TraceRight", m_pImg, fPoint(0, 130), fPoint(130, 130), fPoint(130, 0), 0.2f, 3);

		pMon->GetAnimator()->CreateAnimation(L"TraceMonster_DeadLeft", m_pImg, fPoint(0, 260), fPoint(130, 130), fPoint(130, 0), 0.2f, 8, true);
		pMon->GetAnimator()->CreateAnimation(L"TraceMonster_DeadRight", m_pImg, fPoint(0, 260), fPoint(130, 130), fPoint(130, 0), 0.2f, 8);


		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange.x = 300.f;
		info.fRecogRange.y = 100.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CPatrolState(MON_STATE::PATROL));
		pAI->AddState(new CTraceState(MON_STATE::TRACE));	

		pAI->SetCurState(MON_STATE::PATROL);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
		pMon->m_eCurState = MON_STATE::PATROL;
	}
	break;
	case MON_TYPE::FLY:
	{
		pMon = new CMonster;
		pMon->m_eMonsterType = type;
		pMon->SetPos(pos);

		pMon->SetName(L"Monster_FlyAttacker");
		pMon->SetScale(fPoint(100, 100));

		pMon->CreateCollider();
		pMon->GetCollider()->SetScale(fPoint(50.f, 50.f));
		pMon->GetCollider()->SetOffsetPos(fPoint(0.f, 20.f));

		CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"MonsterTex", L"texture\\Animation\\Monsters\\monsters.png");

		pMon->CreateAnimator();
		pMon->GetAnimator()->CreateAnimation(L"NormalMonster_IdleLeft", m_pImg, fPoint(0, 0), fPoint(130, 130), fPoint(130, 0), 0.2f, 1, true);
		pMon->GetAnimator()->CreateAnimation(L"NormalMonster_IdleRight", m_pImg, fPoint(0, 0), fPoint(130, 130), fPoint(130, 0), 0.2f, 1);

		pMon->GetAnimator()->CreateAnimation(L"NormalMonster_MoveLeft", m_pImg, fPoint(0, 0), fPoint(130, 130), fPoint(130, 0), 0.2f, 5, true);
		pMon->GetAnimator()->CreateAnimation(L"NormalMonster_MoveRight", m_pImg, fPoint(0, 0), fPoint(130, 130), fPoint(130, 0), 0.2f, 5);

		pMon->GetAnimator()->CreateAnimation(L"NormalMonster_AttackLeft", m_pImg, fPoint(0, 0), fPoint(130, 130), fPoint(130, 0), 0.2f, 5, true);
		pMon->GetAnimator()->CreateAnimation(L"NormalMonster_AttackRight", m_pImg, fPoint(0, 0), fPoint(130, 130), fPoint(130, 0), 0.2f, 5);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange.x = 500.f;
		info.fRecogRange.y = 50.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CPatrolState(MON_STATE::PATROL));		
		pAI->AddState(new CAttackState(MON_STATE::ATT));
		pAI->SetCurState(MON_STATE::PATROL);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);

		pMon->m_eCurState = MON_STATE::PATROL;
	}
	break;
	case MON_TYPE::BOSS:
	{
		pMon = new CMonster;
		pMon->SetPos(pos);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange.x = 300.f;
		info.fRecogRange.y = 50.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(MON_STATE::IDLE));
		pAI->AddState(new CTraceState(MON_STATE::TRACE));
		pAI->SetCurState(MON_STATE::IDLE);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);		
	}
	default:
		break;
	}
	assert(pMon);
	return pMon;
}

void CMonster::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::getInst()->GetRenderPos(pos);

	component_render();
}

void CMonster::update()
{
	update_animation();

	if (nullptr != GetAnimator())
		GetAnimator()->update();
	if (nullptr != m_pAI)
		m_pAI->update();
}

void CMonster::update_animation()
{
	switch (m_eCurState)
	{
	case MON_STATE::IDLE:
		if (m_eMonsterType == MON_TYPE::TRACE)
		{
			if (m_iCurDir == -1)
			{
				GetAnimator()->Play(L"NormlMonster_IdleLeft", true);
			}
			else
			{
				GetAnimator()->Play(L"NormalMonster_IdleRight", true);
			}	
		}
		break;
	case MON_STATE::PATROL:
		if (m_eMonsterType == MON_TYPE::NORMAL)
		{
			if (m_iCurDir == -1)
			{
				GetAnimator()->Play(L"NormalMonster_MoveLeft", true);
			}
			else
			{
				GetAnimator()->Play(L"NormalMonster_MoveRight", true);
			}
		}
		else if (m_eMonsterType == MON_TYPE::TRACE)
		{
			if (m_iCurDir == -1)
			{
				GetAnimator()->Play(L"TraceMonster_MoveLeft", true);
			}
			else
			{
				GetAnimator()->Play(L"TraceMonster_MoveRight", true);
			}
		}
		else if (m_eMonsterType == MON_TYPE::FLY)
		{
			if (m_iCurDir == -1)
			{
				GetAnimator()->Play(L"NormalMonster_MoveLeft", true);
			}
			else
			{
				GetAnimator()->Play(L"NormalMonster_MoveRight", true);
			}
		}
		break;
	case MON_STATE::TRACE:	
		if (m_eMonsterType == MON_TYPE::TRACE)
		{
			if (m_iCurDir == -1)
			{
				GetAnimator()->Play(L"TraceMonster_TraceLeft", true);
			}
			else
			{
				GetAnimator()->Play(L"TraceMonster_TraceRight", true);
			}
		}
		break;
	case MON_STATE::ATT:
		if (m_eMonsterType == MON_TYPE::TRACE)
		{
			if (m_iCurDir == -1)
			{
				GetAnimator()->Play(L"NormalMonster_MoveLeft", true);
			}
			else
			{
				GetAnimator()->Play(L"NormalMonster_MoveRight", true);
			}
		}	
		else if (m_eMonsterType == MON_TYPE::FLY)
		{
			if (m_iCurDir == -1)
			{
				GetAnimator()->Play(L"NormalMonster_MoveLeft", true);
			}
			else
			{
				GetAnimator()->Play(L"NormalMonster_MoveRight", true);
			}
		}
		break;
	default:
		break;
	}	
}

float CMonster::GetSpeed()
{
	return m_tInfo.fSpeed;
}

const tMonInfo& CMonster::GetMonInfo()
{
	return m_tInfo;
}

MON_TYPE CMonster::GetMonType()
{
	return m_eMonsterType;
}

void CMonster::SetSpeed(float speed)
{
	m_tInfo.fSpeed = speed;
}

void CMonster::SetAI(AI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CMonster::SetMonInfo(const tMonInfo& info)
{
	m_tInfo = info;
}

void CMonster::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	//Logger::debug(L"Missile OnCollisionEnter");
	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_tInfo.fHP -= 1;
		if (m_tInfo.fHP <= 0)
			DeleteObj(this);
	}
}

