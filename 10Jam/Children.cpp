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
