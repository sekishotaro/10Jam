#include "PlayScene.h"

PlayScene::PlayScene() {
}

PlayScene::~PlayScene() {
	delete player;
	delete children1;
}

void PlayScene::Initialize() {
	player = new Player();
	children1 = new Children(255.0f,255.0f);

}

void PlayScene::Update() {
	player->Update();
	//children1->Update();

}

void PlayScene::Draw() {
	player->Draw();
	children1->Draw();

}
