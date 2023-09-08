#pragma once
class Bloom
{
private:
	Bloom(const Bloom&) = delete;
	Bloom& operator=(const Bloom&) = delete;
	Bloom() = default;

public:
	inline static Bloom* Ins()
	{
		static Bloom b{};
		return &b;
	}

	// ウィンドウの大きさ
	int window_width = -1;
	int window_height = -1;

	int mainScreen = -1;
	int highBrightScreen = -1;
	int downScaleScreen = -1;
	int gaussScreen = -1;

	constexpr static unsigned gaussVal = 200;

	void InitBloomScreen();
	void UpdateBloomScreen();
	void DrawBloomScreen();
};
