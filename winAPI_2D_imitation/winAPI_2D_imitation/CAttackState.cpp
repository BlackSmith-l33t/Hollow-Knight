#include "framework.h"
#include "CAttackState.h"
#include "CKnight.h"
#include "CMonster.h"
#include "CMonsterMissile.h"

CAttackState::CAttackState(MON_STATE state) : CState(state)
{

}

CAttackState::~CAttackState()
{
}

void CAttackState::update()
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

	//fPoint pos = pMonster->GetPos();
	//pos.x += fvDiff.Normalize().x * 100 * fDT;
	//pMonster->SetPos(pos);
	pMonster->SetAttack() = true;


	if (fvDiff.x > 0)
	{
		pMonster->SetDir(1);
		m_iCurDir = 1;
	}
	else
	{
		pMonster->SetDir(-1);
		m_iCurDir = -1;
	}

	RangeAttack(pKnight->GetPos());
}

void CAttackState::Enter()
{	
	Logger::debug(L"Attack ON");
}

void CAttackState::Exit()
{
	Logger::debug(L"Attack OUT");
}