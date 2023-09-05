#include "DxLib.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include "Player.h"
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
	void Collision(XMFLOAT2& PlayerPos);



private:
	//�S����Ԋm�F
	bool FreeFlag = true;
	//�ʒu
	XMFLOAT2 pos = { 600.0f, 410.0f };
	//���a
	const float radius = 8.0f;
};


