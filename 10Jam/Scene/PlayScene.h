#pragma once
#include "BaseScene.h"
#include "../Player.h"
#include "../Children.h"
#include <memory>
#include "Cannon.h"
#include <AccelSpot.h>

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
	std::unique_ptr<Player> player = nullptr;
	std::unique_ptr<Cannon> cannon_ = nullptr;
	std::unique_ptr<AccelSpot> accel = nullptr;
};

