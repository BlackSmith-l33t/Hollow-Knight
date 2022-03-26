#include "framework.h"
#include "CScene_Town.h"
#include "CD2DImage.h"
#include "CMap.h"
#include "CBackGround.h"
#include "CGameObject.h"
#include "CKnight.h"
#include "CGround.h"

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
	// 타일 로딩
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Town.tile";
	LoadTile(path);

	// Knight 생성
	CKnight* pKnight = new CKnight;
	pKnight->SetPos(fPoint(3130, 2090));
	AddObject(pKnight, GROUP_GAMEOBJ::KNIGHT);
	pKnight->RegisterPlayer();

	CMap* map = new CMap;
	map->Load(L"Map_Town", L"texture\\map\\Map_Town1.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);

	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround_Town", L"texture\\background\\Background_Town.png");
	//backGround->SetPos(fPoint(-100.f, -500.f));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

	CGround* pGround_01 = new CGround;
	pGround_01->SetPos(fPoint(1662.f, 2178.f));
	pGround_01->SetScale(fPoint(2496.f, 64.f));
	AddObject(pGround_01, GROUP_GAMEOBJ::GROUND);

	CGround* pGround_02 = new CGround;
	pGround_02->SetPos(fPoint(2990.f, 2210.f));
	pGround_02->SetScale(fPoint(156.f, 64.f));
	AddObject(pGround_02, GROUP_GAMEOBJ::GROUND);

	CGround* pGround_03 = new CGround;
	pGround_03->SetPos(fPoint(3132.f, 2246.f));
	pGround_03->SetScale(fPoint(130.f, 64.f));
	AddObject(pGround_03, GROUP_GAMEOBJ::GROUND);

	CGround* pGround_04 = new CGround;
	pGround_04->SetPos(fPoint(3600.f, 2280.f));
	pGround_04->SetScale(fPoint(800.f, 64.f));
	AddObject(pGround_04, GROUP_GAMEOBJ::GROUND);

	CGround* pGround_05 = new CGround;
	pGround_05->SetPos(fPoint(3600.f, 2188.f));
	pGround_05->SetScale(fPoint(200.f, 64.f));
	AddObject(pGround_05, GROUP_GAMEOBJ::GROUND);

	CGround* pGround_06 = new CGround;
	pGround_06->SetPos(fPoint(3000.f, 1900.f));
	pGround_06->SetScale(fPoint(200.f, 64.f));
	AddObject(pGround_06, GROUP_GAMEOBJ::GROUND);
	
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::GROUND);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::TILE);

	//CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	//CCameraManager::getInst()->SetLookAt(fPoint(pKnight->GetPos().x, pKnight->GetPos().y));
	//CCameraManager::getInst()->SetTargetObj(pKnight);

	start();
}

void CScene_Town::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
