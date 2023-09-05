#include "SceneChanger.h"
#include "DxLib.h"
#include "Easing.h"

SceneChanger::SceneChanger() {
}


SceneChanger::~SceneChanger() {
}

void SceneChanger::Initialize() {
	frame_ = 0.f, kFrameMax = 45.f, frameNow_ = 0.0f;
	r = 0.f;
	isStart = false;
	isClose = false;

}

void SceneChanger::Update() {
	if (isStart) {
		frame_ += 1.0f;
		frameNow_ = frame_ / kFrameMax;
		if (frameNow_ <= 1.1f) {
			r = Ease(In, Quad, frameNow_, 0.f, 600.0f);
		} else {
			frame_ = 0.0f;
			frameNow_ = 0.0f;
			isStart = false;
			return;
		}
	}
	if (isClose) {
		frame_ += 1.0f;
		frameNow_ = frame_ / kFrameMax;
		if (frameNow_ <= 1.0f) {
			r = Ease(In, Quad, frameNow_, 600.f, 0.0f);
		} else {
			frame_ = 0.0f;
			frameNow_ = 0.0f;
			isClose = false;
		}
	}
}

void SceneChanger::Draw() {
	DrawCircleAA(640.f, 360.f, r, 128, GetColor(255, 255, 255), TRUE);
}
