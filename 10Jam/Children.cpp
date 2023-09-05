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
	Collision(player);

	if (freeFlag == true) return;



}

void Children::Draw()
{
	DrawCircle((int)pos.x, (int)pos.y, radius, GetColor(255, 255, 255), true);
}

void Children::Collision(Player& player)
{
	if (freeFlag == false) return;


	//Ž©‹@
	float PlayerRadius = 10.0f;

	float r = radius + PlayerRadius;


	float a = pos.x - player.GetPos().x;
	float b = pos.y - player.GetPos().y;
	float c = (float)sqrt(a * a + b * b);

	if (c <= r)
	{
		freeFlag = false;
		player.HitChildren();

		restraintTh = player.GetChildrenNum();
	}

}
