#pragma once
#include "CGameObject.h"
class CGround : public CGameObject
{
public:
	CGround();
	virtual	~CGround();

	virtual CGameObject* Clone();

	virtual void start();
	virtual void update();
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

};

