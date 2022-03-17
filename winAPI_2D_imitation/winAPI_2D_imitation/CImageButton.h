#pragma once
#include "CButtonUI.h"

class CD2DImage;

class CImageButton : public CButtonUI
{
private:
	CD2DImage* m_pImg;
public:
	CImageButton();
	virtual ~CImageButton();

	virtual void render();
	
	void Load(const wstring& strKey, const wstring& strRelativePath);
};

