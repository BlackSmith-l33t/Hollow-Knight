#pragma once

class CTexture;

class CCore
{
	SINGLETON(CCore);

private:
	HDC m_hDC;
	CTexture* m_pMemTex;

	// GDI
	HBRUSH m_arrBrush[(int)TYPE_BRUSH::SIZE];
	HPEN m_arrPen[(int)TYPE_PEN::SIZE];

public:
	void update();
	void render();
	void init();

	HDC GetMainDC();

	void CreateBrushPen();
	HBRUSH GetBrush(TYPE_BRUSH type);
	HPEN GetPen(TYPE_PEN type);
};

