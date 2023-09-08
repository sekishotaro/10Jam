#pragma once
#include"../Player.h"
#include"DirectXMath.h"
#include"DxLib.h"

class GearSpot {
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
public:
	GearSpot(XMFLOAT2 pos, Player* player);
	~GearSpot();
	/// <summary>
/// èâä˙âª
/// </summary>
	void Initialize();
	/// <summary>
	/// çXêV
	/// </summary>
	void Update();
	/// <summary>
	/// ï`âÊ
	/// </summary>
	void Draw();

	bool Collision();
private:
	XMFLOAT2 pos_ = {};
	float radius = 60.f;
	float spotRadius = 60.0f;
	uint8_t spotframe = 0ui8;
	int color = GetColor(100, 100, 255);
	Player* player_ = nullptr;
};
