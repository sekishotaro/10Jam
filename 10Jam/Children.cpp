#include "Children.h"
#include "math.h"

int Children::trackChilHitNum = 0;

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
	//当たり判定
	FreeChildrenColProcess();
	Follow2Player();
	TrackChildrenColProcess();
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

void Children::Follow2Player() {
	if (freeFlag == true) return;
	move = {};

	//移動
	TrackMove();

	pos.x += move.x;
	pos.y += move.y;
}

void Children::MountMove() {



}

void Children::FreeChildrenColProcess()
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
	//自機の移動量保存
	restrainMoveVec.push_back(player_->GetMoveVec());
	//最後尾になるように待たせる
	if (restrainMoveVec.size() < (trackDis * restraintTh)) return;
	//最後尾まで行ったか確認フラグ
	tailFlag = true;
	//移動量接地
	move = restrainMoveVec[0];
	//削除
	restrainMoveVec.erase(restrainMoveVec.begin());
}

void Children::TrackChildrenColProcess()
{
	//自由子供は早期リターン
	if (freeFlag == true) return;

	//追跡子供になったばかりの場合は判定しない
	if (tailFlag == false) return;

	//自機からX個以下の子供の場合は判定しない
	if (restraintTh <= unColRestrainTh) return;

	//自機との当たり判定
	if (Collision() == true)
	{
		//グローバル変数に保管　保管されていた数より多い場合上書き
		trackChilHitNum = restraintTh;
	}
}

bool Children::DleteCheck()
{
	//追跡子供に当たった番号が0なら無し
	if (trackChilHitNum == 0) return false;

	return true;
}

void Children::TrackChilHitNumReset()
{
	trackChilHitNum = 0;
}

void Children::DleteChildrenCheck()
{
	if (restraintTh <= trackChilHitNum)
	{
		deleteFlag = true;
		player_->Childrendelete();
	}
	else
	{
		deleteFlag = false;
	}
}

void Children::TrackChilOrganize()
{
	restraintTh -= (trackChilHitNum);
	pos = player_->GetPos();
	tailFlag = false;
	restrainMoveVec.clear();
	restrainMoveVec.push_back(player_->GetMoveVec());
}
