#include "BackScreen.h"
#include "ScrollManager.h"
#include <Helper.h>
#include <Easing.h>

BackScreen::BackScreen() {

}
BackScreen::~BackScreen() {

}

void BackScreen::Initialize() {
}

void BackScreen::Update(const int playCount, const int maxCount) {
	const DirectX::XMFLOAT2 scroll = ScrollManager::GetInstance()->GetMove();
	sub.x += scroll.x;
	sub.y += scroll.y;

	if (player_->GetBoost()) { color_ = GetColor(0, 255, 255); }
	else if (player_->GetGear()) { color_ = GetColor(255, 0, 255); }
	else { color_ = GetColor(255, 255, 255); }
	
	if (maxCount-playCount > 5) { return; }
	frame += vel;
	Clamp(frame,0.f, kFrameMax);
	if (frame==0.f) {
		vel = 1.0f;
	}
	if (frame == kFrameMax) {
		vel = -1.0f;
	}
	float fra = frame / kFrameMax;
	int col =(int) Ease(In,Linear, fra,200,0);
	color_ = GetColor(200, col, col);
}

void BackScreen::Draw() {
	const int num = 120;
	const int half = num / 2;
	DirectX::XMFLOAT2 scroll = sub;
	scroll.x = (float)((int)scroll.x % 1280);
	scroll.y = (float)((int)scroll.y % 720);

	for (int i = 0; i < num; i++) {
		DrawLine(0, (50 * (i - half)) - (int)scroll.y, 1280, (50 * (i - half)) - (int)scroll.y, color_, 1);
		DrawLine((50 * (i - half)) - (int)scroll.x, 0, (50 * (i - half)) - (int)scroll.x, 720, color_, 1);
	}
}
