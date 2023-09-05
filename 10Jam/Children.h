#include "DxLib.h"
#include <d3d12.h>
#include <DirectXMath.h>
#pragma once

class Children
{
private: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	Children(float x, float y);
	~Children();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(XMFLOAT2 &PlayerPos);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:

	bool FreeFlag = false;
	XMFLOAT2 pos = { 600.0f, 410.0f };
};

