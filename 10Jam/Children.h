#include "DxLib.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include "Player.h"
#include <vector>
#pragma once

class Children
{
private: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	Children(XMFLOAT2 pos,Player* player);
	~Children();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �폜�m�F�t���O
	/// </summary>
	static bool DleteCheck();
	/// <summary>
	/// �ǐՎq���̔ԍ����Z�b�g
	/// </summary>
	static void TrackChilHitNumReset();

	/// <summary>
	/// �������������q�������m�F����
	/// </summary>
	/// <returns></returns>
	void DleteChildrenCheck();

	void TrackChilOrganize();

	static const int GetHitNum() { return trackChilHitNum; }
private:
	/// <summary>
	/// ���@�Ɠ����蔻��
	/// </summary>
	/// <param name="PlayerPos"></param>
	bool Collision();
	/// <summary>
	/// �v���C���[�Ǐ]����
	/// </summary>
	void Follow2Player();
	/// <summary>
	/// �������~�܂邩
	/// </summary>
	void MountMove();
	/// <summary>
	/// �����ړ�
	/// </summary>
	void MoveFree();
	void TracColProcess();
	
	/// <summary>
	/// ���R�Ȏq�Ƃ̓����蔻�菈��
	/// </summary>
	void FreeChildrenColProcess();
	/// <summary>
	/// �ǐՈړ�
	/// </summary>
	void TrackMove();
	/// <summary>
	/// �ǐՂ��Ă���q�Ƃ̓����蔻�菈��
	/// </summary>
	void TrackChildrenColProcess();

	void ScrollMove();

	bool Spawn();


private:
	Player* player_ = nullptr;
	
	//�����֘A
	bool isMove = false;
	float vel = 0.0f;
	float dir = 1.0f;
	//
	bool isSpawn = true;
	float spawnFrame = 0.0f;
	float kSpawnFrameMax = 15.0f;
	//�ʒu
	XMFLOAT2 pos = { 600.0f, 410.0f };
	XMFLOAT2 move = { 0.0f, 0.0f };
	//���a
	float radius = 8.0f;
	//�S���ԍ�
	int restraintTh = 0;
	//�ǐՈړ��Ԋu
	int trackDis = 15;
	//�����蔻����󂯕t���Ȃ��Œ�S���ԍ�
	int unColRestrainTh = 5;
	XMFLOAT2 moveVec[10] = {};
	std::vector<XMFLOAT2> restrainMoveVec;

	//�ǐՍŌ���m�F�t���O
	bool tailFlag = false;

	//�ǐՎq���Ǝ��@�̓��������ԍ�
	static int trackChilHitNum;
public:
	//�폜�m�F�t���O
	bool deleteFlag = false;
	//�S����Ԋm�F
	bool freeFlag = true;
};


