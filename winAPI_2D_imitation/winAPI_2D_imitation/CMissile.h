#pragma once
#include "CGameObject.h"

class CMissile : public CGameObject
{
private:
	short m_sAttackTimer;
	short m_sAttackTimeLimit;
	short m_sMissileAttackTimeLimit;
	short m_sMissileStartCoolTime;
	short m_sMissileActionCount;
	short m_sMissileCount;

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

