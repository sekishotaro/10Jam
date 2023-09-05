#pragma once
#include "BaseScene.h"
#include <string>
#include <memory>

class SceneManager {
public:	
	enum class SceneName :int {
	TITLE = 0,
	PLAY,
	RESULT
	};
	/// <summary>
	/// �C���X�g���N�^
	/// </summary>
	SceneManager(const SceneName SceneName);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneManager();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
private:
	BaseScene* CreateScene(const SceneName sceneName);
	BaseScene* scene_ = nullptr;

};

