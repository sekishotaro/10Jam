#include "TitleScene.h"
#include "SceneManager.h"
#include "../Particle.h"
#include "../Children.h"
#include "../Bloom.h"
#include "../Sound.h"
#include <ScrollManager.h>

TitleScene::TitleScene() {
	ScrollManager::GetInstance()->Reset();

	startSe = Sound::Ins()->LoadFile("Resources/Sound/����.ogg");
	assert(startSe != -1);
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
	ruby = LoadGraph("Resources/ruby.png");
	ido = LoadGraph("Resources/�y��z.png");
}

void TitleScene::Update() {
	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
	player->TitleUpdate();
	cannon->TitleUpdate();
	Particle::Ins()->Update();

	player->playerStop = cannon->deleteChilFlag;
	if (keys[KEY_INPUT_RETURN] == 1) {
		// �p�[�e�B�N��������
		Particle::Ins()->Clear();
		Children::End();
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::PLAY);
		Sound::Ins()->Play(startSe, true, DX_PLAYTYPE_BACK);
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
	//DrawFormatString(450, 630, GetColor(255, 255, 255), "PRESS ENTER");
	//DrawFormatString(600, 300, GetColor(255, 255, 255), "%.0f,%.0f,",player->GetPos().x, player->GetPos().y);

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// mainScreen�̓��e��`�悷��
	DrawGraphF(0, 0, Bloom::Ins()->mainScreen, FALSE);

	// �ڂ��������̂�`�悷��
	Bloom::Ins()->UpdateBloomScreen();
	Bloom::Ins()->DrawBloomScreen();

	DrawRotaGraph(640, 60, 0.5f, 0, ruby, true, false);
	DrawRotaGraph(640, 360, 1.0f, 0, ido, true, false);
	DrawFormatString(450, 630, GetColor(255, 255, 255), "PRESS ENTER");
}
