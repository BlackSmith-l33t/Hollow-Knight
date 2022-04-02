#include "framework.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CGameObject.h"
#include "CTexture.h"

CAnimation::CAnimation()
{
    m_strName = L"";
    m_pAnimator = nullptr;
    m_pImg = nullptr;
    m_iCurFrm = 0;
    m_fAccTime = 0;
    m_bFinish = false;
}

CAnimation::CAnimation(const CAnimation& pOther)
{
    m_strName = pOther.m_strName;
    for (int i = 0; i < pOther.m_vecFrm.size(); i++)
    {
        m_vecFrm.push_back(pOther.m_vecFrm[i]);
    }
    m_iCurFrm = pOther.m_iCurFrm;
    m_fAccTime = pOther.m_fAccTime;
    m_bReverse = pOther.m_bReverse;

    m_pAnimator = nullptr;
    m_pImg = pOther.m_pImg;
}

CAnimation::~CAnimation()
{
}

void CAnimation::SetName(const wstring& strName)
{
    m_strName = strName;
}

const wstring& CAnimation::GetName()
{
    return m_strName;
}

void CAnimation::SetFrame(int frmIndex)
{      
    m_bFinish = false;
    m_iCurFrm = frmIndex;
    m_fAccTime = 0.f;
}

tAniFrm& CAnimation::GetFrame(int frmIndex)
{
    return m_vecFrm[frmIndex];
}

void CAnimation::update()
{    
    if (m_bFinish) return;
    m_fAccTime += fDT;  

    if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
    {        
        //++m_iCurFrm; 마지막 프레임으로 고정할 때
        if (m_iCurFrm >= m_vecFrm.size())
        {
            m_bFinish = true;
            m_iCurFrm = -1;
            m_fAccTime = 0.f;
            return;
        }   
        ++m_iCurFrm;
        m_iCurFrm %= m_vecFrm.size();
        m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;
    }
}

void CAnimation::render()
{
    if (m_bFinish) return;

    CGameObject* pObj = m_pAnimator->GetObj();
    fPoint fptPos = pObj->GetPos();
    fPoint fptScale = pObj->GetScale();
    tAniFrm frm = m_vecFrm[m_iCurFrm];

    fptPos = fptPos + frm.fptOffset;
    fptPos = CCameraManager::getInst()->GetRenderPos(fptPos);


    if (m_bReverse)
    {
        CRenderManager::getInst()->RenderRevFrame(
            m_pImg,
            fptPos.x - fptScale.x / 2.f,
            fptPos.y - fptScale.y / 2.f,
            fptPos.x + fptScale.x / 2.f,
            fptPos.y + fptScale.y / 2.f,
            frm.fptLT.x,
            frm.fptLT.y,
            frm.fptLT.x + frm.fptSlice.x,
            frm.fptLT.y + frm.fptSlice.y
        );
    }
    else
    {
        CRenderManager::getInst()->RenderFrame(
            m_pImg,
            fptPos.x - fptScale.x / 2.f,
            fptPos.y - fptScale.y / 2.f,
            fptPos.x + fptScale.x / 2.f,
            fptPos.y + fptScale.y / 2.f,
            frm.fptLT.x,
            frm.fptLT.y,
            frm.fptLT.x + frm.fptSlice.x,
            frm.fptLT.y + frm.fptSlice.y
        );
    }
}

void CAnimation::Create(CD2DImage* img,     // 애니메이션의 이미지
    fPoint lt,          // 애니메이션 시작 프레임의 좌상단 좌표
    fPoint slice,       // 애니메이션 프레임의 크기
    fPoint step,        // 애니메이션 프레임의 반복 위치
    float duration,     // 애니메이션 프레임 지속시간
    UINT frmCount)      // 애니메이션 프레임 갯수
{
    m_pImg = img;

    tAniFrm frm = {};
    for (UINT i = 0; i < frmCount; i++)
    {
        frm.fDuration = duration;
        frm.fptSlice = slice;
        frm.fptLT = lt + step * i;

        m_vecFrm.push_back(frm);
    }
}

bool CAnimation::IsFinish()
{    
    return m_bFinish; 
}

bool CAnimation::IsFindFrame(int iFrame)
{
    for (int i = 0; i < m_vecFrm.size(); i++)
    {
        if (m_iCurFrm == iFrame) return true;
    }
    return false;
}
