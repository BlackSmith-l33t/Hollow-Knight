#pragma once
#include "CState.h"
class CAttackState : public CState
{
private:

public:
	CAttackState(MON_STATE state);
	virtual ~CAttackState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();

	void Attack();
};

