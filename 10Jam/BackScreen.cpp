#include "BackScreen.h"
#include "ScrollManager.h"

BackScreen::BackScreen() {

}
BackScreen::~BackScreen() {

}

void BackScreen::Initialize() {
}

void BackScreen::Update() {
	DirectX::XMFLOAT2 scroll = ScrollManager::GetInstance()->GetMove();
	sub.x+= scroll.x;
	sub.y+= scroll.y;
}

void BackScreen::Draw() {
	for (int i = 0; i < 60;i++) {
		DrawLine(0,(50*(i-30))- (int)sub.y, 1280, (50 * (i - 30)) - (int)sub.y,GetColor(200,200,200),1);
	}
	for (int i = 0; i < 80;i++) {
		DrawLine((50 * (i - 30)) - (int)sub.x, 0, (50 * (i - 30)) - (int)sub.x, 720, GetColor(200, 200, 200), 1);
	}

}
