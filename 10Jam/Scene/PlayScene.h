#pragma once
#include "BaseScene.h"
#include "../Player.h"
#include "../Children.h"
#include <memory>
#include "Cannon.h"
#include <AccelSpot.h>
#include <BackScreen.h>
#include "GearSpot.h"
#include "SceneManager.h"

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
	bool StartUpdate();
private:
	std::unique_ptr<BackScreen> backScreen = nullptr;
	std::unique_ptr<Player> player = nullptr;
	std::unique_ptr<Cannon> cannon_ = nullptr;
	std::unique_ptr<AccelSpot> accel = nullptr;
	std::unique_ptr<GearSpot> gear = nullptr;

	int count = 0;
	bool isStart = true;
	int startCount = 0;
	int bgmHandle;
};

