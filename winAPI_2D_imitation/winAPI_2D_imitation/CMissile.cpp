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
	//CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"SoulMissileImg", L"texture\\Animation\\Effect\\effect.png");
	SetScale(fPoint(25.f, 25.f));
	m_fvDir = fVec2(0, 0);
	SetName(L"Missile_Player");

	CreateCollider();
	GetCollider()->SetScale(fPoint(15.f, 15.f));

	/*GetAnimator()->CreateAnimation(L"SoulMissile", m_pImg, fPoint(0.f, 780.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.1f, 9, true);
	GetAnimator()->CreateAnimation(L"SoulMissile", m_pImg, fPoint(0.f, 780.f), fPoint(130.f, 130.f), fPoint(130.f, 0.f), 0.1f, 9);*/
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

	// TODO : 재설정이 필요함 - 현재 pos 값은 항상 window size를 초과함. 
	fPoint fptRenderPos = CCameraManager::getInst()->
	
	if (pos.x < fptRenderPos.x || pos.x > fptRenderPos.x
		|| pos.y < 0 || pos.y > fptRenderPos.y)
		DeleteObj(this);
}

void CMissile::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);

	CRenderManager::getInst()->RenderEllipse(
		fptRenderPos.x,
		fptRenderPos.y,
		scale.x / 2.f,
		scale.y / 2.f);

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
	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObj(this);
	}
}
