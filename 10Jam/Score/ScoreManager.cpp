#include "ScoreManager.h"
#include <DxLib.h>
#include "../Particle.h"
#include <Easing.h>
#include <Helper.h>

using namespace DirectX;

int ScoreManager::score = 0;
int ScoreManager::result[3] = {3000,2000,1000};

ScoreManager* ScoreManager::GetInstance() {
	static ScoreManager instance;
	return &instance;
}

void ScoreManager::Draw() {
	SetFontSize(64);
	DrawFormatString(895, 25, GetColor(100, 100, 100), "SCORE:%d", score);
	DrawFormatString(900, 20, GetColor(255,255,255),"SCORE:%d", score);

}

void ScoreManager::ResultUpdate() {
	frame++;
	float easf = frame / kFrameMax;
	Clamp(easf,0.f,1.0f);
	scroll = Ease(Out, Elastic, easf,-720.f,0.f);
}

void ScoreManager::ResultDraw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0,0,1280,720,GetColor(0,0,0),true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawFormatString(410, 100+scroll, GetColor(255, 255, 255), "SCORE:%d", score);
	DrawFormatString(480, 300+scroll, GetColor(255, 255, 255), "1st:%d", result[0]);
	DrawFormatString(480, 400+scroll, GetColor(255, 255, 255), "2nd:%d", result[1]);
	DrawFormatString(480, 500+scroll, GetColor(255, 255, 255), "3rd:%d", result[2]);

}

void ScoreManager::ScoreSort() {
	for (int i = 0; i < 3;i++) {
		if (result[i] <= score) {
			result[i] = score;
			return;
		}
	}
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
