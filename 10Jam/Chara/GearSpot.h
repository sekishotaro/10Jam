#pragma once
#include"../Player.h"
#include"DirectXMath.h"
#include"DxLib.h"

class GearSpot {
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;

	int gearSe = -1;

public:
	GearSpot(XMFLOAT2 pos, Player* player);
	~GearSpot();
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
	float radius = 70.f;
	float spotRadius = 70.f;
	uint8_t spotframe = 0ui8;
	int color = GetColor(100, 255, 100);
	Player* player_ = nullptr;
};
