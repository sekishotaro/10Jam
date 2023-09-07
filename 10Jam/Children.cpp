#include "Children.h"
#include "math.h"
#include <random>
#include <ScoreManager.h>
#include <ScrollManager.h>
#include <Helper.h>
#include <Easing.h>

int Children::trackChilHitNum = 0;

Children::Children(XMFLOAT2 pos, Player* player) {
	MountMove();
	this->pos = pos;
	player_ = player;
}

Children::~Children() {
}

void Children::Update() {
	if (Spawn()) { return; }
	//当たり判定
	TracColProcess();
	Follow2Player();
	MoveFree();
	ScrollMove();
	TrackChildrenColProcess();
}

void Children::Draw() {
	DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(255, 255, 255), true);
}

bool Children::Collision() {
	float r = radius + player_->radius;

	float a = pos.x - player_->GetPos().x;
	float b = pos.y - player_->GetPos().y;
	float c = sqrtf(a * a + b * b);

	if (c <= r) {
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
	std::random_device seed_gen;
	std::default_random_engine engine(seed_gen());

	// -100以上100以下の値を等確率で発生させる
	std::uniform_int_distribution<> dist(0, 100);
	int rand = dist(engine);
	if (rand < 30) {
		if (rand < 15) {
			dir = -1.0f;
		} else {
			dir = 1.0f;
		}
		isMove = true;
	} else {
		isMove = false;
	}

}

void Children::MoveFree() {
	if (!freeFlag) return;
	if (!isMove) return;
	move = {};
	vel += 0.05f;
	move.x = cosf(vel) * 4.5f;
	move.y = sinf(vel) * 4.5f;
	pos.x += move.x * dir;
	pos.y += move.y * dir;
}

void Children::TracColProcess() {
	if (freeFlag == false) return;

	if (Collision() == true) {
		freeFlag = false;
		ScoreManager::GetInstance()->AddScore(10);
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
	if (freeFlag == true)
	{
		deleteFlag = false;
		return;
	}
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
	if (freeFlag == true) return;

	restraintTh -= (trackChilHitNum);
	pos = player_->GetPos();
	tailFlag = false;
	restrainMoveVec.clear();
	restrainMoveVec.push_back(player_->GetMoveVec());
}

void Children::ScrollMove() {
	XMFLOAT2 scroll = ScrollManager::GetInstance()->GetMove();
	pos.x -= scroll.x;
	pos.y -= scroll.y;
}

bool Children::Spawn() {
	if (!isSpawn) { return false; }
	ScrollMove();
	spawnFrame += 1.0f;
	Clamp(spawnFrame,0.0f, kSpawnFrameMax);
	float sizeFrame = spawnFrame / kSpawnFrameMax;
	radius = Ease(Out,Elastic, sizeFrame,0,8.0f);
	if (spawnFrame == kSpawnFrameMax) {
		isSpawn = false;
		radius = 8.0f;
	}
	return true;
}
