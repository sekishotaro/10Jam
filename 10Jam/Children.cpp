#include "Children.h"
#include "math.h"
#include <random>

Children::Children(XMFLOAT2 pos, Player* player)
{
	MountMove();

	this->pos = pos;
	player_ = player;
}

Children::~Children()
{
}

void Children::Update()
{
	//�����蔻��
	TracColProcess();
	Follow2Player();
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
		isMove = true;
	} else {

	}

}

void Children::TracColProcess()
{
	if (freeFlag == false) return;

	if (Collision() == true)
	{
		freeFlag = false;
		//����h�~�̂��߂������񎩋@�������W�Ƀ��[�v
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
