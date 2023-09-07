#pragma once
#include"../Player.h"
#include"DirectXMath.h"
#include"DxLib.h"

class AccelSpot {
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
public:
	AccelSpot(XMFLOAT2 pos,Player* player);
	~AccelSpot();
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
	float radius = 30.f;
	float spotRadius = 30.0f;
	float spotframe = 0.0f;
	int color = GetColor(100, 100, 255);
	Player* player_ = nullptr;
};
