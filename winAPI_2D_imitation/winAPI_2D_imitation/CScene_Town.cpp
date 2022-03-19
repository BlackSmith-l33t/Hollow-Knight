#include "framework.h"
#include "CScene_Town.h"
#include "CD2DImage.h"
#include "CMap.h"
#include "CBackGround.h"
#include "CGameObject.h"
#include "CKnight.h"

CScene_Town::CScene_Town()
{
}

CScene_Town::~CScene_Town()
{
}

void CScene_Town::update()
{
	CScene::update();

	if (KeyDown(VK_ESCAPE))
	{
		// TODO : ESC 키를 누르면 종료창을 뜨게 만든다.
	}

	// 작업을 위한 임시 사용
	if (Key(VK_F2))
	{
		ChangeScn(GROUP_SCENE::STAGE_01);
	}

	if (Key(VK_F3))
	{
		ChangeScn(GROUP_SCENE::BOSS);
	}

	if (Key(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
	}
}

void CScene_Town::Enter()
{
	// Knight 생성
	// TODO : knight를 원하는 위치에 초기화
	CKnight* pKnight = new CKnight;
	pKnight->SetPos(fPoint(600, 2090));
	//pKnight->SetPos(fPoint(200, 500));
	AddObject(pKnight, GROUP_GAMEOBJ::KNIGHT);

	CMap* map = new CMap;
	map->Load(L"Map_Start", L"texture\\map\\Map_Town1.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);

	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround_Start", L"texture\\background\\Background_Town.png");
	//backGround->SetPos(fPoint(-100.f, -500.f));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::TILE);

	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	//CCameraManager::getInst()->SetLookAt(fPoint(pKnight->GetPos().x, pKnight->GetPos().y));
	//CCameraManager::getInst()->SetTargetObj(pKnight);

}

void CScene_Town::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
