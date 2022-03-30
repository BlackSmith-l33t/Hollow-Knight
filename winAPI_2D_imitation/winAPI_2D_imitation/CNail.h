#pragma once
#include "CEffect.h"
class CNail : public CEffect
{
private:
	float m_fDration;
	float m_fDeleteTime;
public:
	CNail();
	virtual ~CNail();

	virtual void update();
	virtual void render();
};

