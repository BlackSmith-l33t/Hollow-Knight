#include "framework.h"
#include "CPatrolState.h"
#include "CMonster.h"

CPatrolState::CPatrolState(STATE_MON state) : CState(state)
{	
	m_sCurDir = 1;
	m_fPatrolSpeed.x  = 400.f;
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

	m_fPatrolDistance += m_fPatrolSpeed.Normalize() * 100 * fDT;
	
	if (m_bTurnOn)
	{
		fptMonsterPos += m_fPatrolSpeed.Normalize() * 100 * fDT;
	}
	else
	{		
		fptMonsterPos -= m_fPatrolSpeed.Normalize() * 100 * fDT;
	}


	if (m_fPatrolDistance.x >= 300.f)
	{
		m_bTurnOn = !m_bTurnOn;
		m_sCurDir =  m_sCurDir * -1;
		m_fPatrolDistance.x = 0.f;
	}	


	pMonster->SetPos(fptMonsterPos);
	if (m_fPatrolDistance.x >= 300.f)
	{
		m_fPatrolDistance.x = 0.f;
	}
}

void CPatrolState::Enter()
{
}

void CPatrolState::Exit()
{
}
