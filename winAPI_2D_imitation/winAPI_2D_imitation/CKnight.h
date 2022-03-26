#pragma once
#include "CGameObject.h"

class CD2DImage;
class CState;

class CKnight : public CGameObject
{
	friend class CGround;
private:
	static CKnight* instance;

	short m_pHP;			// HP
	short m_pGeo;			// ���� �� ȭ��
	short m_sCurDir;       // ���� ����
	short m_sPrevDir;		// ���� ����

	//float m_fGAccel;		// �߷� ���ӵ�
	float m_fMaxGAccel;		// �ִ� �߷� ���ӵ�
	float m_fJump;			// ������
	float m_MaxVelocity;    // �ִ� �ӵ� 
	
	bool  m_bLeft;			// ����
	bool  m_bAttack;        // ���� ���� 
	bool  m_bDamaged;       // ���� ���� ����
	

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

};

