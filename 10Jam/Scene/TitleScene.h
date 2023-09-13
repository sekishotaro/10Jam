#pragma once
#include "BaseScene.h"
#include <memory>
#include <BackScreen.h>
#include <Cannon.h>


class TitleScene : public BaseScene {
public:
	TitleScene();
	~TitleScene();
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
	char keys[256] = { 0 };
	std::unique_ptr<BackScreen> backScreen = nullptr;
	std::unique_ptr<Cannon> cannon = nullptr;
	std::unique_ptr<Player> player = nullptr;
	int ruby = 0;
	int ido = 0;
};

