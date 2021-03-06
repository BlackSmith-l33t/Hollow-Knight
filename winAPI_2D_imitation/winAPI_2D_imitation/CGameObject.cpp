#include "framework.h"
#include "CGameObject.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CGravity.h"
#include "CGround.h"

CGameObject::CGameObject()
{
	m_fptPos = {};
	m_fptScale = {};
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_pGravity = nullptr;
	m_bAlive = true;
}

CGameObject::CGameObject(const CGameObject& other)
{
	m_strName = other.m_strName;
	m_fptPos = other.m_fptPos;
	m_fptScale = other.m_fptScale;
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_pGravity = nullptr;
	m_bAlive = true;

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
	if (nullptr != other.m_pGravity)
	{
		m_pGravity = new CGravity(*other.m_pGravity);
		m_pGravity->m_pOwner = this;
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
	if (nullptr != m_pGravity)
	{
		delete m_pGravity;
	}
}

void CGameObject::SetDir(int dir)
{
	m_iCurDir = dir;
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

void CGameObject::SetObjType(GROUP_GAMEOBJ type)
{
	m_ObjGroup = type;
}

void CGameObject::SetGround(bool bGround)
{
	m_bCurGround = bGround;
}

void CGameObject::SetVelocity(fVec2 _velocity)
{
	m_fvVelocity = _velocity;
}

int CGameObject::GetDir()
{
	return m_iCurDir;
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

GROUP_GAMEOBJ CGameObject::GetObjType()
{
	return m_ObjGroup;
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
	if (nullptr != m_pGravity)
	{
		m_pGravity->finalupdate();
	}

}

void CGameObject::render()
{
	// ???? ?????? ??????, ?????? ?????? ??????
	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(m_fptPos);

	// ???????? ???????? ???????????? ????
	CRenderManager::getInst()->RenderRectangle(
		fptRenderPos.x - m_fptScale.x / 2,
		fptRenderPos.y - m_fptScale.y / 2,
		fptRenderPos.x + m_fptScale.x / 2,
		fptRenderPos.y + m_fptScale.y / 2);

	component_render();
}

void CGameObject::component_render()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render();
	}
	if (nullptr != m_pCollider)
	{
		m_pCollider->render();
	}
	if (nullptr != m_pGravity)
	{
		m_pGravity->render();
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

CGravity* CGameObject::GetGravity()
{
	return m_pGravity;
}

void CGameObject::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}

void CGameObject::SetGravity(float _fGravity)
{
	m_fGravity = _fGravity;
}


void CGameObject::GetGround(bool _bGround)
{
	m_bCurGround = _bGround;
}
