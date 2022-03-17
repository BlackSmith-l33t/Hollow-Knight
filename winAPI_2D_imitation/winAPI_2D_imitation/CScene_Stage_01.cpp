#include "framework.h"
#include "CScene_Stage_01.h"
#include "CKnight.h"

CScene_Stage_01::CScene_Stage_01()
{

}

CScene_Stage_01::~CScene_Stage_01()
{

}

void CScene_Stage_01::update()
{
	CScene::update();

	if (KeyDown(VK_ESCAPE))
	{
		ChangeScn(GROUP_SCENE::TITLE);
	}
}

void CScene_Stage_01::Enter()
{
	// Knight »ý¼º
	CKnight* pKnight = new CKnight;
	pKnight->SetPos(fPoint(200, 500));
	AddObject(pKnight, GROUP_GAMEOBJ::KNIGHT);

}

void CScene_Stage_01::Exit()
{
}
