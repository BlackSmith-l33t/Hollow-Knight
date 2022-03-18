#include "framework.h"
#include "CScene_Stage_01.h"
#include "CKnight.h"
#include "CMonster.h"
#include "CMap.h"
#include "CBackGround.h"

CScene_Stage_01::CScene_Stage_01()
{

}

CScene_Stage_01::~CScene_Stage_01()
{

}

void CScene_Stage_01::update()
{
	CScene::update();

	if (Key(VK_ESCAPE))
	{
		ChangeScn(GROUP_SCENE::TITLE);
	}

	if (Key(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
	}
}

void CScene_Stage_01::Enter()
{
	// 타일 로딩
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Start_01.tile";
	LoadTile(path);

	// Knight 생성
	CKnight* pKnight = new CKnight;
	pKnight->SetPos(fPoint(300, 500));
	AddObject(pKnight, GROUP_GAMEOBJ::KNIGHT);
	// TODO : knight를 원하는 위치에 초기화

	/*CMap* map = new CMap;
	map->Load(L"Map_Stage01", L"texture\\map\\Stage01.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);*/

	CBackGround* backGround = new CBackGround;
	backGround->Load(L"Map_Stage01", L"texture\\map\\real.png");
	backGround->SetPos(fPoint(-100.f, -500.f));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

	// 몬스터 생성
	CMonster* pMonster = new CMonster;
	pMonster->SetPos(fPoint(1000, 400));
	AddObject(pMonster, GROUP_GAMEOBJ::MONSTER);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::TILE);

	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	CCameraManager::getInst()->SetTargetObj(pKnight);
}

void CScene_Stage_01::Exit()
{
}
