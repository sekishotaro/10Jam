#include "DxLib.h"
#include <d3d12.h>
#include <DirectXMath.h>
#pragma once

class Children
{
private: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	Children(float x, float y);
	~Children();

	/// <summary>
	/// 更新
	/// </summary>
	void Update(XMFLOAT2 &PlayerPos);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

	bool FreeFlag = false;
	XMFLOAT2 pos = { 600.0f, 410.0f };
};

