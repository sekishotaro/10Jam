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
	/// @brief �V���O���g���̃C���X�^���X���擾����
	inline static Particle* Ins()
	{
		static Particle p{};
		return &p;
	}

	/// @brief Ins�֐����Ă�
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
	/// @brief ����ǉ�
	void AddGrain(unsigned life,
				  const XMFLOAT2& startPos,
				  const XMFLOAT2& endPos,
				  float startR,
				  float endR,
				  ColorRGB startColor,
				  ColorRGB endColor,
				  bool fillFlag = true,
				  uint8_t posnum = 4ui8);

	/// @brief �X�V�����B�e�V�[���Ŗ��t���[���ĂԁB
	void Update();

	/// @brief �`�揈���B�e�V�[���Ŗ��t���[���ĂԁB
	void Draw();

	/// @brief ���ˏ�ɐl����p�[�e�B�N�����J�n
	void Fireworks(const XMFLOAT2& centerPos, unsigned life, float range, uint8_t count, ColorRGB color, bool fillFlag = true, uint8_t posnum = 4ui8);

	/// @brief �g����J�n
	/// @param count ���ԓ��ɐ��������
	void Ripple(const XMFLOAT2& centerPos, unsigned life, float range, uint8_t count, ColorRGB color, uint8_t posnum = 4ui8);

	/// @brief ��������Ȃ����ǂ���
	inline bool IsEmpty() const
	{
		return grains.empty();
	}

	/// @brief ���̑S�폜
	inline void Clear()
	{
		grains.clear();
	}
};
