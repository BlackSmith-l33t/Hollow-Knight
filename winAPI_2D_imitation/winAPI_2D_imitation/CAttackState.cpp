#include "framework.h"
#include "CAttackState.h"
#include "CKnight.h"
#include "CMonster.h"
#include "CMissile.h"

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

	// TODO : �̻��� �߻�

	CreateMissile(fptMonsterPos);
	
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
	// TODO : �̻����� ������� �ʾҴٸ� ��߻� �Ұ��� ���� ����
	Logger::debug(L"Monster Missile Create");
	m_fptTargetPos = targetPos;
	int iMissileOffSetX = 20;
	int iMissileOffSetY = 50;

	// [MonsterMisiile Object]	
	CMissile* pMissile = new CMissile;

	if (0 < m_iCurDir)
	{
		pMissile->SetPos(fPoint(m_fptTargetPos.x + iMissileOffSetX, m_fptTargetPos.y + iMissileOffSetY));
		pMissile->SetDir(fVec2(m_iCurDir, 1));
	}
	else
	{
		pMissile->SetPos(fPoint(m_fptTargetPos.x - iMissileOffSetX, m_fptTargetPos.y + iMissileOffSetY));
		pMissile->SetDir(fVec2(m_iCurDir, 1));
	}

	pMissile->SetName(L"Missile_Monster");

	CreateObj(pMissile, GROUP_GAMEOBJ::MONSTER_MISSILE);
}

