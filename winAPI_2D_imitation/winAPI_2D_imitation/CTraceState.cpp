#include "framework.h"
#include "CTraceState.h"
#include "CKnight.h"
#include "CMonster.h"

CTraceState::CTraceState(MON_STATE state)
	: CState(state)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	CKnight* pKnight = CKnight::GetPlayer();
	if (nullptr == pKnight)
	{
		return;
	}

	fPoint fptPlayerPos = pKnight->GetPos();
	fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();

	fPoint pos = pMonster->GetPos();
	pos += fvDiff.Normalize() * 100 * fDT;
	pMonster->SetPos(pos);

	if (0 < fvDiff.x && pMonster->GetMonInfo().fRecogRange.y > fvDiff.y)
	{
		if (fLen >= pMonster->GetMonInfo().fRecogRange.x)
		{
			pMonster->SetDir(1);
			ChangeAIState(GetOwnerAI(), MON_STATE::PATROL);
		}
	}
	else if (0 > fvDiff.x && pMonster->GetMonInfo().fRecogRange.y > fvDiff.y)
	{
		if (fLen >= pMonster->GetMonInfo().fRecogRange.x)
		{
			pMonster->SetDir(-1);
			ChangeAIState(GetOwnerAI(), MON_STATE::PATROL);
		}
	}

	
}

void CTraceState::Enter()
{
	Logger::debug(L"Trace ON!");
}

void CTraceState::Exit()
{
	Logger::debug(L"Trace OUT!");
}
