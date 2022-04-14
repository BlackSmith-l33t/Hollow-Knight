#pragma once

class CCollider;
class CAnimator;
class CGravity;
class CGround;

class CGameObject
{
	friend class CEventManager;
	friend class CGround;

protected:
	int		m_iCurDir;
	wstring m_strName;
	fPoint  m_fptPos;
	fPoint  m_fptScale;
	fVec2   m_fvVelocity;

	GROUP_GAMEOBJ m_ObjGroup;

	// Component
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;
	CGravity* m_pGravity;

	bool	   m_bCurGround;
	bool	   m_bPrevGround;
	bool       m_bWallLeft;
	bool       m_bWallRight;
	bool       m_bWallBottom;
	bool	   m_bAlive;
	bool	   m_bJump;

	void SetDead();

	float m_fGravity;
	float m_fGAccel;

public:
	CGameObject();
	CGameObject(const CGameObject& other);
	virtual ~CGameObject();
	virtual CGameObject* Clone() = 0;

	void SetDir(int dir);
	void SetPos(fPoint pos);
	void SetScale(fPoint scale);
	void SetName(wstring name);
	void SetObjType(GROUP_GAMEOBJ type);
	void SetGround(bool bGround);
	void SetVelocity(fVec2 _velocity);

	int GetDir();
	fPoint GetPos();
	fPoint GetScale();
	wstring GetName();
	GROUP_GAMEOBJ GetObjType();

	bool isDead();

	virtual void start() {};
	virtual void update() = 0;			// 반드시 상속받은 객체가 update를 구현하도록 순수가상함수로 선언
	virtual void finalupdate();
	virtual void render();
	virtual void component_render();	// 컴포넌트들의 영역을 표시하기 위해

	CCollider* GetCollider();				// 충돌체 반환
	void CreateCollider();					// 충돌체 생성

	virtual void OnCollision(CCollider* _pOther) {}			// 재정의용 충돌중 가상함수
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// 재정의용 충돌시 가상함수
	virtual void OnCollisionExit(CCollider* _pOther) {}		// 재정의용 탈충돌 가상함수

	CAnimator* GetAnimator();				// 애니메이터 반환
	void CreateAnimator();					// 애니메이터 생성

	CGravity* GetGravity();					// 중력 반환
	void CreateGravity();					// 중력 생성	
	void SetGravity(float _fGravity);		// 중력 설정

	void GetGround(bool _bGround);
};

