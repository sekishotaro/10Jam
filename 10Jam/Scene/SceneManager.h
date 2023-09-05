#pragma once
#include "BaseScene.h"
#include <memory>

class SceneManager {
public:
	enum class SceneName :int {
		TITLE = 0,
		PLAY,
		RESULT
	};
	static SceneManager* GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const SceneName sceneName);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();


	void ChangeScene(const SceneName sceneName);
private:
	std::unique_ptr<BaseScene> CreateScene(const SceneName sceneName);

	//�V�[���I��
	bool endResquest_ = false;
	//���̃V�[��
	std::unique_ptr<BaseScene> scene_ = nullptr;
	//���̃V�[��
	std::unique_ptr<BaseScene> nextScene_ = nullptr;
private:
	~SceneManager() = default;
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	void operator =(const SceneManager&) = delete;

};

