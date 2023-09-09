#include <Windows.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "Score/ScoreManager.h"

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
	XMFLOAT2 GetMoveVec() { return moveVec; }
	int GetChildrenNum() { return childrenNum; }

	void HitChildren();

	void AddCoin() {getCoin = true; coinFrame= 0.0f;}
	void SetBoost(const bool isBoost) { this->isBoost = isBoost; }
	bool GetBoost() { return isBoost; }
	void Childrendelete();

private:
	void Move();
	void CoinDash();
	void Dash();
	void RotaUpdate();
private:
	XMFLOAT2 pos = { 600.0f, 410.0f };
	XMFLOAT2 moveAdd = {};
	XMFLOAT2 moveVec = { 0.0f, 0.0f };
	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };
	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };
	
	int childrenNum = 0;
	//����
	float rota = 0.0f;
	float rotaVal = 3.0f;

	bool isBoost = false;
	float boostFrame = 0.0f;
	float kBoostFrameMax = 120.0f;
	float accel = 1.0f;

	bool getCoin = false;
	float coinBoost = 1.0f;
	float coinFrame = 0.0f;
	float kCoinFrameMax = 30.0f;

public:
	bool isStop = false;
	//���a
	const float radius = 20.0f;

	bool playerStop = false;
};