#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"

CMonster* CMonster::Clone()
{
	return new CMonster(*this);
}

CMonster::CMonster()
{
	m_fptCenterPos = fPoint(0, 0);
	m_fVelocity = 0;
	m_fDistance = 300;
	m_bIsUPDir = true;

	SetName(L"Monster");
	SetScale(fPoint(520.f, 380.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(500.f, 300.f));

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"MonsterTex", L"texture\\Animation\\Monsters\\Mons.png");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PlayerStand", m_pImg, fPoint(0, 0), fPoint(520.f, 380.f), fPoint(0, 0), 0.1f, 1, false);
	GetAnimator()->Play(L"PlayerStand");
}

CMonster::~CMonster()
{
}

void CMonster::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::getInst()->GetRenderPos(pos);

	component_render();

	CRenderManager::getInst()->RenderImage(
		m_pImg,
		pos.x,
		pos.y,
		pos.x + scale.x,
		pos.y + scale.y);
}

void CMonster::update()
{
	fPoint pos = GetPos();

	if (m_bIsUPDir)
	{
		pos.y -= fDT * m_fVelocity;
		if (pos.y < m_fptCenterPos.y - m_fDistance)
			m_bIsUPDir = false;
	}
	else
	{
		pos.y += fDT * m_fVelocity;
		if (pos.y > m_fptCenterPos.y + m_fDistance)
			m_bIsUPDir = true;
	}

	SetPos(pos);

	GetAnimator()->update();
}

void CMonster::SetCenterPos(fPoint point)
{
	m_fptCenterPos = point;
}

void CMonster::OnCollisionEnter(CCollider* pOther)
{

}