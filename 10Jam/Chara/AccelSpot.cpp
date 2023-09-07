#include"AccelSpot.h"
#include <ScrollManager.h>
#include <Easing.h>
#include <Helper.h>
#include "../Particle.h"

AccelSpot::AccelSpot(XMFLOAT2 pos, Player* player) :
	pos_(pos),
	player_(player) {
}

AccelSpot::~AccelSpot() {
}

void AccelSpot::Initialize() {
}

void AccelSpot::Update() {
	const bool isCollision = Collision();
	const auto nowColor = isCollision ? Particle::ColorRGB{ 100,255,100 } : Particle::ColorRGB{ 100,100,255 };
	color = GetColor(nowColor.red, nowColor.green, nowColor.blue);

	if (isCollision && !player_->GetBoost()) {
		player_->SetBoost(true);
	}

	{
		constexpr uint8_t interval = 60ui8;
		constexpr float interval_f = float(interval);
		spotframe = ++spotframe % interval;

		constexpr float startR = 30.f;
		constexpr float endR = 45.f;
		spotRadius = Ease(In, Linear, float(spotframe) / interval_f, startR, endR);

		if (!spotframe)
		{
			Particle::Ins()->Ripple(pos_, 30u, endR, 1ui8, nowColor, 16ui8, startR, 8.f);
		}
	}


	{
		XMFLOAT2 scroll = ScrollManager::GetInstance()->GetMove();
		pos_.x -= scroll.x;
		pos_.y -= scroll.y;
	}
}

void AccelSpot::Draw() {
	DrawCircleAA(pos_.x, pos_.y, radius, 64, color, 0, 1);
}

bool AccelSpot::Collision() {
	float r = radius + player_->radius;

	float a = pos_.x - player_->GetPos().x;
	float b = pos_.y - player_->GetPos().y;
	float c = sqrtf(a * a + b * b);

	if (c <= r) {
		return true;
	}
	return false;
}
