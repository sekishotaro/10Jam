#include "Children.h"
#include "math.h"
#include <random>
#include <ScoreManager.h>
#include <ScrollManager.h>
#include <Helper.h>
#include <Easing.h>
#include "Particle.h"

int Children::trackChilHitNum = 0;
int Children::trackChildrenNum = 0;
float Children::coolTime = 0.0f;

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

	// 波紋エフェクト更新
	UpdateRippleEffect();
}

void Children::Draw() {

	if (freeFlag == true)
	{
		DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(255, 255, 255), true);
	}
	else if( tailFlag == true)
	{
		DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(255, 55, 255), true);
	}
	else
	{
		DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(55, 55, 255), true);
	}
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
		trackChildrenNum++;
	}
}

void Children::TrackMove()
{
	if (player_->isStop) { return; }
	//自機の移動量保存
	restrainMoveVec.push_back(player_->GetMoveVec());
	//最後尾になるように待たせる
	if (restrainMoveVec.size() < size_t(trackDis * restraintTh)) return;
	//最後尾まで行ったか確認フラグ
	tailFlag = true;
	//移動量接地
	move = restrainMoveVec[0];
	//削除
	restrainMoveVec.erase(restrainMoveVec.begin());
}

void Children::TrackChildrenColProcess()
{
	//クールタイム中なら早期リターン
	if (CoolTime() == true) return;
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
		if (trackChilHitNum <= restraintTh)
		{
			trackChilHitNum = restraintTh;
		}
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
	coolTime = 0.0f;
}

void Children::DleteChildrenCheck()
{
	//連結子供の場合チェックを付けずリターン
	if (freeFlag == true)
	{
		deleteFlag = false;
		return;
	}

	//自身の連結番号が当たった番号以下ならフラグを立てる
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

void Children::TrackChilOrganize(XMFLOAT2 alignmentPos, std::vector<XMFLOAT2> restrainMoveVec, int count)
{
	if (freeFlag == true) return;

	restraintTh = count + 1;
	tailFlag = false;
	oldAliPos = pos;
	this->alignmentPos = alignmentPos;
	this->restrainMoveVec.clear();
	this->restrainMoveVec = restrainMoveVec;
}

void Children::ChilAlignment(const float time, const float timeMax)
{
	float timeRate = min(time / timeMax, 1.0f);	//タイムレート 0.0f->1.0f

	if (time >= timeMax)
	{
		pos = alignmentPos;
		return;
	}

	pos.x = Easing::lerp( oldAliPos.x, alignmentPos.x, timeRate);
	pos.y = Easing::lerp(oldAliPos.y, alignmentPos.y, timeRate);
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
	Clamp(spawnFrame, 0.0f, kSpawnFrameMax);
	float sizeFrame = spawnFrame / kSpawnFrameMax;
	radius = Ease(Out, Elastic, sizeFrame, 0, 8.0f);
	if (spawnFrame == kSpawnFrameMax) {
		isSpawn = false;
		radius = 8.0f;
	}
	Particle::Ins()->Ripple(pos, 60u, 64.f, 1ui8, Particle::ColorRGB{ 0xff, 0x22, 0x22 }, 16ui8);
	return true;
}

void Children::UpdateRippleEffect()
{
	// 3フレームに1回波紋エフェクトを出す
	constexpr uint8_t particleInterval = 3u;
	particleFrame = ++particleFrame % particleInterval;
	if (0 == particleFrame)
	{
		// 描画する頂点数
		constexpr uint8_t vertexCount = 4ui8;
		// 発生してから何フレームで消えるか
		constexpr unsigned life = 16u;
		// 終了時点での半径
		constexpr float endRadius = 64.f;
		// 波紋の色
		constexpr auto rippleColor = Particle::ColorRGB{ 0x22, 0xff, 0xff };

		// 波紋エフェクト開始
		Particle::Ins()->Ripple(pos, life, endRadius, 1ui8, rippleColor, vertexCount);
	}
}

bool Children::CoolTime()
{
	const float flame = 60.0f;
	coolTime += 1.0f / flame;

	if (coolTime <= coolTimeMax)
	{
		return true;
	}
	return false;
}
