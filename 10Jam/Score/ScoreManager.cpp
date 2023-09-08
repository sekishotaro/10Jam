#include "ScoreManager.h"
#include <DxLib.h>
#include "../Particle.h"

using namespace DirectX;

int ScoreManager::score = 0;

ScoreManager* ScoreManager::GetInstance() {
	static ScoreManager instance;
	return &instance;
}

ScoreManager::ScoreManager() {
	constexpr int edgeSize = 2;
	font = LoadFontDataToHandle("Resources/FZゴンタかな_32.dft", edgeSize);
}

void ScoreManager::Draw() {

	constexpr size_t bufLen = 32u;
	char tmp[bufLen]{};
	sprintf_s(tmp, bufLen, "スコア: %d", score);

	static unsigned backColor = GetColor(100, 100, 100);
	static unsigned mainColor = GetColor(255, 255, 255);
	static unsigned edgeColor = GetColor(0, 0, 0);

	constexpr int verticalFlag = FALSE;

	DrawStringFToHandle(16.f, 24.f, tmp, backColor, font, edgeColor, verticalFlag);
	DrawStringFToHandle(20.f, 20.f, tmp, mainColor, font, edgeColor, verticalFlag);
}

void ScoreManager::AddScore(const int add, unsigned particleNum, const DirectX::XMFLOAT2& particleStartPos) {
	score += add;

	for (unsigned i = 0; i < particleNum; i++) {

		// スコアのスプライトまで飛ぶパーティクル
		Particle::Ins()->AddGrain(30u,
								  XMFLOAT2(particleStartPos.x, particleStartPos.y + float(i) * 10.f),
								  XMFLOAT2(1000.f, 75.f),
								  16.f, 16.f,
								  Particle::ColorRGB{ 255, 128, 128 },
								  Particle::ColorRGB{ 255, 128, 128 },
								  true, 3ui8);

	}
}
