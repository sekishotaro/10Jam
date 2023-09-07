#pragma once
#include "BaseScene.h"
#include "../Player.h"
#include "../Children.h"
#include <memory>
#include "Cannon.h"

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
	Player* player = nullptr;
	std::unique_ptr<Cannon> cannon_ = nullptr;
	char keys[256] = { 0 };
};

