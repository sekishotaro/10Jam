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

	Children(float x, float y);
	~Children();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Player& player);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();


private:
	/// <summary>
	/// ���@�Ɠ����蔻��
	/// </summary>
	/// <param name="PlayerPos"></param>
	bool Collision(Player& player);


	void TracColProcess(Player& player);
	
	/// <summary>
	/// �ǐՈړ�
	/// </summary>
	void TrackMove(Player& player);

private:
	//�S����Ԋm�F
	bool freeFlag = true;
	//�ʒu
	XMFLOAT2 pos = { 600.0f, 410.0f };
	XMFLOAT2 move = { 0.0f, 0.0f };
	//���a
	const float radius = 8.0f;
	//�S���ԍ�
	int restraintTh = 0;

	XMFLOAT2 moveVec[10] = {};
	std::vector<XMFLOAT2> restrainMoveVec;
};


