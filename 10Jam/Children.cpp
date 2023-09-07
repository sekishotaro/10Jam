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
	//�����蔻��
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

	//�ړ�
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
