#pragma once
#include "CGameObject.h"

class CD2DImage;

class CKnight : public CGameObject
{
private:
	CD2DImage* m_pImg;
	float m_fVelocity;

public:
	CKnight();
	~CKnight();

	virtual CKnight* Clone();
	
	virtual void update();
	virtual void render();
};

