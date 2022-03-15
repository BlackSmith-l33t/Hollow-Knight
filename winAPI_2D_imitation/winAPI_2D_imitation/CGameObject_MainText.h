#pragma once
#include "CGameObject.h"

class CGameObject_MainText : public CGameObject
{
	wstring startText;
public:
	virtual void Update();
	virtual void Render(HDC hDC);

	void SetText(wstring text);
	wstring GetText();
};

