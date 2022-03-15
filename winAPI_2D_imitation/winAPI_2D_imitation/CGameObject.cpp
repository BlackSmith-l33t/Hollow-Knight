#include "framework.h"
#include "CGameObject.h"
#include "CCollider.h"
#include "CAnimator.h"

CGameObject::CGameObject()
{
	m_fptPos = {};
	m_fptScale = {};
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_bAlive = true;
}

CGameObject::CGameObject(const CGameObject& other)
{
	m_strName	= other.m_strName;
	m_fptPos	= other.m_fptPos;
	m_fptScale	= other.m_fptScale;
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_bAlive	= true;

	if (nullptr != other.m_pCollider)
	{
		m_pCollider = new CCollider(*other.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	if (nullptr != other.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*other.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
}

CGameObject::~CGameObject()
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
	}
	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
	}
}

void CGameObject::SetPos(fPoint pos)
{
	m_fptPos = pos;
}

void CGameObject::SetScale(fPoint scale)
{
	m_fptScale = scale;
}

void CGameObject::SetName(wstring name)
{
	m_strName = name;
}

fPoint CGameObject::GetPos()
{
	return m_fptPos;
}

fPoint CGameObject::GetScale()
{
	return m_fptScale;
}

wstring CGameObject::GetName()
{
	return m_strName;
}

bool CGameObject::isDead()
{
	return !m_bAlive;
}

void CGameObject::SetDead()
{
	m_bAlive = false;
}

void CGameObject::finalupdate()
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->finalupdate();
	}
}

void CGameObject::render(HDC hDC)
{
	// 절대 위치를 넘기고, 랜더링 위치를 받아옴
	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(m_fptPos);

	// 카메라를 기준으로 그려져야하는 위치
	Rectangle(hDC,
		(int)(fptRenderPos.x - m_fptScale.x / 2),
		(int)(fptRenderPos.y - m_fptScale.y / 2),
		(int)(fptRenderPos.x + m_fptScale.x / 2),
		(int)(fptRenderPos.y + m_fptScale.y / 2));

	component_render(hDC);
}

void CGameObject::component_render(HDC hDC)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->render(hDC);
	}
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render(hDC);
	}
}

CCollider* CGameObject::GetCollider()
{
	return m_pCollider;
}

void CGameObject::CreateCollider()
{
	m_pCollider = new CCollider();
	m_pCollider->m_pOwner = this;
}

CAnimator* CGameObject::GetAnimator()
{
	return m_pAnimator;
}

void CGameObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}
