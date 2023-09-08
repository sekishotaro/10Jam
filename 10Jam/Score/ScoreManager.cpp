#include "ScoreManager.h"
#include <DxLib.h>
#include "../Particle.h"

using namespace DirectX;

int ScoreManager::score = 0;

namespace
{
	constexpr XMFLOAT2 scorePosLT = XMFLOAT2(20.f, 20.f);
	constexpr float scoreShadowDiff = 4.f;
	constexpr XMFLOAT2 scoreShadowPosLT = XMFLOAT2(scorePosLT.x - scoreShadowDiff,
												   scorePosLT.y + scoreShadowDiff);
}

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

	DrawStringFToHandle(scoreShadowPosLT.x, scoreShadowPosLT.y, tmp, backColor, font, edgeColor, verticalFlag);
	DrawStringFToHandle(scorePosLT.x, scorePosLT.y, tmp, mainColor, font, edgeColor, verticalFlag);
}

void ScoreManager::AddScore(const int add, unsigned particleNum, const DirectX::XMFLOAT2& particleStartPos) {
	score += add;

	for (unsigned i = 0; i < particleNum; i++) {

		// スコアのスプライトまで飛ぶパーティクル
		Particle::Ins()->AddGrain(30u,
								  XMFLOAT2(particleStartPos.x, particleStartPos.y + float(i) * 10.f),
								  scorePosLT,
								  16.f, 16.f,
								  Particle::ColorRGB{ 255, 128, 128 },
								  Particle::ColorRGB{ 255, 128, 128 },
								  true, 3ui8);

	}
}
