#include "framework.h"
#include "CNail.h"
#include "CCollider.h"

CNail::CNail()
{
	//SetScale(fPoint(65.f, 25.f));
	m_fDration = 0.f;
	m_fDeleteTime = 0.1f;
	CreateCollider();
	GetCollider()->SetScale(fPoint(80.f, 25.f));
}

CNail::~CNail()
{
}

void CNail::update()
{
	fPoint pos = GetPos();
	SetPos(pos);
	
	m_fDration += fDT;

	if (m_fDeleteTime <= m_fDration)
	{
		DeleteObj(this);
	}	
	// 1초 동안 횡격 애니메이션 업데이트
}

void CNail::render()
{
/*	fPoint pos = GetPos();
	fPoint scale = GetScale();
	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);
	CRenderManager::getInst()->RenderRectangle(
		fptRenderPos.x,
		fptRenderPos.y,
		scale.x / 2.f,
		scale.y / 2.f)*/;

	component_render();
}
