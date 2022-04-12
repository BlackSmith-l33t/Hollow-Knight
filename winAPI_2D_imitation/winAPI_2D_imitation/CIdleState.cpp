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
	if (fLen < pMonster->GetMonInfo().fRecogRange)
	{
		ChangeAIState(GetOwnerAI(), MON_STATE::TRACE);
	}

}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}
