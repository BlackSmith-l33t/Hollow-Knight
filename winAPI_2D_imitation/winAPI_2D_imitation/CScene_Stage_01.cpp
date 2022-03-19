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

	// TODO : 씬이 바뀌었을 때 나이트를 어떻게?
	//CKnight* pKnight = new CKnight;		
	//pKnight->SetPos(fPoint(2000, 2000));
	////pKnight->SetPos(fPoint(200, 500));
	//AddObject(pKnight, GROUP_GAMEOBJ::KNIGHT);

	// 몬스터 생성
	CMonster* pMonster = new CMonster;
	pMonster->SetPos(fPoint(3000, 600));
	AddObject(pMonster, GROUP_GAMEOBJ::MONSTER);
		
	// TODO : 플레이어가 맵을 가장자리로 가면 윈도우가 맵프레임을 벗어나지 않게 설정해야함.
	CMap* map = new CMap;
	map->Load(L"Map_Stage01", L"texture\\map\\Stage_01.png");
	map->SetPos(fPoint(100.f, -500.f));
	AddObject(map, GROUP_GAMEOBJ::MAP);	

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::TILE);	

	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	//CCameraManager::getInst()->SetTargetObj(pKnight);
}

void CScene_Stage_01::Exit()
{
}
