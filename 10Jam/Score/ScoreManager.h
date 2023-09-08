#pragma once

#include <DirectXMath.h>

class ScoreManager {
public:

	static ScoreManager* GetInstance();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	/// <summary>
	/// スコア増加
	/// </summary>
	/// <param name="add"></param>
	void AddScore(const int add, unsigned particleNum = 1u, const DirectX::XMFLOAT2& particleStartPos = { 640.f, 360.f });
	/// <summary>
	/// スコアリセット
	/// </summary>
	void ResetScore() { score = 0; }

	static int GetScore() { return score; }

private:
	static int score;
	int font = -1;

private:
	ScoreManager();
	~ScoreManager() = default;
	ScoreManager(const ScoreManager&) = delete;
	void operator =(const ScoreManager&) = delete;
};

