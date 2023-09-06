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

	//“–‚½‚è”»’è
	TracColProcess(player);

	if (freeFlag == true) return;

	//ˆÚ“®

	TrackMove(player);



	pos.x += move.x;
	pos.y += move.y;
}

void Children::Draw()
{
	DrawCircle((int)pos.x, (int)pos.y, radius, GetColor(255, 255, 255), true);
}

bool Children::Collision(Player& player)
{
	float r = radius + player.radius;

	float a = pos.x - player.GetPos().x;
	float b = pos.y - player.GetPos().y;
	float c = (float)sqrt(a * a + b * b);

	if (c <= r)
	{
		return true;
	}
	return false;
}

void Children::TracColProcess(Player& player)
{
	if (freeFlag == false) return;

	if (Collision(player) == true)
	{
		freeFlag = false;
		//‚¸‚ê–hŽ~‚Ì‚½‚ß‚¢‚Á‚½‚ñŽ©‹@’†‰›À•W‚Éƒ[ƒv
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
