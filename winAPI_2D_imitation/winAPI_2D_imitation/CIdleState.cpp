#include "framework.h"
#include "CIdleState.h"
#include "CKnight.h"
#include "CMonster.h"

CIdleState::CIdleState(MON_STATE state)
	: CState(state)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
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

	if (0 < fvDiff.x && pMonster->GetMonInfo().fRecogRange.y > fvDiff.y)
	{
		if (fLen <= pMonster->GetMonInfo().fRecogRange.x)
		{
			pMonster->SetDir(1);
			ChangeAIState(GetOwnerAI(), MON_STATE::TRACE);
		}
	}
	else if (0 > fvDiff.x && pMonster->GetMonInfo().fRecogRange.y > fvDiff.y)
	{
		if (fLen >= pMonster->GetMonInfo().fRecogRange.x)
		{
			pMonster->SetDir(-1);
			ChangeAIState(GetOwnerAI(), MON_STATE::TRACE);
		}
	}

}

void CIdleState::Enter()
{
	Logger::debug(L"Idle ON!");
}

void CIdleState::Exit()
{
	Logger::debug(L"Idle ON!");
}
