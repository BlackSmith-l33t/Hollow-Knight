#pragma once
#include "CGameObject.h"

class CGravity : public CGameObject
{
	friend class CGameObject;
private:
	CGameObject* m_pOwner;
	bool m_bGround;	

public:
	CGravity();
	virtual ~CGravity();

	virtual CGameObject* Clone();
	virtual void finalupdate();
	virtual void update();

	void SetGround(bool _bGround);		// Ground ¼³Á¤
	

};

