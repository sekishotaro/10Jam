#pragma once
#include "DxLib.h"

class BaseScene {
public:
	BaseScene();
	~BaseScene();
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// 更新
	/// </summary>
	virtual void  Update();
	/// <summary>
	/// 描画
	/// </summary>
	virtual void  Draw();
private:

};