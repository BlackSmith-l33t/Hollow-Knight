#include "framework.h"
#include "CPatrolState.h"
#include "CMonster.h"

CPatrolState::CPatrolState(STATE_MON state) : CState(state)
{
	m_fStartPos = GetMonster()->GetPos();
	m_fEndPos = m_fStartPos + fPoint(300.f, 0.f);
}

CPatrolState::~CPatrolState()
{
}

void CPatrolState::update()
{
	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	m_fPatrolInterval = m_fStartPos - m_fEndPos;
	fptMonsterPos += m_fPatrolInterval.Normalize() * 100 * fDT;

	pMonster->SetPos(fptMonsterPos);
}

void CPatrolState::Enter()
{
}

void CPatrolState::Exit()
{
}
