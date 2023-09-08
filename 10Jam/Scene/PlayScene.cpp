#include "PlayScene.h"
#include "ScoreManager.h"
#include "../Particle.h"
#include "../Sound.h"
#include "../Bloom.h"

PlayScene::PlayScene() {
}

PlayScene::~PlayScene() {
	// �`���𗠉�ʂɂ���
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

	// �`����mainScreen�ɂ���
	SetDrawScreen(Bloom::Ins()->mainScreen);

	bgmHandle = Sound::Ins()->LoadFile("Resources/Sound/D_rhythmaze_119.ogg");
	Sound::Ins()->Play(bgmHandle, true, DX_PLAYTYPE_LOOP);
}

void PlayScene::Update() {
	player->Update();
	cannon_->Update();
	accel->Update();
	backScreen->Update();
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		ChangeNextScene(SceneManager::SceneName::TITLE);
	}

	Particle::Ins()->Update();
}

void PlayScene::Draw() {
	backScreen->Draw();
	accel->Draw();
	cannon_->Draw();
	player->Draw();

	Particle::Ins()->Draw();

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// mainScreen�̓��e��`�悷��
	DrawGraphF(0, 0, Bloom::Ins()->mainScreen, FALSE);

	// �ڂ��������̂�`�悷��
	Bloom::Ins()->UpdateBloomScreen();
	Bloom::Ins()->DrawBloomScreen();

	// �X�R�A��`��
	// �X�R�A�Ƀu���[���͂����Ȃ�
	ScoreManager::GetInstance()->Draw();

	// �`����mainScreen�ɂ���
	SetDrawScreen(Bloom::Ins()->mainScreen);
}

void PlayScene::ChangeNextScene(SceneManager::SceneName scene) {
	Sound::Ins()->Stop(bgmHandle);
	SceneManager::GetInstance()->ChangeScene(scene);
}
