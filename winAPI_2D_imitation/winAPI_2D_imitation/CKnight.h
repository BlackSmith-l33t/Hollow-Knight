#pragma once
#include "CGameObject.h"

enum class PLAYER_STATE
{
	STEND,
	WAIK,
	JUMP,
	FALL,
	ATTACK,
	DEAD,

	SIZE,
};

class CD2DImage;

class CKnight : public CGameObject
{
private:
	CD2DImage* m_pImg;

	float m_fVelocity;		// 속력
	float m_fAccel;			// 가속도	
	float m_fAccel_G;		// 중력 가속도	

	fVec2 m_fvCurDir;       // 현재 방향
	fVec2 m_fvPrevDir;		// 이전 방향

	bool  m_bGround;	
	bool  m_bLeft;

public:
	CKnight();
	~CKnight();

	virtual CKnight* Clone();
	
	virtual void update();
	virtual void render();

	void update_move();
	void update_ani();

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

