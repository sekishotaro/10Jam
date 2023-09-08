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
	// •`‰æŒ‹‰Ê‚©‚ç‚‹P“x•”•ª‚Ì‚İ‚ğ”²‚«o‚µ‚½‰æ‘œ‚ğ“¾‚é
	GraphFilterBlt(mainScreen, highBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);

	// ‚‹P“x•”•ª‚ğ‚W•ª‚Ì‚P‚Ék¬‚µ‚½‰æ‘œ‚ğ“¾‚é
	GraphFilterBlt(highBrightScreen, downScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, 8);

	// ‚W•ª‚Ì‚P‚Ék¬‚µ‚½‰æ‘œ‚ğƒKƒEƒXƒtƒBƒ‹ƒ^‚Å‚Ú‚©‚·
	GraphFilterBlt(downScaleScreen, gaussScreen, DX_GRAPH_FILTER_GAUSS, 16, int(gaussVal));
}

void Bloom::DrawBloomScreen()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawExtendGraphF(0.f, 0.f, window_width, window_height, gaussScreen, TRUE);
	DrawExtendGraphF(0.f, 0.f, window_width, window_height, gaussScreen, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
