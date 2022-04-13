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
	CKnight* pKnight = CKnight::GetPlayer();
	if (nullptr == pKnight)
	{
		return;
	}

	fPoint fptPlayerPos = pKnight->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();
	if (fLen >= pMonster->GetMonInfo().fRecogRange)
	{
		ChangeAIState(GetOwnerAI(), MON_STATE::PATROL);
	}

	fPoint pos = pMonster->GetPos();
	pos += fvDiff.Normalize() * 100 * fDT;
	pMonster->SetPos(pos);
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
