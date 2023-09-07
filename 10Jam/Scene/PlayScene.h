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
	/// ������
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;
private:
	Player* player = nullptr;
	std::unique_ptr<Cannon> cannon_ = nullptr;
	char keys[256] = { 0 };
};

