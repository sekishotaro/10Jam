#pragma once
#include "../Children.h"
#include<memory>
#include<list>

#include "GearSpot.h"
#include "AccelSpot.h"

class Cannon {
public:
	Cannon();
	~Cannon();
	/// <summary>
	/// èâä˙âª
	/// </summary>
	void Initialize();
	/// <summary>
	/// çXêV
	/// </summary>
	void Update();
	/// <summary>
	/// ï`âÊ
	/// </summary>
	void Draw();

	void Spawn();
	void SpotSpawn();

	void SetPlayer(Player* player) {player_ = player;}

	bool TimeProgress();
private:
	std::list<std::unique_ptr<Children>> Childrens = {};
	std::list<std::unique_ptr<AccelSpot>> accels = {};
	std::list<std::unique_ptr<GearSpot>> gears = {};

	bool isSpawnGear = false;
	bool isSpawn = false;
	int mScore = 0;
	int mGscore = 0;

	Player* player_ = nullptr;
	float coolTimer_ = 0.0f;
	float kCoolTimer = 60.0f;

	float alignmentMaxTime = 0.5f;
	float time = 0.0f;
public:
	bool deleteChilFlag = false;
};