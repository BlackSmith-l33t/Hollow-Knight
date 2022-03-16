#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerImg", L"texture\\Animation\\Knight\\knight.png");
	SetName(L"Player");
	SetScale(fPoint(80.f, 80.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(35.f, 80.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"LeftNone", m_pImg, fPoint(0.f, 0.f), fPoint(80.f, 80.f), fPoint(80.f, 80.f), 0.5f, 1);
	GetAnimator()->CreateAnimation(L"RightNone", m_pImg, fPoint(0.f, 0.f), fPoint(80.f, 80.f), fPoint(80.f, 0.f), 0.5f, 1);
	GetAnimator()->CreateAnimation(L"LeftMove", m_pImg, fPoint(0.f, 0.f), fPoint(80.f, 80.f), fPoint(80.f, 0.f), 0.01f, 9);
	GetAnimator()->CreateAnimation(L"RightMove", m_pImg, fPoint(0.f, 0.f), fPoint(80.f, 80.f), fPoint(80.f, 0.f), 0.08f, 6);
	GetAnimator()->CreateAnimation(L"LeftHit", m_pImg, fPoint(160.f, 0.f), fPoint(80.f, 80.f), fPoint(80.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"RightHit", m_pImg, fPoint(160.f, 80.f), fPoint(80.f, 80.f), fPoint(80.f, 0.f), 0.25f, 1);
	GetAnimator()->Play(L"RightNone");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"LeftMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, 0.f);
	pAni = GetAnimator()->FindAnimation(L"RightMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, 0.f);
}

CPlayer::~CPlayer()
{

}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::update()
{
	fPoint pos = GetPos();

	if (Key(VK_LEFT))
	{
		pos.x -= m_fVelocity * fDT;
		GetAnimator()->Play(L"LeftMove");
	}
	if (KeyDown(VK_RIGHT))
	{
		pos.x += m_fVelocity * fDT;
		GetAnimator()->Play(L"RightMove");
	}
	if (Key(VK_UP))
	{
		pos.y -= m_fVelocity * fDT;
	}
	if (Key(VK_DOWN))
	{
		pos.y += m_fVelocity * fDT;
	}

	SetPos(pos);

	if (KeyDown(VK_SPACE))
	{
		CreateMissile();
		GetAnimator()->Play(L"LeftHit");
	}

	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::CreateMissile()
{
	fPoint fpMissilePos = GetPos();
	fpMissilePos.x += GetScale().x / 2.f;

	// Misiile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(fpMissilePos);
	pMissile->SetDir(fVec2(1, 0));

	CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
}
