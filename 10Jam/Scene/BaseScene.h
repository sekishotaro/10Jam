#pragma once
class BaseScene {
public:
	BaseScene();
	~BaseScene();
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void  Update();
	/// <summary>
	/// �`��
	/// </summary>
	virtual void  Draw();
private:

};