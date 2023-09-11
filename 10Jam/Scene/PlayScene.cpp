#include "PlayScene.h"
#include "ScoreManager.h"
#include "../Particle.h"
#include "../Sound.h"
#include "../Bloom.h"

PlayScene::PlayScene() {
}

PlayScene::~PlayScene() {
	// •`‰ææ‚ð— ‰æ–Ê‚É‚·‚é
	SetDrawScreen(DX_SCREEN_BACK);
}

void PlayScene::Initialize() {
	ScoreManager::GetInstance()->ResetScore();
	backScreen = std::make_unique<BackScreen>();
	player = std::make_unique<Player>();
	cannon_ = std::make_unique<Cannon>();
	cannon_->SetPlayer(player.get());
	cannon_->Initialize();
	accel = std::make_unique<AccelSpot>(DirectX::XMFLOAT2{ 600,200 }, player.get());
	accel->Initialize();

	// •`‰ææ‚ðmainScreen‚É‚·‚é
	SetDrawScreen(Bloom::Ins()->mainScreen);

	bgmHandle = Sound::Ins()->LoadFile("Resources/Sound/D_rhythmaze_119.ogg");
	Sound::Ins()->Play(bgmHandle, true, DX_PLAYTYPE_LOOP);
	gear = std::make_unique<GearSpot>(DirectX::XMFLOAT2{ 1000,500 }, player.get());
	gear->Initialize();
	startCount =GetNowCount();
}

void PlayScene::Update() {
	if(!StartUpdate()){ return; } 
	player->playerStop = cannon_->deleteChilFlag;
	player->Update();
	cannon_->Update();
	accel->Update();
	gear->Update();

	backScreen->Update();
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		ChangeNextScene(SceneManager::SceneName::TITLE);
	}

	Particle::Ins()->Update();
}

void PlayScene::Draw() {
	backScreen->Draw();
	accel->Draw();
	gear->Draw();
	cannon_->Draw();
	player->Draw();

	Particle::Ins()->Draw();

	// •`‰ææ‚ð— ‰æ–Ê‚É‚·‚é
	SetDrawScreen(DX_SCREEN_BACK);

	// mainScreen‚Ì“à—e‚ð•`‰æ‚·‚é
	DrawGraphF(0, 0, Bloom::Ins()->mainScreen, FALSE);

	// ‚Ú‚©‚µ‚½‚à‚Ì‚ð•`‰æ‚·‚é
	Bloom::Ins()->UpdateBloomScreen();
	Bloom::Ins()->DrawBloomScreen();

	// ƒXƒRƒA‚ð•`‰æ
	// ƒXƒRƒA‚Éƒuƒ‹[ƒ€‚Í‚©‚¯‚È‚¢
	if (isStart) {
		DrawFormatString(600, 360, GetColor(255, 255, 255), "%d", 3 - (GetNowCount() - startCount) / 1000);
	} else {
		DrawFormatString(640, 20, GetColor(255, 255, 255), "%d", (GetNowCount() - count) / 1000);
	}
	ScoreManager::GetInstance()->Draw();

	// •`‰ææ‚ðmainScreen‚É‚·‚é
	SetDrawScreen(Bloom::Ins()->mainScreen);
}

void PlayScene::ChangeNextScene(SceneManager::SceneName scene) {
	Sound::Ins()->Stop(bgmHandle);
	SceneManager::GetInstance()->ChangeScene(scene);
}

bool PlayScene::StartUpdate() {
	if (!isStart) {
		return true;
	}
	if (((GetNowCount() - startCount) / 1000) == 4) {
		isStart = false;
		count = GetNowCount();
		return true;
	} else {
		return false;
	}
}
