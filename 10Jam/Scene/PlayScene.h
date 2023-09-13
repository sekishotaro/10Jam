#pragma once
#include "BaseScene.h"
#include "../Player.h"
#include "../Children.h"
#include <memory>
#include "Cannon.h"
#include <BackScreen.h>
#include "SceneManager.h"
#include <functional>

class PlayScene : public BaseScene {
public:
	PlayScene();
	~PlayScene();
	/// <summary>
	/// èâä˙âª
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// çXêV
	/// </summary>
	void Update() override;
	/// <summary>
	/// ï`âÊ
	/// </summary>
	void Draw() override;
private:
	void ChangeNextScene(SceneManager::SceneName scene);
	void StartUpdate();
	void MainUpdate();
	void FinishUpdate();
private:
	std::unique_ptr<BackScreen> backScreen = nullptr;
	std::unique_ptr<Player> player = nullptr;
	std::unique_ptr<Cannon> cannon_ = nullptr;

	std::function<void()> updateProc = [] {};
	std::function<void()> drawCountProc = [] {};

	int count = 0;
	int playcount = 0;
	const int kPlayCount = 60;
	int startCount = 0;
	int bgmHandle = 0;
	int backTitleSe = -1;

	static constexpr int startUpdateTimeSecMax = 3;
};

