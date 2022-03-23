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
    if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::KNIGHT  ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::MONSTER ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::BOSS)
    {
        pOtherObj->GetGravity()->SetGround(true);
        
        fVec2 fvObjPos = _pOther->GetFinalPos();
        fVec2 fvObjScale = _pOther->GetScale();

        fVec2 fvPos = GetCollider()->GetFinalPos();
        fVec2 fvSalse = GetCollider()->GetScale();

        float fLen = abs(fvObjPos.y - fvPos.y);
        float fValue = (fvObjScale.y / 2.f + fvSalse.y / 2.f) - fLen;

        fvObjPos = pOtherObj->GetPos();
        fvObjPos.y -= fValue;
        pOtherObj->SetPos(fvObjPos);   
    }
}

void CGround::OnCollision(CCollider* _pOther)
{
    Logger::debug(L"OnCollision");
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::KNIGHT ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::MONSTER ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::BOSS)
    {
        pOtherObj->GetGravity()->SetGround(true);

        fVec2 fvObjPos = _pOther->GetFinalPos();
        fVec2 fvObjScale = _pOther->GetScale();

        fVec2 fvPos = GetCollider()->GetFinalPos();
        fVec2 fvSalse = GetCollider()->GetScale();

        float fLen = abs(fvObjPos.y - fvPos.y);
        float fValue = (fvObjScale.y / 2.f + fvSalse.y / 2.f) - fLen;

        fvObjPos = pOtherObj->GetPos();
        fvObjPos.y -= fValue;
        pOtherObj->SetPos(fvObjPos);
    }
}

void CGround::OnCollisionExit(CCollider* _pOther)
{
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::KNIGHT ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::MONSTER ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::BOSS)
    {
        pOtherObj->GetGravity()->SetGround(false);
    }
}
