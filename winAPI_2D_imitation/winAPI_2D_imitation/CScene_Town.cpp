#include "framework.h"
#include "CScene_Town.h"
#include "CD2DImage.h"
#include "CMap.h"
#include "CBackGround.h"
#include "CGameObject.h"
#include "CKnight.h"
#include "CGround.h"
#include "CMonster.h"

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
	pKnight->SetPos(fPoint(2000, 2178.f));
	AddObject(pKnight, GROUP_GAMEOBJ::KNIGHT);
	pKnight->RegisterPlayer();	

	/*CMonster* pMonNormal = CMonster::Create(MON_TYPE::NORMAL, fPoint(2500.f, 2096.f));
	AddObject(pMonNormal, GROUP_GAMEOBJ::MONSTER);*/

	CMonster* pMonTrace = CMonster::Create(MON_TYPE::TRACE, fPoint(1500.f, 2096.f));
	AddObject(pMonTrace, GROUP_GAMEOBJ::MONSTER);	

	/*CMonster* pMonFly = CMonster::Create(MON_TYPE::FLY, fPoint(1800.f, 1800.f));
	AddObject(pMonFly, GROUP_GAMEOBJ::MONSTER);*/


	CMap* map = new CMap;
	map->Load(L"Map_Town", L"texture\\map\\Map_Town1.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);

	/*CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround_Town", L"texture\\background\\Background_Town.png");
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);*/

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
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::NAIL, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MONSTER, GROUP_GAMEOBJ::GROUND);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::SOUL_MISSILE, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::SOUL_MISSILE, GROUP_GAMEOBJ::GROUND);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MONSTER_MISSILE, GROUP_GAMEOBJ::GROUND);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MONSTER_MISSILE, GROUP_GAMEOBJ::KNIGHT);

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
