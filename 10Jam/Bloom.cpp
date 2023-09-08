#include "Bloom.h"
#include <DxLib.h>

void Bloom::InitBloomScreen()
{
	GetWindowSize(&window_width, &window_height);
	const int gauss_window_width = window_width / 8;
	const int gauss_window_height = window_height / 8;

	mainScreen = MakeScreen(window_width, window_height);
	highBrightScreen = MakeScreen(window_width, window_height);
	downScaleScreen = MakeScreen(gauss_window_width, gauss_window_height);
	gaussScreen = MakeScreen(gauss_window_width, gauss_window_height);
}

void Bloom::UpdateBloomScreen()
{
	// �`�挋�ʂ��獂�P�x�����݂̂𔲂��o�����摜�𓾂�
	GraphFilterBlt(mainScreen, highBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);

	// ���P�x�������W���̂P�ɏk�������摜�𓾂�
	GraphFilterBlt(highBrightScreen, downScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, 8);

	// �W���̂P�ɏk�������摜���K�E�X�t�B���^�łڂ���
	GraphFilterBlt(downScaleScreen, gaussScreen, DX_GRAPH_FILTER_GAUSS, 16, int(gaussVal));
}

void Bloom::DrawBloomScreen()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawExtendGraphF(0.f, 0.f, window_width, window_height, gaussScreen, TRUE);
	DrawExtendGraphF(0.f, 0.f, window_width, window_height, gaussScreen, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
