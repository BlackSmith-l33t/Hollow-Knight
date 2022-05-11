#pragma once
#include "CState.h"
class CAttackState : public CState
{
private:	
	int m_iCurDir;
	float attackRange;
	float attackCoolTime;
	fPoint m_fptTargetPos;

	bool bAttack;
	
public:
	CAttackState(MON_STATE state);
	virtual ~CAttackState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();

	void CreateMissile(fPoint targetPos);	
};

