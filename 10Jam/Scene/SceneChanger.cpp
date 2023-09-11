#include "SceneChanger.h"
#include "DxLib.h"
#include "Easing.h"

namespace
{
	inline float StartEase(float t)
	{
		return Ease(In, Quad, t, 0.f, 600.0f);
	}

	inline float EndEase(float t)
	{
		return Ease(In, Quad, t, 630.f, 0.f);
	}
}

void SceneChanger::UpdateStart()
{
	UpdateFrame();
	if (frame_ == 0u)
	{
		EndSceneChange();
	} else
	{
		r = StartEase(float(frame_) / float(kFrameMax));
	}
}

void SceneChanger::UpdateClose()
{
	UpdateFrame();
	if (frame_ == 0u)
	{
		EndSceneChange();
	} else
	{
		r = EndEase(float(frame_) / float(kFrameMax));
	}
}

SceneChanger::SceneChanger() {
}


SceneChanger::~SceneChanger() {
}

void SceneChanger::Initialize() {
	frame_ = 0;
	r = 0.0f;
}

void SceneChanger::Update() {
	updateProc();
}

void SceneChanger::Draw() {
	if (phase == PHASE::INVISIBLE) { return; }

	DrawCircleAA(640.f, 360.f, r, 128, GetColor(255, 255, 255), TRUE);
}
