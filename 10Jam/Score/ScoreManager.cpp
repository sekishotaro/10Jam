#include "ScoreManager.h"
#include <DxLib.h>

int ScoreManager::score = 0;

ScoreManager* ScoreManager::GetInstance() {
	static ScoreManager instance;
	return &instance;
}

void ScoreManager::Draw() {
	SetFontSize(64);
	DrawFormatString(895, 25, GetColor(100, 100, 100), "SCORE:%d", score);
	DrawFormatString(900, 20, GetColor(255,255,255),"SCORE:%d", score);

}
