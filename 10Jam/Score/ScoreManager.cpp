#include "ScoreManager.h"
#include <DxLib.h>

int ScoreManager::score = 0;

ScoreManager* ScoreManager::GetInstance() {
	static ScoreManager instance;
	return &instance;
}

void ScoreManager::Draw() {
	DrawFormatString(1000, 0, GetColor(255,255,255),"SCORE: %d", score);
}
