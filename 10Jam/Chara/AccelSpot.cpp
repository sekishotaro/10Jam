#include"AccelSpot.h"
#include <ScrollManager.h>


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
			player_->SetBoost(true);
		}
	}
	XMFLOAT2 scroll = ScrollManager::GetInstance()->GetMove();
	pos_.x -= scroll.x;
	pos_.y -= scroll.y;
}

void AccelSpot::Draw() {
	DrawCircleAA(pos_.x,pos_.y, radius,64,GetColor(100,100,255),0,1);
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
