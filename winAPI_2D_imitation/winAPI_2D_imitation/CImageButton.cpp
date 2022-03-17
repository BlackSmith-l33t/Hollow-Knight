#include "framework.h"
#include "CImageButton.h"

CImageButton::CImageButton()
{
	m_pImg = nullptr;
}

CImageButton::~CImageButton()
{
}

void CImageButton::render()
{
	if (nullptr != m_pImg)
	{
		CRenderManager::getInst()->RenderImage(
			m_pImg,
			GetPos().x,
			GetPos().y,
			GetPos().x + GetScale().x,
			GetPos().y + GetScale().y
		);
	}
}

void CImageButton::Load(const wstring& strKey, const wstring& strRelativePath)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strRelativePath);
}
