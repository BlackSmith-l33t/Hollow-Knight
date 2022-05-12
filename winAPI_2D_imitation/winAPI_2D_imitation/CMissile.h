#pragma once
#include "CGameObject.h"

class CMissile : public CGameObject
{
private:
	int m_iMissileActionCount;
	int m_iMissileCount;

	float m_fAttackTimer;
	float m_fAttackTimeLimit;
	float m_fMissileAttackTimeLimit;
	float m_fMissileStartCoolTime;
	float m_fSpeed;

	fVec2 m_fvDir;

public:
	CMissile();
	~CMissile();
	virtual CMissile* Clone();

	virtual void update();
	void update_animation();

	virtual void render();

	void SetDir(fVec2 vec);
	void SetDir(float theta);

	void OnCollisionEnter(CCollider* pOther);
};

