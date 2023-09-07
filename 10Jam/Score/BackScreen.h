#pragma once
#include"DxLib.h"
#include "DirectXMath.h"

class BackScreen {
public:
	BackScreen();
	~BackScreen();
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize();
	/// <summary>
	/// XV
	/// </summary>
	void Update();
	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw();
private:
	DirectX::XMFLOAT2 sub = {};

};

