#include "framework.h"
#include "CAttackState.h"
#include "CKnight.h"
#include "CMonster.h"
#include "CMonsterMissile.h"

CAttackState::CAttackState(MON_STATE state) : CState(state)
{
	m_iCurDir = 0;
	attackRange = 0.f;

	bAttack = false;
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


	if (!bAttack)
	{
		CreateMissile(m_fptTargetPos);
	}	
}

void CAttackState::Enter()
{	
	Logger::debug(L"Attack ON");
}

void CAttackState::Exit()
{
	Logger::debug(L"Attack OUT");
}

void CAttackState::CreateMissile(fPoint targetPos)
{
	// TODO : 미사일이 사라지지 않았다면 재발사 불가능 상태 설정

	m_fptTargetPos = targetPos;
	int iMissileOffSetX = 150;
	int iMissileOffSetY = 20;

	// [MonsterMisiile Object]
	CMonsterMissile* pMonsterMissile = new CMonsterMissile;



	if (0 < m_iCurDir)
	{
		pMonsterMissile->SetPos(fPoint(m_fptTargetPos.x + iMissileOffSetX, m_fptTargetPos.y + iMissileOffSetY));

		pMonsterMissile->SetDir(fVec2(m_iCurDir, 0));
	}
	else
	{
		pMonsterMissile->SetPos(fPoint(m_fptTargetPos.x - iMissileOffSetX, m_fptTargetPos.y + iMissileOffSetY));
		pMonsterMissile->SetDir(fVec2(m_iCurDir, 0));
	}

	pMonsterMissile->SetName(L"Missile_Monster");

	CreateObj(pMonsterMissile, GROUP_GAMEOBJ::MONSTER_MISSILE);
}
