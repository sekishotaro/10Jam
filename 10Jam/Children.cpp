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
	//�����蔻��
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

	//�ړ�
	TrackMove();

	pos.x += move.x;
	pos.y += move.y;
}

void Children::MountMove() {
	std::random_device seed_gen;
	std::default_random_engine engine(seed_gen());

	// -100�ȏ�100�ȉ��̒l�𓙊m���Ŕ���������
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
		//����h�~�̂��߂������񎩋@�������W�Ƀ��[�v
		pos = player_->GetPos();
		player_->HitChildren();
		restraintTh = player_->GetChildrenNum();
	}
}

void Children::TrackMove()
{
	//���@�̈ړ��ʕۑ�
	restrainMoveVec.push_back(player_->GetMoveVec());
	//�Ō���ɂȂ�悤�ɑ҂�����
	if (restrainMoveVec.size() < (trackDis * restraintTh)) return;
	//�Ō���܂ōs�������m�F�t���O
	tailFlag = true;
	//�ړ��ʐڒn
	move = restrainMoveVec[0];
	//�폜
	restrainMoveVec.erase(restrainMoveVec.begin());
}

void Children::TrackChildrenColProcess()
{
	//���R�q���͑������^�[��
	if (freeFlag == true) return;

	//�ǐՎq���ɂȂ����΂���̏ꍇ�͔��肵�Ȃ�
	if (tailFlag == false) return;

	//���@����X�ȉ��̎q���̏ꍇ�͔��肵�Ȃ�
	if (restraintTh <= unColRestrainTh) return;

	//���@�Ƃ̓����蔻��
	if (Collision() == true)
	{
		//�O���[�o���ϐ��ɕۊǁ@�ۊǂ���Ă�������葽���ꍇ�㏑��
		trackChilHitNum = restraintTh;
	}
}

bool Children::DleteCheck()
{
	//�ǐՎq���ɓ��������ԍ���0�Ȃ疳��
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
