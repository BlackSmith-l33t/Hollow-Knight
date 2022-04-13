#include "framework.h"
#include "CPatrolState.h"
#include "CMonster.h"
#include "CKnight.h"

CPatrolState::CPatrolState(MON_STATE state) : CState(state)
{	
	m_iCurDir = -1;
	m_fPatrolSpeed.x  = 200.f;
	m_fPatrolDistance = {};
	m_bTurnOn = false;
}

CPatrolState::~CPatrolState()
{
}

void CPatrolState::update()
{
	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	m_fPatrolDistance += m_fPatrolSpeed.Normalize() * 50 * fDT;
	
	if (m_bTurnOn)
	{
		fptMonsterPos += m_fPatrolSpeed.Normalize() * 50 * fDT;
	}
	else
	{		
		fptMonsterPos -= m_fPatrolSpeed.Normalize() * 50 * fDT;
	}


	if (m_fPatrolDistance.x >= 300.f)
	{
		m_iCurDir = m_iCurDir * -1;
		pMonster->SetDir(m_iCurDir);
		m_bTurnOn = !m_bTurnOn;		
		m_fPatrolDistance.x = 0.f;
	}	
	pMonster->SetPos(fptMonsterPos);

	// TODO : Trace 타입 몬스터일 경우 state 변경을 구성해주어야함.
	// partol -> idle -> trace -> idle -> patrol 순환 구조

	if (pMonster->GetMonType() != MON_TYPE::NORMAL)
	{
		CKnight* pKnight = CKnight::GetPlayer();
		if (nullptr == pKnight)
		{
			return;
		}

		fPoint fptPlayerPos = pKnight->GetPos();

		fptMonsterPos = pMonster->GetPos();

		fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
		float fLen = fvDiff.Length();
		if (fLen >= pMonster->GetMonInfo().fRecogRange)
		{
			ChangeAIState(GetOwnerAI(), MON_STATE::TRACE);
		}
	}
}

void CPatrolState::Enter()
{
}

void CPatrolState::Exit()
{
}
