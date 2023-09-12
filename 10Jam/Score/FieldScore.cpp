#include "FieldScore.h"
#include <Helper.h>
#include <Easing.h>

FieldScore::FieldScore(XMFLOAT2 pos, int score, int color) {
	pos_ = pos;
	score_ = score;
	color_ = color;
}

FieldScore::~FieldScore() {
}

void FieldScore::Initialize() {


}

void FieldScore::Update() {
	frame++;
	Clamp(frame,0.f, vanish);
	float easeF = frame / vanish;
	alpha = (int)Ease(Out,Cubic, easeF,255,0);
	up = Ease(Out, Cubic, easeF, 0.f, 60.0f);
	if (frame == vanish) {
		isfinish = true;
	}
}

void FieldScore::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	if (score_ >= 100) {
		DrawFormatString(670, 100 - (int)up, GetColor(255,255,255), "+3");
	}
	DrawFormatString((int)pos_.x,(int)pos_.y-(int)up,color_,"+%d",score_);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
