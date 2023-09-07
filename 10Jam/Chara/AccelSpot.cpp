#include"AccelSpot.h"
#include <ScrollManager.h>
#include <Easing.h>
#include <Helper.h>


AccelSpot::AccelSpot(XMFLOAT2 pos, Player* player) {
	pos_ = pos;
	player_ = player;
}

AccelSpot::~AccelSpot() {
}

void AccelSpot::Initialize() {


}

void AccelSpot::Update() {
	if (Collision()) {
		if (!player_->GetBoost()) {
			color= GetColor(100, 255, 100);
			player_->SetBoost(true);
		}
	} else {
		color = GetColor(100, 100, 255);
	}
	{
		spotframe+=1.0f;
		Clamp(spotframe,0.f,30.f);
		spotRadius = Ease(In,Linear, spotframe/30.f,30.f,45.f);
		if (spotframe==30.f) {
			spotframe = 0.0f;
		}
	}


	{
		XMFLOAT2 scroll = ScrollManager::GetInstance()->GetMove();
		pos_.x -= scroll.x;
		pos_.y -= scroll.y;
	}
}

void AccelSpot::Draw() {
	DrawCircleAA(pos_.x, pos_.y, spotRadius, 64, color, 0, 1);
	DrawCircleAA(pos_.x,pos_.y, radius,64, color,0,1);

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
