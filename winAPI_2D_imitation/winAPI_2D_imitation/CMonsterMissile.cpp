#include "framework.h"
#include "CMonsterMissile.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CKnight.h"

CMonsterMissile::CMonsterMissile()
{
	m_fAttackTimer = 0;
	m_fAttackTimeLimit = 300;
	//CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"SoulMissileImg", L"texture\\Animation\\Effect\\effect.png");
	m_fSpeed = 700.f;
	SetScale(fPoint(80.f, 80.f));
	m_fvDir = fVec2(0, 0);
	SetName(L"Missile");

	CreateCollider();
	GetCollider()->SetScale(fPoint(50.f, 50.f));

	/*CreateAnimator();
	GetAnimator()->CreateAnimation(L"MonsterMissile_Left", m_pImg, fPoint(0.f, 0.f), fPoint(260.f, 130.f), fPoint(260.f, 0.f), 0.1f, 4, true);
	GetAnimator()->CreateAnimation(L"MonsterMissile_Right", m_pImg, fPoint(0.f, 0.f), fPoint(260.f, 130.f), fPoint(260.f, 0.f), 0.1f, 4);*/
}

CMonsterMissile::~CMonsterMissile()
{
}

CMonsterMissile* CMonsterMissile::Clone()
{
	return new CMonsterMissile(*this);
}

void CMonsterMissile::update()
{
	fPoint pos = GetPos();

	pos.x += m_fSpeed * m_fvDir.x * fDT;
	pos.y += m_fSpeed * m_fvDir.y * fDT;

	SetPos(pos);

	update_animation();
	GetAnimator()->update();
}

void CMonsterMissile::render()
{
	component_render();
}

void CMonsterMissile::SetDir(fVec2 vec)
{
	m_fvDir = vec.Normalize();
}

void CMonsterMissile::SetDir(float theta)
{	
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CMonsterMissile::update_animation()
{
	
}

void CMonsterMissile::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster" || pOtherObj->GetObjType() == GROUP_GAMEOBJ::GROUND)
	{
		DeleteObj(this);
		m_fAttackTimer = 0;
	}
}
