#pragma once
#include <DxLib.h>
#include <DirectXmath.h>

class FieldScore {
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
public:
	FieldScore(XMFLOAT2 pos, int score, int color);
	~FieldScore();
	/// <summary>
	/// èâä˙âª
	/// </summary>
	void Initialize();
	/// <summary>
	/// çXêV
	/// </summary>
	void Update();
	/// <summary>
	/// ï`âÊ
	/// </summary>
	void Draw();

	bool GetIsFinish() { return isfinish; }
private:
	bool isfinish = false;
	float up = 0.0f;
	int alpha = 255;
	float frame = 0.f;
	const float vanish = 60.0f;
	XMFLOAT2 pos_ = {};
	int score_ = 0;
	int color_ = GetColor(255, 255, 100);
};

