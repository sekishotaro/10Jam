#include "GearSpot.h"
#include <ScrollManager.h>
#include <Easing.h>
#include <Helper.h>
#include "../Particle.h"

GearSpot::GearSpot(XMFLOAT2 pos, Player* player) :
	pos_(pos),
	player_(player) {
	color = GetColor(255, 100, 255);
}

GearSpot::~GearSpot() {
}

void GearSpot::Initialize() {
}

void GearSpot::Update() {
	const bool isCollision = Collision();

	if (isCollision && !player_->GetGear()) {
		player_->SetGear(true);
	}

	{
		constexpr uint8_t interval = 60ui8;
		constexpr float interval_f = float(interval);
		spotframe = ++spotframe % interval;

		constexpr float startR = 70.f;
		constexpr float endR = 85.f;
		spotRadius = Ease(In, Linear, float(spotframe) / interval_f, startR, endR);
	}

	{
		XMFLOAT2 scroll = ScrollManager::GetInstance()->GetMove();
		pos_.x -= scroll.x;
		pos_.y -= scroll.y;
	}
}

void GearSpot::Draw() {
	DrawCircleAA(pos_.x, pos_.y, radius, 64, color, 0, 1);
}

bool GearSpot::Collision() {
	float r = radius + player_->radius;

	float a = pos_.x - player_->GetPos().x;
	float b = pos_.y - player_->GetPos().y;
	float c = sqrtf(a * a + b * b);

	if (c <= r) {
		return true;
	}
	return false;
}
