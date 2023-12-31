#pragma once
#include"DxLib.h"
#include "DirectXMath.h"
#include "../Player.h"

class BackScreen {
public:
	BackScreen();
	~BackScreen();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update(const int playCount=0,const int maxCount=60);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void SetPlayer(Player* player) { player_ = player; }
private:
	Player* player_=nullptr;
	DirectX::XMFLOAT2 sub = {};
	int color_ = GetColor(200, 200, 200);
	float frame = 0.0f;
	float kFrameMax = 15.f;
	float vel = 1.0f;
};

