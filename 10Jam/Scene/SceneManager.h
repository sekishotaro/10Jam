#pragma once
#include "BaseScene.h"
#include "SceneChanger.h"

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
	/// <summary>
	/// �V�[���`�F���W���[���I����Ă邩�m�F
	/// </summary>
	/// <returns></returns>
	bool CheckChanger();

	//�V�[���I��
	bool endResquest_ = false;
	//���̃V�[��
	std::unique_ptr<BaseScene> scene_ = nullptr;
	//���̃V�[��
	std::unique_ptr<BaseScene> nextScene_ = nullptr;
	//�V�[���`�F���W
	std::unique_ptr<SceneChanger> sceneChanger_ = nullptr;

private:
	~SceneManager() = default;
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	void operator =(const SceneManager&) = delete;

};

