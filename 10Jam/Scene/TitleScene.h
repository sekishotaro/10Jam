#pragma once
#include "BaseScene.h"

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

};

