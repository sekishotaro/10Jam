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
	move = {};

	//当たり判定
	Collision(player);

	if (freeFlag == true) return;

	//移動

	TrackMove(player);



	pos.x += move.x;
	pos.y += move.y;
}

void Children::Draw()
{
	DrawCircle((int)pos.x, (int)pos.y, radius, GetColor(255, 255, 255), true);
}

void Children::Collision(Player& player)
{
	if (freeFlag == false) return;


	//自機
	float PlayerRadius = 10.0f;

	float r = radius + PlayerRadius;


	float a = pos.x - player.GetPos().x;
	float b = pos.y - player.GetPos().y;
	float c = (float)sqrt(a * a + b * b);

	if (c <= r)
	{
		freeFlag = false;
		//ずれ防止のためいったん自機中央座標にワープ
		pos = player.GetPos();
		player.HitChildren();
		
		restraintTh = player.GetChildrenNum();
	}

}

void Children::TrackMove(Player& player)
{
	restrainMoveVec.push_back(player.GetMoveVec());

	if (restrainMoveVec.size() < (13 * restraintTh)) return;

	move = restrainMoveVec[0];

	restrainMoveVec.erase(restrainMoveVec.begin());

}
