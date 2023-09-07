#include "Particle.h"
#include <DxLib.h>
#include <cmath>
#include <ScrollManager.h>

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

	/// @brief 弐次元ベクトルの回転
	/// @param vec 回転前のベクトル
	/// @param angleRad 回転する角度
	/// @return 回転後のベクトル
	inline XMFLOAT2 rotation(const XMFLOAT2& vec, float angleRad)
	{
		return XMFLOAT2(vec.x * std::cos(angleRad) - vec.y * std::sin(angleRad),
						vec.x * std::sin(angleRad) + vec.y * std::cos(angleRad));
	}

	inline XMFLOAT2 operator+(const XMFLOAT2& l, const XMFLOAT2& r)
	{
		return XMFLOAT2(l.x + r.x, l.y + r.y);
	}
	inline XMFLOAT2 operator-(const XMFLOAT2& l, const XMFLOAT2& r)
	{
		return l + XMFLOAT2(-r.x, -r.y);
	}
	inline void operator+=(XMFLOAT2& l, const XMFLOAT2& r)
	{
		l.x += r.x;
		l.y += r.y;
	}
	inline void operator-=(XMFLOAT2& l, const XMFLOAT2& r)
	{
		l.x -= r.x;
		l.y -= r.y;
	}
}

Particle::Grain::Grain(unsigned life,
					   const XMFLOAT2& startPos,
					   const XMFLOAT2& endPos,
					   float startR,
					   float endR,
					   Particle::ColorRGB startColor,
					   Particle::ColorRGB endColor,
					   bool fillFlag) :
	lifeMax(life), life(life),
	startPos(startPos), pos(startPos),
	endPos(endPos),
	startR(startR), r(startR),
	endR(endR),
	startColor(startColor),
	endColor(endColor),
	fillFlag(fillFlag)
{
}

void Particle::Grain::Update()
{
	const auto scr = ScrollManager::GetInstance()->GetMove();
	startPos -= scr;
	endPos -= scr;

	const float rate = static_cast<float>(lifeMax - life) / static_cast<float>(lifeMax);

	pos = lerp(startPos, endPos, rate);
	r = lerp(startR, endR, rate);
	ColorRGB nowColor = lerp(startColor, endColor, rate);
	color = GetColor((int)nowColor.red, (int)nowColor.green, (int)nowColor.blue);

	--life;
}

int Particle::Grain::Draw() const
{
	return DxLib::DrawCircleAA(pos.x, pos.y, r, 64, color, fillFlag ? TRUE : FALSE);
}

void Particle::AddGrain(unsigned life,
						const XMFLOAT2& startPos,
						const XMFLOAT2& endPos,
						float startR,
						float endR,
						ColorRGB startColor,
						ColorRGB endColor,
						bool fillFlag)
{
	grains.emplace_front(life, startPos, endPos, startR, endR, startColor, endColor, fillFlag);
}

void Particle::Update()
{
	// 遅延生成情報更新
	delayGrainData.remove_if(
		[&](DelayGrainData& d)
		{
			const auto scr = ScrollManager::GetInstance()->GetMove();
			d.startPos -= scr;
			d.endPos -= scr;

			// 寿命が来ていたら、粒を出して遅延情報から削除
			if (d.nowFrame >= d.delayFrame)
			{
				AddGrain(d.life, d.startPos, d.endPos, d.startR, d.endR, d.startColor, d.endColor, d.fillFlag);
				return true;
			}
			// 寿命がまだなら更新
			++d.nowFrame;
			return false;
		});

	// 寿命が尽きた粒は消してから更新
	grains.remove_if([](const Grain& g) { return 0u >= g.GetLife(); });
	for (auto& i : grains)
	{
		i.Update();
	}
}

void Particle::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ADD, 64);
	for (auto& i : grains)
	{
		i.Draw();
	}
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Particle::Fireworks(const XMFLOAT2& centerPos, unsigned life, float range, uint8_t count, Particle::ColorRGB color, bool fillFlag)
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

		AddGrain(life, centerPos, endPos, 16.f, 0.f, color, color, fillFlag);
	}
}

void Particle::Ripple(const XMFLOAT2& centerPos, unsigned life, float range, uint8_t count, Particle::ColorRGB color)
{
	for (uint8_t i = 0; i < count; ++i)
	{
		const float rate = float(i) / float(count);

		delayGrainData.emplace_front();
		auto& n = delayGrainData.front();
		n.nowFrame = 0ui16;
		n.delayFrame = uint16_t(float(life) * rate);

		n.startPos = centerPos;
		n.endPos = centerPos;
		n.life = life;
		n.startR = 0.f;
		n.endR = range;
		n.startColor = color;
		n.endColor = ColorRGB{ 0, 0, 0 };
		n.fillFlag = false;
	}
}
