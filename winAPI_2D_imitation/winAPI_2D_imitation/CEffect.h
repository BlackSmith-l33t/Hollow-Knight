#pragma once
#include "CGameObject.h"
class CEffect : public CGameObject
{
public:
	CEffect();
	virtual ~CEffect();

	virtual CEffect* Clone();

	virtual void update();
	virtual void render();

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

