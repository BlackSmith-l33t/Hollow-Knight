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

	int m_iHP;			// HP
	int m_iGeo;			// 게임 내 화폐	
	int m_iPrevDir;		// 이전 방향
	int m_iMissileActionCount;
	int m_iMissileCount;

	float m_fAttackTimer;
	float m_fAttackTimeLimit;
	float m_fMissileAttackTimeLimit;
	float m_fMissileStartCoolTime;
	float m_fMaxAccel;		// 최대 중력 가속도
	float m_fJump;			// 점프력
	float m_fMaxVelocity;    // 최대 속도	

	bool  m_bLeft;			// 방향
	bool  m_bAttack;        // 공격 여부 
	bool  m_bDamaged;       // 공격 받은 여부
	bool m_bFall;


	fVec2 m_fvVelocity;		// 속도

	fPoint m_fptCurView;     // 현재 카메라 시점
	fPoint m_fptPrevView;    // 이전 카메라 시점

	PLAYER_STATE m_eCurState;
	PLAYER_STATE m_ePrevState;

	void CreateSoulMissile();

public:
	CKnight();
	~CKnight();
	virtual CKnight* Clone();

	static CKnight* GetPlayer();	// 게임 내에 하나만 있는 플레이어 객체 확인(임의로 싱글톤 선언)
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

