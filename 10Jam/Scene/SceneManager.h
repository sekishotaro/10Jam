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
	/// 初期化
	/// </summary>
	void Initialize(const SceneName sceneName);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	void ChangeScene(const SceneName sceneName);
private:
	std::unique_ptr<BaseScene> CreateScene(const SceneName sceneName);
	/// <summary>
	/// シーンチェンジャーが終わってるか確認
	/// </summary>
	/// <returns></returns>
	bool CheckChanger();

	//シーン終了
	bool endResquest_ = false;
	//今のシーン
	std::unique_ptr<BaseScene> scene_ = nullptr;
	//次のシーン
	std::unique_ptr<BaseScene> nextScene_ = nullptr;
	//シーンチェンジ
	std::unique_ptr<SceneChanger> sceneChanger_ = nullptr;

private:
	~SceneManager() = default;
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	void operator =(const SceneManager&) = delete;

};

