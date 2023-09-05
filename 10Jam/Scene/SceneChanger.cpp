#include "SceneChanger.h"
#include "DxLib.h"
#include "Easing.h"

SceneChanger::SceneChanger() {
}


SceneChanger::~SceneChanger() {
}

void SceneChanger::Initialize() {

}

void SceneChanger::Update() {
	if (isStart) {
		frame_+=1.0f;
		if (frameNow_<= 1.0f) {
			frameNow_ = frame_ / kFrameMax;
		} else {

		}
		r=Ease(In,Quad, frameNow_,0.f,600.0f);
	}
}

void SceneChanger::Draw() {

	//DrawCircleAA(640.f, 360.f, r, 128, GetColor(255,255,255), TRUE);
}
