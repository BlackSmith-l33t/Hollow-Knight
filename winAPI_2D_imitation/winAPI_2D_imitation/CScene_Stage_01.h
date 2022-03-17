#pragma once
#include "CScene.h"
class CScene_Stage_01 : public CScene
{
public:
	CScene_Stage_01();
	virtual ~CScene_Stage_01();
	
	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

