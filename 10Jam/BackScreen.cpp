#include "BackScreen.h"
#include "ScrollManager.h"
#include <Helper.h>

BackScreen::BackScreen() {

}
BackScreen::~BackScreen() {

}

void BackScreen::Initialize() {
}

void BackScreen::Update() {
	DirectX::XMFLOAT2 scroll = ScrollManager::GetInstance()->GetMove();
	sub.x += scroll.x;
	sub.y += scroll.y;
}

void BackScreen::Draw() {
	const int num = 120;
	const int half = num / 2;
	DirectX::XMFLOAT2 scroll = sub;
	scroll.x = (int)scroll.x % 1280;
	scroll.y = (int)scroll.y % 720;

	for (int i = 0; i < num; i++) {
		DrawLine(0, (50 * (i - half)) - (int)scroll.y, 1280, (50 * (i - half)) - (int)scroll.y, GetColor(200, 200, 200), 1);
		DrawLine((50 * (i - half)) - (int)scroll.x, 0, (50 * (i - half)) - (int)scroll.x, 720, GetColor(200, 200, 200), 1);
	}
}
