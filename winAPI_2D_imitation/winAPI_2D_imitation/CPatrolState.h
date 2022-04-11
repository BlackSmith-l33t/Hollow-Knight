#pragma once
#include "CState.h"
class CPatrolState : public CState
{
private:
	int m_iCurDir;

	fPoint m_fPatrolSpeed;
	fPoint m_fPatrolDistance;
	fPoint m_fStartPos;
	fPoint m_fEndPos;

	bool m_bTurnOn;
public:
	CPatrolState(STATE_MON state);
	virtual ~CPatrolState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

