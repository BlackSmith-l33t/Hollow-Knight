#include "framework.h"
#include "CMissile.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CMissile* CMissile::Clone()
{
	return new CMissile(*this);
}

CMissile::CMissile()
{
	m_fAttackTimer = 0;
	m_fAttackTimeLimit = 300;
	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"SoulMissileImg", L"texture\\Animation\\Effect\\effect.png");
	m_fSpeed = 700.f;
	SetScale(fPoint(270.f, 130.f));
	m_fvDir = fVec2(0, 0);
	SetName(L"Missile");

	CreateCollider();
	GetCollider()->SetScale(fPoint(140.f, 50.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"SoulMissile_Left", m_pImg, fPoint(0.f, 0.f), fPoint(260.f, 130.f), fPoint(260.f, 0.f), 0.1f, 4, true);
	GetAnimator()->CreateAnimation(L"SoulMissile_Right", m_pImg, fPoint(0.f, 0.f), fPoint(260.f, 130.f), fPoint(260.f, 0.f), 0.1f, 4);
	
	
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

	update_animation();
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
		m_fAttackTimer = 0;
	}	
}

void CMissile::update_animation()
{
	// TODO : 애니메이션 수정 중 / 반복 현상 발생
	if (0 > m_fvDir.x && m_fAttackTimer <= m_fAttackTimeLimit)
	{
		if (m_fAttackTimer >= m_fAttackTimeLimit)
		{
			CAnimation* pAni;
			pAni = GetAnimator()->FindAnimation(L"SoulMissile_Left");
			pAni->SetFrame(3);
			return;
		}
		GetAnimator()->Play(L"SoulMissile_Left", false);
		m_fAttackTimer++;
	}
 	else if (0 < m_fvDir.x && m_fAttackTimer <= m_fAttackTimeLimit)
	{
		if (m_fAttackTimer >= m_fAttackTimeLimit)
		{
			CAnimation* pAni;
			pAni = GetAnimator()->FindAnimation(L"SoulMissile_Right");
		    pAni->SetFrame(3);
			return;
		}
		GetAnimator()->Play(L"SoulMissile_Right", false);		
		m_fAttackTimer++;	
	}
}
