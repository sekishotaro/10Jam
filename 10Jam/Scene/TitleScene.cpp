#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene() {
}

TitleScene::~TitleScene() {
}

void TitleScene::Initialize() {
}

void TitleScene::Update() {
	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
	if (keys[KEY_INPUT_RETURN] == true) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::PLAY);
	}
}

void TitleScene::Draw() {
}
