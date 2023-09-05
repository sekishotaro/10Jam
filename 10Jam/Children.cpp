#include "Children.h"
#include "math.h"

Children::Children(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

Children::~Children()
{
}

void Children::Update(Player& player)
{
	Collision(player.GetPos());

	if (FreeFlag == true) return;


}

void Children::Draw()
{
	DrawCircle((int)pos.x, (int)pos.y, radius, GetColor(255, 255, 255), true);
}

void Children::Collision(XMFLOAT2& PlayerPos)
{
	if (FreeFlag == false) return;


	//Ž©‹@
	float PlayerRadius = 10.0f;

	float r = radius + PlayerRadius;


	float a = pos.x - PlayerPos.x;
	float b = pos.y - PlayerPos.y;
	float c = (float)sqrt(a * a + b * b);

	if (c <= r)
	{
		FreeFlag = false;
	}
	else
	{
		FreeFlag = true;
	}

}
