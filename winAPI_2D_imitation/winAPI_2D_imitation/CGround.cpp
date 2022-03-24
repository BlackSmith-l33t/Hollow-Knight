#include "framework.h"
#include "CGround.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CKnight.h"

CGround::CGround()
{
    CreateCollider();
}

CGround::~CGround()
{
}

CGameObject* CGround::Clone()
{
    return new CGround(*this);
}


void CGround::start()
{
    GetCollider()->SetScale(GetScale());
}

void CGround::update()
{
}


void CGround::OnCollisionEnter(CCollider* _pOther)
{
    Logger::debug(L"OnCollisionEnter");
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::KNIGHT ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::MONSTER)
    {
        pOtherObj->GetGravity()->SetGround(true);

        fVec2 fvObjPos = _pOther->GetFinalPos();
        fVec2 fvObjScale = _pOther->GetScale();

        fVec2 fvPos = GetCollider()->GetFinalPos();
        fVec2 fvSalse = GetCollider()->GetScale();

        //fvPos.x + (fvSalse.x / 2.f) == (_pOther->GetFinalPos().x - _pOther->GetScale().x / 2.f)
        if (fvPos.y + (fvSalse.y / 2.f) > (_pOther->GetFinalPos().y + _pOther->GetScale().y))
        {
            pOtherObj->m_fvVelocity.x = 0.f;
            fvObjPos = pOtherObj->GetPos();
            pOtherObj->SetPos(fvObjPos);
        }

        pOtherObj->SetPos(fPoint(fvObjPos.x, fvPos.y - (fvObjScale.y + fvSalse.y) / 2.f + 1.f));
        pOtherObj->m_fGAccel = 0.f;
    }
}

void CGround::OnCollision(CCollider* _pOther)
{
    Logger::debug(L"OnCollision");
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::KNIGHT ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::MONSTER)
    {
        pOtherObj->GetGravity()->SetGround(true);

        fVec2 fvObjPos = _pOther->GetFinalPos();
        fVec2 fvObjScale = _pOther->GetScale();

        fVec2 fvPos = GetCollider()->GetFinalPos();
        fVec2 fvSalse = GetCollider()->GetScale();

        if (fvPos.y + (fvSalse.y / 2.f) > (_pOther->GetFinalPos().y + _pOther->GetScale().y))
        {
            pOtherObj->m_fvVelocity.x = 0.f;
            fvObjPos = pOtherObj->GetPos();
            pOtherObj->SetPos(fvObjPos);
        }

        pOtherObj->SetPos(fPoint(fvObjPos.x, fvPos.y - (fvObjScale.y + fvSalse.y) / 2.f + 1.f));
        pOtherObj->m_fGAccel = 0.f;

    }
}

void CGround::OnCollisionExit(CCollider* _pOther)
{
    Logger::debug(L"OnCollisionExit");
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::KNIGHT ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::MONSTER)
    {
        pOtherObj->GetGravity()->SetGround(false);
    }
}
