#pragma once
class SceneChanger {
public:
	/// <summary>
	/// �C���X�g���N�^
	/// </summary>
	SceneChanger();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneChanger();

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
	float frame_ = 0.f, kFrameMax = 45.f, frameNow_ = 0.0f;
	float r = 0.f;
	bool isStart = true;
	bool isClose = false;

};
