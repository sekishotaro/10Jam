#pragma once
class SceneChanger {
public:
	/// <summary>
	/// インストラクタ
	/// </summary>
	SceneChanger();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneChanger();

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

	/// <summary>
	/// ゲッター&setter
	/// </summary>
	void SetIsStart() { isStart = true; isVisible = true; }
	bool GetIsStart() { return isStart; }

	void SetIsClose(const bool& flag) { isClose = true; }
	bool GetIsClose() { return isClose; }


private:
	float frame_ = 0.f, kFrameMax = 45.f, frameNow_ = 0.0f;
	float r = 0.f;
	bool isStart = true;
	bool isClose = false;
	bool isVisible = false;
};

