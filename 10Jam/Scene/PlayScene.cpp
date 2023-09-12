#include "PlayScene.h"
#include "ScoreManager.h"
#include "../Particle.h"
#include "../Sound.h"
#include "../Bloom.h"

PlayScene::PlayScene() {
	updateProc = std::bind(&PlayScene::StartUpdate, this);
	drawCountProc = [&] { DrawFormatString(600, 360, GetColor(255, 255, 255), "%d", startUpdateTimeSecMax - playcount); };
}

PlayScene::~PlayScene() {
}

void PlayScene::Initialize() {
	ScoreManager::GetInstance()->ResetScore();
	backScreen = std::make_unique<BackScreen>();
	player = std::make_unique<Player>();
	backScreen->SetPlayer(player.get());
	cannon_ = std::make_unique<Cannon>();
	cannon_->SetPlayer(player.get());
	cannon_->Initialize();

	bgmHandle = Sound::Ins()->LoadFile("Resources/Sound/D_rhythmaze_119.ogg");

	startCount = GetNowCount();
}

void PlayScene::Update() {
	updateProc();
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

	drawCountProc();

	// スコアを描画
	// スコアにブルームはかけない
	ScoreManager::GetInstance()->Draw();
}

void PlayScene::ChangeNextScene(SceneManager::SceneName scene) {
	// BGMが鳴っていたら止める
	Sound::Ins()->Stop(bgmHandle);
	// パーティクルを消す
	Particle::Ins()->Clear();
	// スコアは非表示に戻す
	ScoreManager::GetInstance()->drawResultFlag = false;
	// シーンを切り替える
	SceneManager::GetInstance()->ChangeScene(scene);
}

void PlayScene::StartUpdate() {
	playcount = (GetNowCount() - startCount) / 1000;
	if (playcount < startUpdateTimeSecMax) { return; }
	
	playcount = 0;
	// 更新処理を切り替える
	updateProc = std::bind(&PlayScene::MainUpdate, this);
	// BGMを鳴らす
	Sound::Ins()->Play(bgmHandle, true, DX_PLAYTYPE_LOOP);
	// カウント表示関数を切り替える
	drawCountProc = [&]
		{
			static const unsigned color = GetColor(255, 255, 255);
			DrawFormatString(550, 20, color, "TIME: %d", kPlayCount - playcount);
		};

	// 現在の時間を記録
	count = GetNowCount();
}

void PlayScene::MainUpdate() {
	playcount = (GetNowCount() - count) / 1000;
	player->playerStop = cannon_->deleteChilFlag;
	player->Update();
	cannon_->Update();
	backScreen->Update(playcount);
	Particle::Ins()->Update();

	// カウントが終わったら終了
	if (playcount >= 60) {
		playcount = 60;
		ScoreManager::GetInstance()->ScoreSort();
		updateProc = std::bind(&PlayScene::FinishUpdate, this);
		drawCountProc = [] {};
		// BGMを止める
		Sound::Ins()->Stop(bgmHandle);
		// スコアを表示する
		ScoreManager::GetInstance()->drawResultFlag = true;
	}
}

void PlayScene::FinishUpdate() {
	ScoreManager::GetInstance()->ResultUpdate();
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		ChangeNextScene(SceneManager::SceneName::TITLE);
	}
}
