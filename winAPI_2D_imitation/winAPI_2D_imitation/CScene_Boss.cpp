#include "framework.h"
#include "CScene_Boss.h"
#include "CMonster.h"
#include "CMap.h"
#include "CBackGround.h"



CScene_Boss::CScene_Boss()
{
}

CScene_Boss::~CScene_Boss()
{
}

void CScene_Boss::Enter()
{
	CScene::update();

	if (KeyDown(VK_ESCAPE))
	{
		// TODO : ESC 키를 누르면 종료창을 뜨게 만든다.
	}

	CMap* map = new CMap;
	map->Load(L"Map_Start", L"texture\\map\\Map_Boss.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);

	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround_Start", L"texture\\background\\Background_Boss.png");
	//backGround->SetPos(fPoint(-100.f, -500.f));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::TILE);

	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	//CCameraManager::getInst()->SetTargetObj(pKnight);

}

void CScene_Boss::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
