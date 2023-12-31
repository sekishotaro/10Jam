#pragma once
#include"../Player.h"
#include"DirectXMath.h"
#include"DxLib.h"

class AccelSpot {
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;

	int accelSe = -1;

public:
	AccelSpot(XMFLOAT2 pos,Player* player);
	~AccelSpot();
	/// <summary>
/// 初期化
/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool Collision();
private:
	XMFLOAT2 pos_ = {};
	float radius = 30.f;
	float spotRadius = 30.0f;
	uint8_t spotframe = 0ui8;
	int color = GetColor(100, 100, 255);
	Player* player_ = nullptr;
};
