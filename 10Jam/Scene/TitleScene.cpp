#include "TitleScene.h"
#include "SceneManager.h"
#include "../Particle.h"
#include "../Bloom.h"

TitleScene::TitleScene() {
}

TitleScene::~TitleScene() {
}

void TitleScene::Initialize() {
	cannon = std::make_unique<Cannon>();
	player = std::make_unique<Player>();
	player->TitleInitialize();
	cannon->SetPlayer(player.get());
	cannon->TitleInitialize();
	backScreen = std::make_unique<BackScreen>();

}

void TitleScene::Update() {
	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
	player->TitleUpdate();
	cannon->TitleUpdate();
	Particle::Ins()->Update();

	player->playerStop = cannon->deleteChilFlag;
	if (keys[KEY_INPUT_RETURN] == 1) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::PLAY);
	}
}

void TitleScene::Draw() {
	// �`����mainScreen�ɂ���
	SetDrawScreen(Bloom::Ins()->mainScreen);
	ClearDrawScreen();

	backScreen->Draw();
	cannon->Draw();
	player->Draw();

	Particle::Ins()->Draw();

	DrawFormatString(600, 300, GetColor(255, 255, 255), "�^�C�g���ł��B�G���^�[�Ńv���C");

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// mainScreen�̓��e��`�悷��
	DrawGraphF(0, 0, Bloom::Ins()->mainScreen, FALSE);

	// �ڂ��������̂�`�悷��
	Bloom::Ins()->UpdateBloomScreen();
	Bloom::Ins()->DrawBloomScreen();


}
