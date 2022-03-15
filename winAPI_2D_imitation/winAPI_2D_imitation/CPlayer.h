#pragma once

#include "CGameObject.h"

class CTexture;

class CPlayer : public CGameObject
{
private:
	CTexture* m_pTex;
	float m_fVelocity = 300;

	void CreateMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render(HDC hDC);

	
};

