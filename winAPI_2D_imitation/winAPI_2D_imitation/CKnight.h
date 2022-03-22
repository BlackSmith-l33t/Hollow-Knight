#pragma once
#include "CGameObject.h"

class CD2DImage;

class CKnight : public CGameObject
{
private:
	CD2DImage* m_pImg;
	float m_fVelocity; // 속력
	float m_fGravity;  // 중력
	float m_fAccel;    // 가속도
	float m_fAccelA;
	bool  m_bGround;


public:
	CKnight();
	~CKnight();

	virtual CKnight* Clone();
	
	virtual void update();
	virtual void render();

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

