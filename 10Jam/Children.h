#include "DxLib.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include "Player.h"
#include <vector>
#pragma once

class Children
{
private: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	Children(XMFLOAT2 pos,Player* player);
	~Children();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private:
	/// <summary>
	/// 自機と当たり判定
	/// </summary>
	/// <param name="PlayerPos"></param>
	bool Collision();
	/// <summary>
	/// プレイヤー追従処理
	/// </summary>
	void Follow2Player();
	/// <summary>
	/// 動くか止まるか
	/// </summary>
	void MountMove();
	/// <summary>
	/// 自動移動
	/// </summary>
	void MoveFree();
	void TracColProcess();
	
	/// <summary>
	/// 追跡移動
	/// </summary>
	void TrackMove();

	void ScrollMove();

	bool Spawn();
private:
	Player* player_ = nullptr;
	//拘束状態確認
	bool freeFlag = true;
	//動き関連
	bool isMove = false;
	float vel = 0.0f;
	float dir = 1.0f;
	//
	bool isSpawn = true;
	float spawnFrame = 0.0f;
	float kSpawnFrameMax = 15.0f;
	//位置
	XMFLOAT2 pos = { 600.0f, 410.0f };
	XMFLOAT2 move = { 0.0f, 0.0f };
	//半径
	float radius = 8.0f;
	//拘束番号
	int restraintTh = 0;

	XMFLOAT2 moveVec[10] = {};
	std::vector<XMFLOAT2> restrainMoveVec;
};


