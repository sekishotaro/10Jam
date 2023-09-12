#pragma once
#include "BaseScene.h"
#include "../Player.h"
#include "../Children.h"
#include <memory>
#include "Cannon.h"
#include <BackScreen.h>
#include "SceneManager.h"

class PlayScene : public BaseScene {
public:
	PlayScene();
	~PlayScene();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
private:
	void ChangeNextScene(SceneManager::SceneName scene);
	bool StartUpdate();
	bool FinishUpdate();
private:
	std::unique_ptr<BackScreen> backScreen = nullptr;
	std::unique_ptr<Player> player = nullptr;
	std::unique_ptr<Cannon> cannon_ = nullptr;

	bool isFinish = false;

	int count = 0;
	int playcount = 0;
	int kPlayCount = 60;
	bool isStart = true;
	int startCount = 0;
	int bgmHandle=0;
};

