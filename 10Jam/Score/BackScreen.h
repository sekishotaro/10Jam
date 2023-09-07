#pragma once
#include"DxLib.h"
#include "DirectXMath.h"

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
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
private:
	DirectX::XMFLOAT2 sub = {};

};

