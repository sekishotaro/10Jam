#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene() {
}

TitleScene::~TitleScene() {
}

void TitleScene::Initialize() {
}

void TitleScene::Update() {
	backScreen = std::make_unique<BackScreen>();
	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
	if (keys[KEY_INPUT_RETURN] == 1) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::PLAY);
	}
}

void TitleScene::Draw() {

	backScreen->Draw();

	DrawFormatString(600,300,GetColor(255,255,255),"�^�C�g���ł��B�G���^�[�Ńv���C");
}
