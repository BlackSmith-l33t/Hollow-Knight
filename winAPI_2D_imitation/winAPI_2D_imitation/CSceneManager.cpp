#include "framework.h"
#include "CSceneManager.h"

#include "CScene_Title.h"
#include "CScene_Town.h"
#include "CScene_Stage_01.h"
#include "CScene_Boss.h"
#include "CScene_Tool.h"

CSceneManager::CSceneManager()
{
	// ?? ???? ?ʱ?ȭ
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		m_arrScene[i] = nullptr;
	}
	m_pCurScene = nullptr;
}

CSceneManager::~CSceneManager()
{
	// ?? ???? ????
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneManager::ChangeScene(GROUP_SCENE scene)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)scene];
	m_pCurScene->Enter();
}

void CSceneManager::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}

void CSceneManager::render()
{
	m_pCurScene->render();
}

void CSceneManager::init()
{
	m_arrScene[(size_t)GROUP_SCENE::TITLE] = new CScene_Title;
	m_arrScene[(size_t)GROUP_SCENE::TITLE]->SetName(L"Title_Scene");

	m_arrScene[(size_t)GROUP_SCENE::TOWN] = new CScene_Town;
	m_arrScene[(size_t)GROUP_SCENE::TOWN]->SetName(L"Tonw_Scene");

	m_arrScene[(size_t)GROUP_SCENE::STAGE_01] = new CScene_Stage_01;
	m_arrScene[(size_t)GROUP_SCENE::STAGE_01]->SetName(L"Stage01_Scene");
	
	m_arrScene[(size_t)GROUP_SCENE::BOSS] = new CScene_Boss;
	m_arrScene[(size_t)GROUP_SCENE::BOSS]->SetName(L"Boss_Scene");

	m_arrScene[(size_t)GROUP_SCENE::TOOL] = new CScene_Tool;
	m_arrScene[(size_t)GROUP_SCENE::TOOL]->SetName(L"Tool_Scene");

	m_pCurScene = m_arrScene[(size_t)GROUP_SCENE::TOWN];
	m_pCurScene->Enter();
}

CScene* CSceneManager::GetCurScene()
{
	return m_pCurScene;
}
