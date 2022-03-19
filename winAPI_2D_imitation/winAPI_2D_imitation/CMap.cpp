#include "framework.h"
#include "CMap.h"
#include "CD2DImage.h"

CMap::CMap()
{
    m_pImg = nullptr;
}

CMap::~CMap()
{
}

void CMap::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth(), m_pImg->GetHeight()));
}

CMap* CMap::Clone()
{
    return nullptr;
}

void CMap::update()
{
    
}

void CMap::render()
{
    if (nullptr == m_pImg)
    {
        return;
    }
    fPoint pos = GetPos();
    fPoint scale = GetScale();
    //pos = CCameraManager::getInst()->GetRenderPos(pos);
    fPoint renderPos = CCameraManager::getInst()->GetRenderPos(pos);
    renderPos = pos + (renderPos - pos);

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        renderPos.x,
        renderPos.y,
        renderPos.x + scale.x,
        renderPos.y + scale.y
    );
}
