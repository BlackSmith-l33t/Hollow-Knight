#include "framework.h"
#include "CGravity.h"

CGravity::CGravity()
{
}

CGravity::~CGravity()
{
}

CGameObject* CGravity::Clone()
{
	return nullptr;
}

void CGravity::finalupdate()
{
	m_pOwner->SetGravity(Gravity);
}

void CGravity::update()
{
}

void CGravity::SetGround(bool _bGround)
{
	m_bGround = _bGround;
	if (m_bGround)
	{
		m_pOwner->SetGravity(Gravity);	
		m_pOwner->SetGround(m_bGround);
	}
}

