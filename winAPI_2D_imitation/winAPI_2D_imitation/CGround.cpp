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
    CGameObject* pOtherObj = _pOther->GetObj();

    if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::KNIGHT ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::MONSTER)
    {
        pOtherObj->GetGravity()->SetGround(true);
        fVec2 fvObjPos = _pOther->GetFinalPos();
        fVec2 fvObjScale = _pOther->GetScale();

        fVec2 fvPos = GetCollider()->GetFinalPos();
        fVec2 fvScale = GetCollider()->GetScale();
           

        // 오른쪽 Ground와 충돌시 
        float fWallX_Right = fvPos.x + (fvScale.x / 2.f);
        float fWallY_Top = fvPos.y;// -(fvScale.y / 2.f) + 20.f;
        float fWallY_Bottom = fvPos.y + (fvScale.y / 2.f) - 30.f;

        float objX_Left = fvObjPos.x - (fvObjScale.x / 2.f);
        float objY_Bottom = fvObjPos.y + (fvObjScale.y / 2.f);

        // 왼쪽 Ground와 충돌시 
        float fWallX_Left = fvPos.x - (fvScale.x / 2.f);
        //float fWallY_Left = fvPos.y - (fvScale.y / 2.f) + 20.f;

        float objX_Right = fvObjPos.x + (fvObjScale.x / 2.f);    

        // 아래쪽 Ground와 충돌시
        float objY_Top = fvObjPos.y - (fvObjScale.y / 2.f);

        // 아래 벽 
        if (fWallY_Top <= objY_Top && fWallY_Bottom <= objY_Top)
        {
            pOtherObj->m_bWallBottom = true;          
        }
        // 왼쪽 벽     
        else if (fWallX_Left < objX_Right && fWallX_Left > objX_Left && fWallY_Top < objY_Bottom && !m_bCurGround)
        {
            pOtherObj->m_bWallLeft = true;
        }
        // 오른쪽 벽
        else if (fWallX_Right > objX_Left && fWallX_Right < objX_Right && fWallY_Top < objY_Bottom && !m_bCurGround)
        {          
            pOtherObj->m_bWallRight = true;
        }      
        else if (!pOtherObj->m_bJump || pOtherObj->m_bCurGround)
        {
          
            pOtherObj->SetPos(fPoint(fvObjPos.x, fvPos.y - (fvObjScale.y + fvScale.y) / 2.f + 1.f));
            pOtherObj->m_fGAccel = 0.f;
            pOtherObj->m_bJump = false;
        }
        
    }
}

void CGround::OnCollision(CCollider* _pOther)
{
    CGameObject* pOtherObj = _pOther->GetObj();

    if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::KNIGHT ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::MONSTER)
    {
        pOtherObj->GetGravity()->SetGround(true);
        fVec2 fvObjPos = _pOther->GetFinalPos();
        fVec2 fvObjScale = _pOther->GetScale();

        fVec2 fvPos = GetCollider()->GetFinalPos();
        fVec2 fvScale = GetCollider()->GetScale();

        // 오른쪽 Ground와 충돌시 
        float fWallX_Right = fvPos.x + (fvScale.x / 2.f);
        float fWallY_Top = fvPos.y;// -(fvScale.y / 2.f) + 20.f;
        float fWallY_Bottom = fvPos.y + (fvScale.y / 2.f) - 30.f;

        float objX_Left = fvObjPos.x - (fvObjScale.x / 2.f);
        float objY_Bottom = fvObjPos.y + (fvObjScale.y / 2.f);

        // 왼쪽 Ground와 충돌시 
        float fWallX_Left = fvPos.x - (fvScale.x / 2.f);       

        float objX_Right = fvObjPos.x + (fvObjScale.x / 2.f);      
     
        // 아래쪽 Ground와 충돌시
        float objY_Top = fvObjPos.y - (fvObjScale.y / 2.f);
     

        // 아래 벽 
        if (fWallY_Top <= objY_Top && fWallY_Bottom <= objY_Top)
        {
            pOtherObj->m_bWallBottom = true;
            
        }
        // 왼쪽 벽     
        else if (fWallX_Left < objX_Right && fWallX_Left > objX_Left && fWallY_Top < objY_Bottom && !m_bCurGround)
        {
            pOtherObj->m_bWallLeft = true;
        }
        // 오른쪽 벽
        else if (fWallX_Right > objX_Left && fWallX_Right < objX_Right && fWallY_Top < objY_Bottom && !m_bCurGround)
        {
            if (fWallY_Top < objY_Top && fWallY_Bottom < objY_Top)
            {
                pOtherObj->m_bWallBottom = true;
                return;
            }
            pOtherObj->m_bWallRight = true;
        }      
        else if (!pOtherObj->m_bJump)
        {
            pOtherObj->SetPos(fPoint(fvObjPos.x, fvPos.y - (fvObjScale.y + fvScale.y) / 2.f + 1.f));
            pOtherObj->m_fGAccel = 0.f;    
            pOtherObj->m_bJump = false;
        }
    }
}

void CGround::OnCollisionExit(CCollider* _pOther)
{
    CGameObject* pOtherObj = _pOther->GetObj();

    if (pOtherObj->GetObjType() == GROUP_GAMEOBJ::KNIGHT ||
        pOtherObj->GetObjType() == GROUP_GAMEOBJ::MONSTER)
    {       
       pOtherObj->GetGravity()->SetGround(false);   
       
    }
}