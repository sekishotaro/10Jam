#include "Particle.h"
#include <DxLib.h>
#include <cmath>

using namespace DirectX;

namespace
{
	template <class T>
	constexpr T lerp(T a, T b, float t)
	{
		return static_cast<T>(a + t * (b - a));
	}

	constexpr XMFLOAT2 lerp(const XMFLOAT2& a, const XMFLOAT2& b, float t)
	{
		return XMFLOAT2(lerp(a.x, b.x, t),
						lerp(a.y, b.y, t));
	}
	constexpr Particle::ColorRGB lerp(const Particle::ColorRGB& a, const Particle::ColorRGB& b, float t)
	{
		return Particle::ColorRGB{
			(uint8_t)lerp<float>(a.red, b.red, t),
			(uint8_t)lerp<float>(a.green, b.green, t),
			(uint8_t)lerp<float>(a.blue, b.blue, t)
		};
	}

	inline XMFLOAT2 rotation(const XMFLOAT2& vec, float angleRad)
	{
		return XMFLOAT2(vec.x * std::cos(angleRad) - vec.y * std::sin(angleRad),
						vec.x * std::sin(angleRad) + vec.y * std::cos(angleRad));
	}
}

Particle::Grain::Grain(unsigned life,
					   const XMFLOAT2& startPos,
					   const XMFLOAT2& endPos,
					   float startR,
					   float endR,
					   Particle::ColorRGB startColor,
					   Particle::ColorRGB endColor) :
	lifeMax(life), life(life),
	startPos(startPos), pos(startPos),
	endPos(endPos),
	startR(startR), r(startR),
	endR(endR),
	startColor(startColor),
	endColor(endColor)
{
}

void Particle::Grain::update()
{
	const float rate = static_cast<float>(lifeMax - life) / static_cast<float>(lifeMax);

	pos = lerp(startPos, endPos, rate);
	r = lerp(startR, endR, rate);
	ColorRGB nowColor = lerp(startColor, endColor, rate);
	color = GetColor((int)nowColor.red, (int)nowColor.green, (int)nowColor.blue);

	--life;
}

int Particle::Grain::draw() const
{
	return DxLib::DrawCircleAA(pos.x, pos.y, r, 32, color);
}

void Particle::addGrain(unsigned life,
						const XMFLOAT2& startPos,
						const XMFLOAT2& endPos,
						float startR,
						float endR,
						ColorRGB startColor,
						ColorRGB endColor)
{
	grains.emplace_front(life, startPos, endPos, startR, endR, startColor, endColor);
}

void Particle::update()
{
	grains.remove_if([](const Grain& g) { return 0u >= g.getLife(); });
	for (auto& i : grains)
	{
		i.update();
	}
}

void Particle::draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ADD, 64);
	for (auto& i : grains)
	{
		i.draw();
	}
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Particle::fireworks(const XMFLOAT2& centerPos, unsigned life, float range, uint8_t count, Particle::ColorRGB color)
{
	XMFLOAT2 endPos{};
	float angleRad{};

	for (uint8_t i = 0; i < count; ++i)
	{
		angleRad = (float)i / (float)count * XM_2PI;

		float length = range / 1.41421356f;
		endPos = rotation(XMFLOAT2(length, length), angleRad);

		endPos.x += centerPos.x;
		endPos.y += centerPos.y;

		addGrain(life, centerPos, endPos, 16.f, 0.f, color, color);
	}
}
