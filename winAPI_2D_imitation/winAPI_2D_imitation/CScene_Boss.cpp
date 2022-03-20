#include "framework.h"
#include "CScene.h"
#include "CScene_Boss.h"
#include "CMonster.h"
#include "CMap.h"
#include "CBackGround.h"
#include "CKnight.h"



CScene_Boss::CScene_Boss()
{
}

CScene_Boss::~CScene_Boss()
{
}

void CScene_Boss::update()
{
	CScene::update();

	if (KeyDown(VK_ESCAPE))
	{
		// TODO : ESC 키를 누르면 종료창을 뜨게 만든다.
	}

	// 작업을 위한 임시 사용
	if (Key(VK_F1))
	{
		ChangeScn(GROUP_SCENE::TOWN);
	}

	if (Key(VK_F2))
	{
		ChangeScn(GROUP_SCENE::STAGE_01);
	}

	if (Key(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
	}
}

void CScene_Boss::Enter()
{
	// 타일 로드
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Boss.tile";
	LoadTile(path);

	CKnight* pKnight = new CKnight;
	pKnight->SetPos(fPoint(300, 860));
	AddObject(pKnight, GROUP_GAMEOBJ::KNIGHT);

	CMap* map = new CMap;
	map->Load(L"Map_Boss", L"texture\\map\\Map_Boss.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);

	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround_Boss", L"texture\\background\\Background_Boss.png");
	//backGround->SetPos(fPoint(-100.f, -500.f));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::TILE);

	CCameraManager::getInst()->SetLookAt(fPoint(pKnight->GetPos().x, pKnight->GetPos().y));
	CCameraManager::getInst()->SetTargetObj(pKnight);

}

void CScene_Boss::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
