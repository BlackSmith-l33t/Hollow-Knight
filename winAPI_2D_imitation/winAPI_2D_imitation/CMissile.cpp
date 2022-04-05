#include "framework.h"
#include "CMissile.h"
#include "CCollider.h"
#include "CAnimator.h"

CMissile* CMissile::Clone()
{
	return new CMissile(*this);
}

CMissile::CMissile()
{
	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"SoulMissileImg", L"texture\\Animation\\Effect\\effect.png");
	m_fSpeed = 500.f;
	SetScale(fPoint(270.f, 130.f));
	m_fvDir = fVec2(0, 0);
	SetName(L"Missile_Player");

	CreateCollider();
	GetCollider()->SetScale(fPoint(140.f, 50.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"SoulMissile_Left", m_pImg, fPoint(0.f, 0.f), fPoint(260.f, 130.f), fPoint(260.f, 0.f), 0.08f, 5, true);
	GetAnimator()->CreateAnimation(L"SoulMissile_Right", m_pImg, fPoint(0.f, 0.f), fPoint(260.f, 130.f), fPoint(260.f, 0.f), 0.08f, 5);
	
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	fPoint pos = GetPos();

	pos.x += m_fSpeed * m_fvDir.x * fDT;
	pos.y += m_fSpeed * m_fvDir.y * fDT;

	SetPos(pos);

	 
	fPoint fptCurLookPos = CCameraManager::getInst()->GetLookAt();
	
	// TODO : 애니메이션 수정 중 / 반복 현상 발생
	if (0 > m_fvDir.x)
	{
		GetAnimator()->Play(L"SoulMissile_Left", false);
		m_sAttackTimer++;
		if (pos.x < fptCurLookPos.x - WINSIZEX / 2.f)
			DeleteObj(this);
	}
	else
	{
		GetAnimator()->Play(L"SoulMissile_Right", false);
		m_sAttackTimer++;
		if (pos.x > fptCurLookPos.x + WINSIZEX / 2.f)
			DeleteObj(this);
	}
	
	GetAnimator()->update();
	
}

void CMissile::render()
{	
	component_render();
}

void CMissile::SetDir(fVec2 vec)
{
	m_fvDir = vec.Normalize();
}

void CMissile::SetDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CMissile::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster" || pOtherObj->GetObjType() == GROUP_GAMEOBJ::GROUND)
	{
		Logger::debug(L"OnCollisionEnter_Monster");
		DeleteObj(this);
	}	
}
