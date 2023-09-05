#include <Windows.h>
#include <d3d12.h>
#include <DirectXMath.h>
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

private:

	XMFLOAT2 pos = { 600.0f, 410.0f };
	XMFLOAT2 moveVec = { 0.0f, 0.0f };
	// 最新のキーボード情報用
	char keys[256] = { 0 };
	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };
};

