#include <Windows.h>
#include <d3d12.h>
#include <DirectXMath.h>
#pragma once

class Player
{
private: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	Player();
	~Player();

	/// <summary>
	/// ������
	/// </summary>
	void initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	XMFLOAT2& GetPos() { return pos; }
	XMFLOAT2& GetMoveVec() { return moveVec; }
	int GetChildrenNum() { return childrenNum; }

	void HitChildren();

private:
	void Move();

private:

	XMFLOAT2 pos = { 600.0f, 410.0f };
	XMFLOAT2 moveVec = { 0.0f, 0.0f };
	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };
	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };
	//���a
	const float radius = 10.0f;
	int childrenNum = 0;


	//����
	float rota = 0.0f;


};