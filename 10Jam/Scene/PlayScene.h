#pragma once
#include "BaseScene.h"
#include "../Player.h"
#include "../Children.h"

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
	Children* children1 = nullptr;
	char keys[256] = { 0 };




};

