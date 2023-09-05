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
	/// インストラクタ
	/// </summary>
	SceneManager(const SceneName SceneName);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneManager();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
private:
	BaseScene* CreateScene(const SceneName sceneName);
	BaseScene* scene_ = nullptr;

};

