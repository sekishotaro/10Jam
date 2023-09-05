#include "Children.h"

Children::Children(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

Children::~Children()
{
}

void Children::Update(XMFLOAT2& PlayerPos)
{
	
}

void Children::Draw()
{
	DrawCircle((int)pos.x, (int)pos.y, (int)8.0f, GetColor(255, 255, 255), true);
}
