#pragma once

#include <DirectXMath.h>
#include <forward_list>

class Particle
{
public:
	struct ColorRGB
	{
		uint8_t red = 0ui8;
		uint8_t green = 0ui8;
		uint8_t blue = 0ui8;
	};

private:
	using XMFLOAT2 = DirectX::XMFLOAT2;

	class Grain
	{
	private:
		unsigned life = 0u;

		XMFLOAT2 startPos{};
		XMFLOAT2 endPos{};
		float startR = 1.f;
		float endR = 1.f;
		ColorRGB startColor{};
		ColorRGB endColor{};

		XMFLOAT2 pos{};
		float r = 1.f;
		unsigned lifeMax = 1u;
		unsigned color;

	public:
		Grain(unsigned life,
			  const XMFLOAT2& startPos,
			  const XMFLOAT2& endPos,
			  float startR,
			  float endR,
			  ColorRGB startColor,
			  ColorRGB endColor);

		inline unsigned getLife() const { return life; }

		void update();
		int draw() const;
	};

	std::forward_list<Grain> grains;

public:
	void addGrain(unsigned life,
				  const XMFLOAT2& startPos,
				  const XMFLOAT2& endPos,
				  float startR,
				  float endR,
				  ColorRGB startColor,
				  ColorRGB endColor);

	void update();

	void draw();

	void fireworks(const XMFLOAT2& centerPos, unsigned life, float range, uint8_t count, ColorRGB color);

	inline bool isEmpty() const
	{
		return grains.empty();
	}
};

