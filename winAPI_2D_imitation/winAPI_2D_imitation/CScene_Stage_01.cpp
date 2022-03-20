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

	// �۾��� ���� �ӽ� ���
	if (Key(VK_F1))
	{
		ChangeScn(GROUP_SCENE::TOWN);
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

void CScene_Stage_01::Enter()
{
	// Ÿ�� �ε�
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Start_01.tile";
	LoadTile(path);

	// TODO : ���� �ٲ���� �� ����Ʈ�� ���?
	CKnight* pKnight = new CKnight;
	pKnight->SetPos(fPoint(2450, 200));
	AddObject(pKnight, GROUP_GAMEOBJ::KNIGHT);

	// ���� ����
	CMonster* pMonster = new CMonster;
	pMonster->SetPos(fPoint(3000, 600));
	AddObject(pMonster, GROUP_GAMEOBJ::MONSTER);
			
	CMap* map = new CMap;
	map->Load(L"Map_Stage01", L"texture\\Background\\Stage_01.png");
	//map->SetPos(fPoint(100.f, -500.f));
	AddObject(map, GROUP_GAMEOBJ::MAP);	

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::KNIGHT, GROUP_GAMEOBJ::TILE);	

	//CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	CCameraManager::getInst()->SetLookAt(fPoint(pKnight->GetPos().x, pKnight->GetPos().y));
	CCameraManager::getInst()->SetTargetObj(pKnight);
}

void CScene_Stage_01::Exit()
{
}
