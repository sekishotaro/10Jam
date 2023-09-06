#include "Children.h"
#include "math.h"

Children::Children(XMFLOAT2 pos, Player* player)
{
	this->pos = pos;
	player_ = player;
}

Children::~Children()
{
}

void Children::Update()
{
	move = {};

	//当たり判定
	TracColProcess();

	if (freeFlag == true) return;

	//移動

	TrackMove();



	pos.x += move.x;
	pos.y += move.y;
}

void Children::Draw()
{
	DrawCircleAA((int)pos.x, (int)pos.y, radius,64, GetColor(255, 255, 255), true);
}

bool Children::Collision()
{
	float r = radius + player_->radius;

	float a = pos.x - player_->GetPos().x;
	float b = pos.y - player_->GetPos().y;
	float c = sqrtf(a * a + b * b);

	if (c <= r)
	{
		return true;
	}
	return false;
}

void Children::TracColProcess()
{
	if (freeFlag == false) return;

	if (Collision() == true)
	{
		freeFlag = false;
		//ずれ防止のためいったん自機中央座標にワープ
		pos = player_->GetPos();
		player_->HitChildren();

		restraintTh = player_->GetChildrenNum();
	}
}

void Children::TrackMove()
{
	restrainMoveVec.push_back(player_->GetMoveVec());

	if (restrainMoveVec.size() < (13 * restraintTh)) return;

	move = restrainMoveVec[0];

	restrainMoveVec.erase(restrainMoveVec.begin());

}
