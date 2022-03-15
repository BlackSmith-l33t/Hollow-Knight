#include "framework.h"
#include "CGameObject_MainText.h"

void CGameObject_MainText::Update()
{

}

void CGameObject_MainText::Render(HDC hDC)
{
	TextOutW(hDC, (int)GetPos().x, (int)GetPos().y, startText.c_str(), (int)startText.size());
}

void CGameObject_MainText::SetText(wstring text)
{
	startText = text;
}

wstring CGameObject_MainText::GetText()
{
	return wstring();
}
