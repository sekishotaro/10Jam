#include "ScoreManager.h"
#include <DxLib.h>
#include "../Particle.h"
#include <Easing.h>
#include <Helper.h>

using namespace DirectX;

int ScoreManager::score = 0;
int ScoreManager::result[3] = {3000,2000,1000};

namespace
{
	constexpr XMFLOAT2 scorePosLT = XMFLOAT2(20.f, 20.f);
}

ScoreManager* ScoreManager::GetInstance() {
	static ScoreManager instance;
	return &instance;
}

void ScoreManager::Update() {
	for (std::unique_ptr<FieldScore>& field : fields) {
		field->Update();
	}
	fields.remove_if([](std::unique_ptr<FieldScore>& field) {
			return field->GetIsFinish();
		});
}

void ScoreManager::Draw() {
	constexpr size_t bufLen = 32u;
	char tmp[bufLen]{};
	sprintf_s(tmp, bufLen, "SCORE: %d", score);

	static unsigned backColor = GetColor(100, 100, 100);
	static unsigned mainColor = GetColor(255, 255, 255);
	static unsigned edgeColor = GetColor(0, 0, 0);

	DrawStringF(scorePosLT.x, scorePosLT.y, tmp, mainColor, edgeColor);

	for (std::unique_ptr<FieldScore>& field : fields) {
		field->Draw();
	}

	if (drawResultFlag) {
		ResultDraw();
	}
}

void ScoreManager::ResultUpdate() {
	frame++;
	float easf = frame / kFrameMax;
	Clamp(easf,0.f,1.0f);
	scroll = Ease(Out, Elastic, easf,-720.f,0.f);
}

void ScoreManager::ResultDraw() {
	static const unsigned black = GetColor(0, 0, 0);
	static const unsigned white = GetColor(255, 255, 255);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBoxAA(0.f, 0.f, 1280.f, 720.f, black, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawFormatStringF(410.f, 100.f + scroll, white, "SCORE: %d", score);
	DrawFormatStringF(480.f, 300.f + scroll, white, "1st: %d", result[0]);
	DrawFormatStringF(480.f, 400.f + scroll, white, "2nd: %d", result[1]);
	DrawFormatStringF(480.f, 500.f + scroll, white, "3rd: %d", result[2]);
	if (frame>= kFrameMax) {
		DrawFormatStringF(430.f, 600.f, white, "PRESS SPACE");
	}
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
	AddFields(particleStartPos, add,GetColor(255,255,100));
	for (unsigned i = 0; i < particleNum; i++) {

		// スコアのスプライトまで飛ぶパーティクル
		Particle::Ins()->AddGrain(45u,
								  XMFLOAT2(particleStartPos.x, particleStartPos.y + float(i) * 10.f),
								  scorePosLT,
								  16.f, 16.f,
								  Particle::ColorRGB{ 255, 0x22, 0x22 },
								  Particle::ColorRGB{ 255, 0x22, 0x22 },
								  true, 3ui8);

	}
}

void ScoreManager::AddFields(XMFLOAT2 pos, int score, int color) {
	std::unique_ptr<FieldScore> scoreF;
	scoreF = std::make_unique<FieldScore>(pos,score,color);
	fields.push_back(std::move(scoreF));
}
