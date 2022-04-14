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

	// TODO : Trace Ÿ�� ������ ��� state ������ �������־����.
	// partol -> idle -> trace -> idle -> patrol ��ȯ ����

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

		if (0 < fvDiff.x &&  pMonster->GetMonInfo().fRecogRange.y > fvDiff.y)
		{			
			if (fLen <= pMonster->GetMonInfo().fRecogRange.x)
			{
				pMonster->SetDir(1);
				ChangeAIState(GetOwnerAI(), MON_STATE::IDLE);
			}
		}
		else if (0 > fvDiff.x && pMonster->GetMonInfo().fRecogRange.y > fvDiff.y)
		{
			if (fLen >= pMonster->GetMonInfo().fRecogRange.x)
			{
				pMonster->SetDir(-1);
				ChangeAIState(GetOwnerAI(), MON_STATE::IDLE);
			}
		}		
	}
}

void CPatrolState::Enter()
{
	Logger::debug(L"Patrol ON!");
}

void CPatrolState::Exit()
{
	Logger::debug(L"Patrol OUT!");
}
