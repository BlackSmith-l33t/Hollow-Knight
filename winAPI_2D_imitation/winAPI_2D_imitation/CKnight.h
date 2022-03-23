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
	static CKnight* instance;

	float m_fSpeed = 300;
	float m_fVelocity;		// �ӷ�
	float m_fAccel;			// ���ӵ�	
	float m_fAccel_G;		// �߷� ���ӵ�	
	

	fVec2 m_fvCurDir;       // ���� ����
	fVec2 m_fvPrevDir;		// ���� ����

	bool  m_bGround;	
	bool  m_bLeft;

	void CreateMissile();

public:
	CKnight();
	~CKnight();

	virtual CKnight* Clone();
	
	virtual void update();
	virtual void render();

	void update_move();
	void update_ani();

	void RegisterPlayer();
	static CKnight* GetPlayer();	// ���� ���� �ϳ��� �ִ� �÷��̾� ��ü Ȯ��(���Ƿ� �̱��� ����)

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

