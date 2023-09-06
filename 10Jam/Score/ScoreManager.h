#pragma once
class ScoreManager {
public:

	static ScoreManager* GetInstance();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();


	/// <summary>
	/// �X�R�A����
	/// </summary>
	/// <param name="add"></param>
	void AddScore(const int add) { score += add; }
	/// <summary>
	/// �X�R�A���Z�b�g
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

