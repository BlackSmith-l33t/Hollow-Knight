#pragma once
#include "CGameObject.h"

class CD2DImage;
class AI;

struct tMonInfo
{
	float fSpeed;
	float fHP;	
	float fAttRange;
	float fAtt;
	fPoint fRecogRange;
};

enum class MON_TYPE
{
	NONE,
	NORMAL,
	TRACE,	
	FLY,
	BOSS,

	SIZE,
};

class CMonster : public CGameObject
{
private:	
	tMonInfo m_tInfo;
	AI* m_pAI;	
	MON_TYPE m_eMonsterType;
	MON_STATE m_eCurState;

	bool m_bRangeAttack;

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* Clone();

	static CMonster* Create(MON_TYPE type, fPoint pos);

	virtual void render();
	virtual void update();
	void update_animation();

	float GetSpeed();
	const tMonInfo& GetMonInfo();
	MON_TYPE GetMonType();

	void SetSpeed(float speed);
	void SetAI(AI* ai);
	void SetMonInfo(const tMonInfo& info);	
	
	void OnCollisionEnter(CCollider* pOther);

	
};

