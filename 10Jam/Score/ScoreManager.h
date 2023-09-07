#pragma once
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
	void AddScore(const int add) { score += add; }
	/// <summary>
	/// スコアリセット
	/// </summary>
	void ResetScore() { score = 0; }
private:
	static int score;
private:
	~ScoreManager() = default;
	ScoreManager() = default;
	ScoreManager(const ScoreManager&) = delete;
	void operator =(const ScoreManager&) = delete;
};

