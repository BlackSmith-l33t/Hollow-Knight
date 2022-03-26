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
    Logger::debug(L"OnCollisionEnter_Ground");
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::KNIGHT ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::MONSTER)
    {
        pOtherObj->GetGravity()->SetGround(true);
        fVec2 fvObjPos = _pOther->GetFinalPos();
        fVec2 fvObjScale = _pOther->GetScale();

        fVec2 fvPos = GetCollider()->GetFinalPos();
        fVec2 fvScale = GetCollider()->GetScale();
           
        float wallX = fvPos.x + (fvScale.x / 2.f);
        float wallY = fvPos.y - (fvScale.y / 2.f) + 20.f;
        
        float objX = fvObjPos.x - (fvObjScale.x / 2.f);
        float objY = fvObjPos.y + (fvObjScale.y / 2.f);    

        // 오른쪽 벽
        if (wallX > objX && wallY < objY && !m_bCurGround)
        {
            Logger::debug(L"Wall_Right");
            pOtherObj->m_bWallRight = true;
        }
        // TODO :  왼쪽 벽     
        else if (wallX > objX && wallY < objY && !m_bCurGround)
        {
            Logger::debug(L"Wall_Left");
            pOtherObj->m_bWallLeft = true;
        }
        // TODO :  아래 벽
        else if (wallX > objX && wallY < objY && !m_bCurGround)
        {
            Logger::debug(L"Wall_Under");
            pOtherObj->m_bWallUnder = true;
        }
        else if (!pOtherObj->m_bJump || pOtherObj->m_bCurGround)
        {
            Logger::debug(L"Ground");
          
            pOtherObj->SetPos(fPoint(fvObjPos.x, fvPos.y - (fvObjScale.y + fvScale.y) / 2.f + 1.f));
            pOtherObj->m_fGAccel = 0.f;
            pOtherObj->m_bJump = false;
        }
    }
}

void CGround::OnCollision(CCollider* _pOther)
{
    Logger::debug(L"OnCollision_Ground");
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::KNIGHT ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::MONSTER)
    {
        pOtherObj->GetGravity()->SetGround(true);
        fVec2 fvObjPos = _pOther->GetFinalPos();
        fVec2 fvObjScale = _pOther->GetScale();

        fVec2 fvPos = GetCollider()->GetFinalPos();
        fVec2 fvScale = GetCollider()->GetScale();

        float wallX = fvPos.x + (fvScale.x / 2.f);
        float wallY = fvPos.y - (fvScale.y / 2.f) + 20.f;

        float objX = fvObjPos.x - (fvObjScale.x / 2.f);
        float objY = fvObjPos.y + (fvObjScale.y / 2.f);

        // 오른쪽 벽
        if (wallX > objX && wallY < objY && !m_bCurGround)
        {
            Logger::debug(L"Wall_Right");
            pOtherObj->m_bWallRight = true;
        }
        // TODO :  왼쪽 벽     
        else if (wallX > objX && wallY < objY && !m_bCurGround)
        {
            Logger::debug(L"Wall_Left");
            pOtherObj->m_bWallLeft = true;
        }
        // TODO :  아래 벽
        else if (wallX > objX && wallY < objY && !m_bCurGround)
        {
            Logger::debug(L"Wall_Under");
            pOtherObj->m_bWallUnder = true;
        }
        else if (!pOtherObj->m_bJump)
        {
            Logger::debug(L"Ground");
           
            pOtherObj->SetPos(fPoint(fvObjPos.x, fvPos.y - (fvObjScale.y + fvScale.y) / 2.f + 1.f));
            pOtherObj->m_fGAccel = 0.f;    
            pOtherObj->m_bJump = false;
        }
    }
    //!pOtherObj->m_bWallRight && !m_bPrevGround
}

void CGround::OnCollisionExit(CCollider* _pOther)
{
    Logger::debug(L"OnCollisionExit_Ground");
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::KNIGHT ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::MONSTER)
    {       
       pOtherObj->GetGravity()->SetGround(false);   
       
    }
}
