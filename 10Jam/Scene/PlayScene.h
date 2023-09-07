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
	/// ‰Šú‰»
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// XV
	/// </summary>
	void Update() override;
	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw() override;
private:
	Player* player = nullptr;
	std::unique_ptr<Cannon> cannon_ = nullptr;
	Children* children1 = nullptr;
	Children* children2 = nullptr;
	Children* children3 = nullptr;
	Children* children4 = nullptr;
	Children* children5 = nullptr;
	char keys[256] = { 0 };
};

