#include "DxLib.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include "Player.h"
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
	void Update(Player& player);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private:
	/// <summary>
	/// 自機と当たり判定
	/// </summary>
	/// <param name="PlayerPos"></param>
	void Collision(Player& player);



private:
	//拘束状態確認
	bool freeFlag = true;
	//位置
	XMFLOAT2 pos = { 600.0f, 410.0f };
	//半径
	const float radius = 8.0f;
	//拘束番号
	int restraintTh = 0;

	XMFLOAT2 moveVec[10] = {};
};


