#include "PlayScene.h"
#include "ScoreManager.h"
#include "../Particle.h"
#include "../Sound.h"
#include "../Bloom.h"

PlayScene::PlayScene() {
}

PlayScene::~PlayScene() {
	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	Particle::Ins()->Clear();
}

void PlayScene::Initialize() {
	ScoreManager::GetInstance()->ResetScore();
	backScreen = std::make_unique<BackScreen>();
	player = std::make_unique<Player>();
	backScreen->SetPlayer(player.get());
	cannon_ = std::make_unique<Cannon>();
	cannon_->SetPlayer(player.get());
	cannon_->Initialize();

	// 描画先をmainScreenにする
	SetDrawScreen(Bloom::Ins()->mainScreen);

	bgmHandle = Sound::Ins()->LoadFile("Resources/Sound/D_rhythmaze_119.ogg");
	Sound::Ins()->Play(bgmHandle, true, DX_PLAYTYPE_LOOP);

	startCount =GetNowCount();
}

void PlayScene::Update() {
	if(!StartUpdate()){ return; } 
	if (FinishUpdate()) { return; }
	ScoreManager::GetInstance()->Update();
	playcount = (GetNowCount() - count) / 1000;
	player->playerStop = cannon_->deleteChilFlag;
	player->Update();
	cannon_->Update();
	backScreen->Update(playcount, kPlayCount + cannon_->GetAditional());
	Particle::Ins()->Update();
}

void PlayScene::Draw() {
	// 描画先をmainScreenにする
	SetDrawScreen(Bloom::Ins()->mainScreen);
	ClearDrawScreen();

	backScreen->Draw();
	cannon_->Draw();
	player->Draw();

	Particle::Ins()->Draw();

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// mainScreenの内容を描画する
	DrawGraphF(0, 0, Bloom::Ins()->mainScreen, FALSE);

	// ぼかしたものを描画する
	Bloom::Ins()->UpdateBloomScreen();
	Bloom::Ins()->DrawBloomScreen();

	// スコアを描画
	// スコアにブルームはかけない
	if (isStart) {
		DrawFormatString(600, 360, GetColor(255, 255, 255), "%d", 3 - (GetNowCount() - startCount) / 1000);
	} else {
		DrawFormatString(550, 20, GetColor(255, 255, 255), "%d/%d", playcount, kPlayCount + cannon_->GetAditional());
	}
	ScoreManager::GetInstance()->Draw();
	if (isFinish) {
		ScoreManager::GetInstance()->ResultDraw();
	}
	// 描画先をmainScreenにする
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

bool PlayScene::FinishUpdate() {
	if (playcount >= kPlayCount+cannon_->GetAditional() && !isFinish) {
		playcount = kPlayCount + cannon_->GetAditional();
		ScoreManager::GetInstance()->ScoreSort();
		isFinish = true;
	}
	if(!isFinish){return false;}
	ScoreManager::GetInstance()->ResultUpdate();
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		ChangeNextScene(SceneManager::SceneName::TITLE);
	}
	return true;
}
