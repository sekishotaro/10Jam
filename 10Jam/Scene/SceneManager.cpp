#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "../Bloom.h"

SceneManager* SceneManager::GetInstance() {
	static SceneManager instance;
	return &instance;
}

void SceneManager::Initialize(const SceneName sceneName) {
	scene_ = CreateScene(sceneName);
	scene_->Initialize();
	sceneChanger_ = std::make_unique<SceneChanger>();
	sceneChanger_->Initialize();

	// �u���[���p�`���̏�����
	Bloom::Ins()->InitBloomScreen();

	// �o�C���j�A��Ԃŕ`�悷��
	SetDrawMode(DX_DRAWMODE_BILINEAR);
}

void SceneManager::Update() {
	if (CheckChanger()) { return; }
	//�V�[���؂�ւ�
	if (nextScene_) {
		//���V�[���̏I��
		if (scene_) {
			//scene_->Finalize();
			scene_.reset();
		}
		scene_ = std::move(nextScene_);
		scene_->Initialize();
		nextScene_.reset();
		sceneChanger_->SetIsClose();
	}
	scene_->Update();
}

void SceneManager::Draw() {
	scene_->Draw();
	sceneChanger_->Draw();
}

void SceneManager::ChangeScene(const SceneName sceneName) {
	nextScene_ = CreateScene(sceneName);
	sceneChanger_->SetIsStart();
}

std::unique_ptr<BaseScene> SceneManager::CreateScene(const SceneName sceneName) {
	std::unique_ptr<BaseScene> scene = nullptr;
	switch (sceneName) {
	case SceneName::TITLE:
		scene = std::make_unique<TitleScene>();
		break;
	case SceneName::PLAY:
		scene = std::make_unique<PlayScene>();
		break;
	case SceneName::RESULT:
		break;
	default:
		assert(0);
		break;
	}
	return std::move(scene);
}

bool SceneManager::CheckChanger() {
	sceneChanger_->Update();
	return sceneChanger_->GetPhase() != SceneChanger::PHASE::INVISIBLE;
}
