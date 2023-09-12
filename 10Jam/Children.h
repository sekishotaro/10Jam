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

	Children(XMFLOAT2 pos, Player* player, bool isStop = false);
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
	/// <summary>
	/// �c�����A�����Ă���q���̈ʒu�A�ړ��ʂ�ۑ�
	/// </summary>
	/// <param name="alignmentPos"></param>
	/// <param name="restrainMoveVec"></param>
	void TrackChilOrganize(XMFLOAT2 alignmentPos, std::vector<XMFLOAT2> restrainMoveVec, int count);
	
	/// <summary>
	/// �A�������q���̐���
	/// </summary>
	/// <param name="time">���񊄍�����</param>
	void ChilAlignment(const float time, const float timeMax);

	/// <summary>
	/// ���������A���q���̔ԍ�
	/// </summary>
	/// <returns></returns>
	static const int GetHitNum() { return trackChilHitNum; }
	/// <summary>
	/// �A���q���̑S�̐�
	/// </summary>
	/// <returns></returns>
	static const int GetTracChildrenNum() { return trackChildrenNum; }

	DirectX::XMFLOAT2 GetPos() { return pos; }
	std::vector<DirectX::XMFLOAT2> GetRestrainMoveVec() { return restrainMoveVec; }
	int GetRestraintTh() { return restraintTh; }
	bool GetTailFlag() { return tailFlag; }
	void SetIsSlow(const bool flag) { isSlow = flag; dir *= -1.0f; }

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
	/// �ǐՈړ�
	/// </summary>
	void TrackMove();
	/// <summary>
	/// �ǐՂ��Ă���q�Ƃ̓����蔻�菈��
	/// </summary>
	void TrackChildrenColProcess();

	void ScrollMove();

	bool Spawn();

	bool CoolTime();

	/// @brief �g��G�t�F�N�g�X�V
	void UpdateRippleEffect();

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

	XMFLOAT2 alignmentPos = {};
	XMFLOAT2 oldAliPos = {};

	//�ǐՍŌ���m�F�t���O
	bool tailFlag = false;

	uint8_t particleFrame = 0ui8;

	//�ǐՎq���Ǝ��@�̓��������ԍ�
	static int trackChilHitNum;

	//�폜�����Ăэ폜���邽�߂̃N�[���^�C��
	static float coolTime;
	float coolTimeMax = 3.0f;
	
	//�폜�㐮�񂪂��邩�m�F�t���O
	bool alignmentFlag = false;

	bool isSlow = false;
	float slowframe = 0.0f;
	float kSlowframeMax = 300.f;
	float speed = 4.5f;
public:
	//�ǐՎq���S�̐�
	static int trackChildrenNum;
	//�폜�m�F�t���O
	bool deleteFlag = false;
	//�S����Ԋm�F
	bool freeFlag = true;
};


