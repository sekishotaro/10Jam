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

	/// <summary>
	/// 削除確認フラグ
	/// </summary>
	static bool DleteCheck();
	/// <summary>
	/// 追跡子供の番号リセット
	/// </summary>
	static void TrackChilHitNumReset();

	/// <summary>
	/// 自分が消される子供かを確認する
	/// </summary>
	/// <returns></returns>
	void DleteChildrenCheck();

	void TrackChilOrganize();

	static const int GetHitNum() { return trackChilHitNum; }
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
	/// 自由な子との当たり判定処理
	/// </summary>
	void FreeChildrenColProcess();
	/// <summary>
	/// 追跡移動
	/// </summary>
	void TrackMove();
	/// <summary>
	/// 追跡している子との当たり判定処理
	/// </summary>
	void TrackChildrenColProcess();

	void ScrollMove();

	bool Spawn();


private:
	Player* player_ = nullptr;
	
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
	//追跡移動間隔
	int trackDis = 15;
	//当たり判定を受け付けない最低拘束番号
	int unColRestrainTh = 5;
	XMFLOAT2 moveVec[10] = {};
	std::vector<XMFLOAT2> restrainMoveVec;

	//追跡最後尾確認フラグ
	bool tailFlag = false;

	//追跡子供と自機の当たった番号
	static int trackChilHitNum;
public:
	//削除確認フラグ
	bool deleteFlag = false;
	//拘束状態確認
	bool freeFlag = true;
};


