#include "framework.h"
#include "CPatrolState.h"
#include "CMonster.h"

CPatrolState::CPatrolState(STATE_MON state) : CState(state)
{	
	m_iCurDir = 1;
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

}

void CPatrolState::Enter()
{
}

void CPatrolState::Exit()
{
}
