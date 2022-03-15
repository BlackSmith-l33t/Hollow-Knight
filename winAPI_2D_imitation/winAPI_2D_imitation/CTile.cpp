#include "framework.h"
#include "CTile.h"
#include "CTexture.h"

CTile::CTile()
{
	m_pTex = nullptr;
	m_iIdx = 0;
	SetScale(fPoint(SIZE_TILE, SIZE_TILE));
}

CTile::~CTile()
{
}

CTile* CTile::Clone()
{
	return new CTile(*this);
}

void CTile::update()
{
}

void CTile::render(HDC hDC)
{
	if (nullptr == m_pTex)
	{
		return;
	}

	UINT iWidth = m_pTex->GetBmpWidth();
	UINT iHeight = m_pTex->GetBmpHeight();

	UINT iMaxRow = iHeight / SIZE_TILE;
	UINT iMaxCol = iWidth / SIZE_TILE;

	UINT iCurRow = (m_iIdx / iMaxCol) % iMaxRow;
	UINT iCurCol = (m_iIdx % iMaxCol);

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(GetPos());
	fPoint fptScale = GetScale();

	/*TransparentBlt(hDC,
		(int)(fptRenderPos.x),
		(int)(fptRenderPos.y),
		(int)(fptScale.x),
		(int)(fptScale.y),
		m_pTex->GetDC(),
		(int)(iCurCol * SIZE_TILE),
		(int)(iCurRow * SIZE_TILE),
		(int)(fptScale.x),
		(int)(fptScale.y),
		RGB(255, 0, 255));*/
	BitBlt(hDC,
		(int)(fptRenderPos.x),
		(int)(fptRenderPos.y),
		(int)(fptScale.x),
		(int)(fptScale.y),
		m_pTex->GetDC(),
		iCurCol * SIZE_TILE,
		iCurRow * SIZE_TILE,
		SRCCOPY);
}

void CTile::SetTexture(CTexture* pTex)
{
	m_pTex = pTex;
}

void CTile::SetImgIdx(UINT idx)
{
	m_iIdx = idx;
}

void CTile::Save(FILE* pFile)
{
	fwrite(&m_iIdx, sizeof(int), 1, pFile);
}

void CTile::Load(FILE* pFile)
{
	fread(&m_iIdx, sizeof(int), 1, pFile);
}
