#pragma once

#include <DirectXMath.h>

class ScoreManager {
public:

	static ScoreManager* GetInstance();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();


	void ResultUpdate();

	/// <summary>
	/// �`��
	/// </summary>
	void ResultDraw();

	void ScoreSort();

	/// <summary>
	/// �X�R�A����
	/// </summary>
	/// <param name="add"></param>
	void AddScore(const int add, unsigned particleNum = 1u, const DirectX::XMFLOAT2& particleStartPos = { 640.f, 360.f });
	/// <summary>
	/// �X�R�A���Z�b�g
	/// </summary>
	void ResetScore() { score = 0; frame = 0.f; }

	static int GetScore() { return score; }

private:
	static int score;
	float frame = 0.0f;
	float kFrameMax = 60.0f;
	float scroll = -720;
	static int result[3];
private:
	~ScoreManager() = default;
	ScoreManager() = default;
	ScoreManager(const ScoreManager&) = delete;
	void operator =(const ScoreManager&) = delete;
};

