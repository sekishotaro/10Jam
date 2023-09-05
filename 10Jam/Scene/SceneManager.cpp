#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"



SceneManager* SceneManager::GetInstance() {
	static SceneManager instance;
	return &instance;
}


void SceneManager::Initialize(const SceneName sceneName) {
	scene_ = CreateScene(sceneName);
	scene_->Initialize();
}

void SceneManager::Update() {
	//シーン切り替え
	if (nextScene_) {
		//旧シーンの終了
		if (scene_) {
			//scene_->Finalize();
			scene_.reset();
		}
		scene_ = std::move(nextScene_);
		nextScene_.reset();
		scene_->Initialize();
	}
	scene_->Update();
}

void SceneManager::Draw() {
	scene_->Draw();
}

void SceneManager::ChangeScene(const SceneName sceneName) {
	nextScene_ = CreateScene(sceneName);
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
