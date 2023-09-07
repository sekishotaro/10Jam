#pragma once
#include "BaseScene.h"
#include "../Player.h"
#include "../Children.h"
#include <memory>
#include "Cannon.h"
#include <AccelSpot.h>
#include <BackScreen.h>

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
	std::unique_ptr<BackScreen> backScreen = nullptr;
	std::unique_ptr<Player> player = nullptr;
	std::unique_ptr<Cannon> cannon_ = nullptr;
	std::unique_ptr<AccelSpot> accel = nullptr;
};

