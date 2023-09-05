#pragma once
class BaseScene {
public:
	BaseScene();
	~BaseScene();
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// XV
	/// </summary>
	virtual void  Update();
	/// <summary>
	/// •`‰æ
	/// </summary>
	virtual void  Draw();
private:

};