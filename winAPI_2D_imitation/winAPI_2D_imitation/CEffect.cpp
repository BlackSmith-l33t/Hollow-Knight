#include "framework.h"
#include "CEffect.h"

CEffect::CEffect()
{
}

CEffect::~CEffect()
{
}

CEffect* CEffect::Clone()
{
	return new CEffect;
}

void CEffect::update()
{
}

void CEffect::render()
{
}

void CEffect::OnCollision(CCollider* _pOther)
{
}

void CEffect::OnCollisionEnter(CCollider* _pOther)
{
}

void CEffect::OnCollisionExit(CCollider* _pOther)
{
}
