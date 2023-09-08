#include "ScoreManager.h"
#include <DxLib.h>
#include "../Particle.h"

using namespace DirectX;

int ScoreManager::score = 0;

ScoreManager* ScoreManager::GetInstance() {
	static ScoreManager instance;
	return &instance;
}

void ScoreManager::Draw() {
	SetFontSize(64);
	DrawFormatString(895, 25, GetColor(100, 100, 100), "SCORE:%d", score);
	DrawFormatString(900, 20, GetColor(255,255,255),"SCORE:%d", score);

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
