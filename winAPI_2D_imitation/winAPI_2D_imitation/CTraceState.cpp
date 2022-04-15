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
	if (fLen >= pMonster->GetMonInfo().fRecogRange.x)
	{		
		ChangeAIState(GetOwnerAI(), MON_STATE::PATROL);
	}

	fPoint pos = pMonster->GetPos();
	pos.x += fvDiff.Normalize().x * 100 * fDT;
	pMonster->SetPos(pos);

	if (fvDiff.x > 0)
	{
		pMonster->SetDir(1);
	}
	else
	{
		pMonster->SetDir(-1);
	}
}

void CTraceState::Enter()
{
	Logger::debug(L"Trace ON");
}

void CTraceState::Exit()
{
	Logger::debug(L"Trace OUT");
}
