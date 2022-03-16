#include "framework.h"
#include "CScene_Title.h"
#include "CD2DImage.h"
#include "CButtonUI.h"
#include "CBackGround.h"

void ClickStartButton(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::STAGE_01);
}

void ClickExitButton()
{

}

void CScene_Title::Enter()
{
	//CD2DImage* m_pTitleImage = CResourceManager::getInst()->LoadD2DImage(L"TitleImage", L"texture\\Title_Background.png");
	CBackGround* m_pTitleImage = new CBackGround;
	m_pTitleImage->Load(L"TitleImage", L"texture\\Title\\Title_Background.png");
	m_pTitleImage->SetPos(fPoint(0, 0));
	AddObject(m_pTitleImage, GROUP_GAMEOBJ::BACKGROUND);


	CButtonUI* m_pStartButton = new CButtonUI;
	m_pStartButton->SetScale(fPoint(100.f, 50.f));
	m_pStartButton->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY - 300.f));
	m_pStartButton->SetClickedCallBack(ClickStartButton, 0, 0);
	AddObject(m_pStartButton, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pExitButton = new CButtonUI;
	m_pExitButton->SetScale(fPoint(100.f, 50.f));
	m_pExitButton->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY - 220.f));
	AddObject(m_pExitButton, GROUP_GAMEOBJ::UI);
}

void CScene_Title::Exit()
{
	DeleteAll();
}
