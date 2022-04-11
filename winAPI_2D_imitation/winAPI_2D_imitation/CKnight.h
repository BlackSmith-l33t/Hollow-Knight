#pragma once
#include "CGameObject.h"

class CD2DImage;
class CState;
class CAnimation;
class CNail;

class CKnight : public CGameObject
{
	friend class CGround;
private:
	static CKnight* instance;
	CAnimation* pAni;
	CNail* pNail;

	int m_sHP;			// HP
	int m_sGeo;			// ���� �� ȭ��
	int m_iCurDir;       // ���� ����
	int m_iPrevDir;		// ���� ����
	int m_iMissileActionCount;
	int m_iMissileCount;

	float m_fAttackTimer;
	float m_fAttackTimeLimit;
	float m_fMissileAttackTimeLimit;
	float m_fMissileStartCoolTime;
	float m_fMaxAccel;		// �ִ� �߷� ���ӵ�
	float m_fJump;			// ������
	float m_fMaxVelocity;    // �ִ� �ӵ�	

	bool  m_bLeft;			// ����
	bool  m_bAttack;        // ���� ���� 
	bool  m_bDamaged;       // ���� ���� ����
	bool m_bFall;


	fVec2 m_fvVelocity;		// �ӵ�

	fPoint m_fptCurView;     // ���� ī�޶� ����
	fPoint m_fptPrevView;    // ���� ī�޶� ����

	PLAYER_STATE m_eCurState;
	PLAYER_STATE m_ePrevState;

	void CreateSoulMissile();

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

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	void Attack();

};

