#pragma once
#include "CGameObject.h"

class CD2DImage;
class CState;

class CKnight : public CGameObject
{
	friend CGround;
private:
	static CKnight* instance;

	short m_pHP;			// HP
	short m_pGeo;			// ���� �� ȭ��

	float m_fSpeed;  		// �ӷ�	
	float m_fAccel;			// ���ӵ�	
	float m_fGAccel;		// �߷� ���ӵ�	
	float m_fFriction;      // ������
	float m_fJump;			// ������

	bool  m_bLeft;			// ����
	bool  m_bAttack;        // ���� ���� 

	fVec2 m_fvCurDir;       // ���� ����
	fVec2 m_fvPrevDir;		// ���� ����
	fVec2 m_fvVelocity;		// �ӵ�

	fPoint m_fptCurView;     // ���� ī�޶� ����

	PLAYER_STATE m_eCurState; 
	PLAYER_STATE m_ePrevState; 

	void CreateMissile();

public:
	CKnight();
	~CKnight();
	virtual CKnight* Clone();

	static CKnight* GetPlayer();	// ���� ���� �ϳ��� �ִ� �÷��̾� ��ü Ȯ��(���Ƿ� �̱��� ����)
	void RegisterPlayer();

	virtual void update();
	virtual void render();

	void update_state();
	void update_move();
	void update_animation();	

	virtual void OnCollisionExit(CCollider* _pOther);
};

