#pragma once
#include "../Children.h"
#include<memory>
#include<list>

class Cannon {
public:
	Cannon();
	~Cannon();
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize();
	/// <summary>
	/// XV
	/// </summary>
	void Update();
	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw();

	void Spawn();

	void SetPlayer(Player* player) {player_ = player;}

	bool TimeProgress();
private:
	std::list<std::unique_ptr<Children>> Childrens = {};
	Player* player_ = nullptr;
	float coolTimer_ = 0.0f;
	float kCoolTimer = 60.0f;

	float alignmentMaxTime = 2.0f;
	float time = 0.0f;
public:
	bool deleteChilFlag = false;
};