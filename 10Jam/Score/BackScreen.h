#pragma once
#include"DxLib.h"
#include "DirectXMath.h"

class BackScreen {
public:
	BackScreen();
	~BackScreen();
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
	DirectX::XMFLOAT2 sub = {};

};

