#include "framework.h"
#include "CScene_Title.h"
#include "CD2DImage.h"
#include "CButtonUI.h"
#include "CBackGround.h"
#include "CImageObject.h"
#include "CImageButton.h"
#include "resource.h"

void ClickStartButton(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::TOWN);
}

void ClickExitButton(DWORD_PTR, DWORD_PTR)
{
	PostQuitMessage(0);
}

void CScene_Title::Enter()
{
	//CD2DImage* m_pTitleImage = CResourceManager::getInst()->LoadD2DImage(L"TitleImage", L"texture\\Title_Background.png");
	/*CBackGround* m_pTitleImage = new CBackGround;
	m_pTitleImage->Load(L"TitleImage", L"texture\\Title\\Title_Background.png");
	m_pTitleImage->SetPos(fPoint(0, 0));
	AddObject(m_pTitleImage, GROUP_GAMEOBJ::BACKGROUND);*/

	CImageObject* m_pImageObject_TitleBackground = new CImageObject;
	m_pImageObject_TitleBackground->Load(L"TitleBackground", L"texture\\Title\\title_background.png");
	m_pImageObject_TitleBackground->SetPos(fPoint(0, 0));
	m_pImageObject_TitleBackground->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pImageObject_TitleBackground, GROUP_GAMEOBJ::BACKGROUND);

	CImageObject* m_pImageObject_TitleText = new CImageObject;
	m_pImageObject_TitleText->Load(L"TitleText", L"texture\\Title\\title_text.png");
	m_pImageObject_TitleText->SetPos(fPoint(WINSIZEX / 2.f - 350.f, WINSIZEY - 650.f));
	m_pImageObject_TitleText->SetScale(fPoint(700.f, 350.f));
	AddObject(m_pImageObject_TitleText, GROUP_GAMEOBJ::BACKGROUND);

	CImageObject* m_pImageObject_whiteFader = new CImageObject;
	m_pImageObject_whiteFader->Load(L"Title_whiteFader", L"texture\\Title\\Main_Menu_White_Fader.png");
	m_pImageObject_whiteFader->SetPos(fPoint(WINSIZEX / 2.f - 200.f, WINSIZEY - 650.f));
	m_pImageObject_whiteFader->SetScale(fPoint(400.f, 250.f));
	AddObject(m_pImageObject_whiteFader, GROUP_GAMEOBJ::BACKGROUND);

	CImageButton* m_pStartButton = new CImageButton;
	m_pStartButton->Load(L"StartText", L"texture\\Title\\StartText.png");
	m_pStartButton->SetScale(fPoint(200.f, 50.f));
	m_pStartButton->SetPos(fPoint(WINSIZEX / 2.f - 100.f, WINSIZEY - 300.f));
	m_pStartButton->SetClickedCallBack(ClickStartButton, 0, 0);
	AddObject(m_pStartButton, GROUP_GAMEOBJ::UI);

	CImageButton* m_pExitButton = new CImageButton;
	m_pExitButton->Load(L"ExitText", L"texture\\Title\\ExitText.png");
	m_pExitButton->SetScale(fPoint(200.f, 50.f));
	m_pExitButton->SetPos(fPoint(WINSIZEX / 2.f - 100.f, WINSIZEY - 240.f));
	m_pExitButton->SetClickedCallBack(ClickExitButton, 0, 0);
	AddObject(m_pExitButton, GROUP_GAMEOBJ::UI);


	// TODO : bmp, cur, 두 개다 시도 했지만 커서는 바뀌지 않음. 원인은 아직 찾기 못함.
	/*HCURSOR hCursor;
	hCursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1));
	SetCursor(hCursor);*/
	//::SetSystemCursor(hCursor, 32512/*OCR_NORMAL*/);

}

void CScene_Title::Exit()
{
	DeleteAll();
}
