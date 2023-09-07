#pragma once

#include <DirectXMath.h>
#include <forward_list>
#include <memory>

class Particle
{
private:
	Particle(const Particle&) = delete;
	Particle& operator=(const Particle&) = delete;
	Particle() = default;

public:
	/// @brief シングルトンのインスタンスを取得する
	inline static Particle* Ins()
	{
		static Particle p{};
		return &p;
	}

	/// @brief Ins関数を呼ぶ
	inline static Particle* GetInstance()
	{
		return Ins();
	}

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
		bool fillFlag;
		uint8_t posnum;

	public:
		Grain(unsigned life,
			  const XMFLOAT2& startPos,
			  const XMFLOAT2& endPos,
			  float startR,
			  float endR,
			  ColorRGB startColor,
			  ColorRGB endColor,
			  bool fillFlag = true,
			  uint8_t posnum = 4ui8);

		inline unsigned GetLife() const { return life; }

		void Update();
		int Draw() const;
	};

	std::forward_list<Grain> grains{};

	struct DelayGrainData
	{
		uint16_t delayFrame = 0ui16;
		uint16_t nowFrame = 0ui16;

		unsigned life;
		XMFLOAT2 startPos;
		XMFLOAT2 endPos;
		float startR;
		float endR;
		ColorRGB startColor;
		ColorRGB endColor;
		bool fillFlag = true;
		uint8_t posnum;
	};
	std::forward_list<DelayGrainData> delayGrainData{};

public:
	/// @brief 粒を追加
	void AddGrain(unsigned life,
				  const XMFLOAT2& startPos,
				  const XMFLOAT2& endPos,
				  float startR,
				  float endR,
				  ColorRGB startColor,
				  ColorRGB endColor,
				  bool fillFlag = true,
				  uint8_t posnum = 4ui8);

	/// @brief 更新処理。各シーンで毎フレーム呼ぶ。
	void Update();

	/// @brief 描画処理。各シーンで毎フレーム呼ぶ。
	void Draw();

	/// @brief 放射状に人がるパーティクルを開始
	void Fireworks(const XMFLOAT2& centerPos, unsigned life, float range, uint8_t count, ColorRGB color, bool fillFlag = true, uint8_t posnum = 4ui8);

	/// @brief 波紋を開始
	/// @param count 時間内に生成する個数
	void Ripple(const XMFLOAT2& centerPos, unsigned life, float range, uint8_t count, ColorRGB color, uint8_t posnum = 4ui8);

	/// @brief 粒が一つもないかどうか
	inline bool IsEmpty() const
	{
		return grains.empty();
	}

	/// @brief 粒の全削除
	inline void Clear()
	{
		grains.clear();
	}
};
