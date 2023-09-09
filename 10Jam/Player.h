#include <Windows.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "Score/ScoreManager.h"

#pragma once

class Player
{
private: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	Player();
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
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
	// 最新のキーボード情報用
	char keys[256] = { 0 };
	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };
	
	int childrenNum = 0;
	//入力
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
	//半径
	const float radius = 20.0f;

	bool playerStop = false;
};