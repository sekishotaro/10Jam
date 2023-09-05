#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"



SceneManager::SceneManager(const SceneName sceneName) {
	scene_ = CreateScene(sceneName);

}

SceneManager::~SceneManager() {
}

void SceneManager::Initialize() {
	scene_->Initialize();
}

void SceneManager::Update() {
	scene_->Update();
}

void SceneManager::Draw() {
	scene_->Draw();
}

BaseScene* SceneManager::CreateScene(const SceneName sceneName) {
	BaseScene* scene = nullptr;
	switch (sceneName) {
	case SceneName::TITLE:
		scene = new TitleScene();
		break;
	case SceneName::PLAY:
		scene = new PlayScene();
		break;
	case SceneName::RESULT:
		break;
	default:
		assert(0);
		break;
	}
	return scene;
}
