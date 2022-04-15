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

	// TODO : Trace 타입 몬스터일 경우 state 변경을 구성해주어야함.

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

		if (fLen < pMonster->GetMonInfo().fRecogRange.x)
		{
			if (fvDiff.x > 0)
			{
				pMonster->SetDir(1);
			}
			else
			{
				pMonster->SetDir(-1);
			}

			ChangeAIState(GetOwnerAI(), MON_STATE::TRACE);
		}		
	}
	m_fPatrolDistance += m_fPatrolSpeed.Normalize() * 50 * fDT;

	if (m_bTurnOn)
	{
		fptMonsterPos.x += m_fPatrolSpeed.Normalize().x * 50 * fDT;
		pMonster->SetDir(1);
	}
	else
	{
		fptMonsterPos.x -= m_fPatrolSpeed.Normalize().x * 50 * fDT;
		pMonster->SetDir(-1);
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
	Logger::debug(L"Patrol ON");
}

void CPatrolState::Exit()
{
	Logger::debug(L"Patrol OUT");
}
