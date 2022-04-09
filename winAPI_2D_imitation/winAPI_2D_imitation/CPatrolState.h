#pragma once
#include "CState.h"
class CPatrolState : public CState
{
private:
	fVec2 m_fPatrolInterval;
	fPoint m_fStartPos;
	fPoint m_fEndPos;
public:
	CPatrolState(STATE_MON state);
	virtual ~CPatrolState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

