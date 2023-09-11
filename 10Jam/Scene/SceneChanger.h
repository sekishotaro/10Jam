#pragma once
#include <cstdint>
#include <functional>
class SceneChanger {
public:
	enum class PHASE : uint8_t
	{
		START,
		CLOSE,
		INVISIBLE
	};

	/// <summary>
	/// �C���X�g���N�^
	/// </summary>
	SceneChanger();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneChanger();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �Q�b�^�[&setter
	/// </summary>
	inline void SetIsStart() { phase = PHASE::START; updateProc = std::bind(&SceneChanger::UpdateStart, this);
	}
	inline bool GetIsStart() const { return phase == PHASE::START; }

	inline void SetIsClose() { phase = PHASE::CLOSE; updateProc = std::bind(&SceneChanger::UpdateClose, this); }
	inline bool GetIsClose() const { return phase == PHASE::CLOSE; }

	inline auto GetPhase() const { return phase; }

private:
	static constexpr uint8_t kFrameMax = 45ui8;
	uint8_t frame_ = 0;
	float r = 0.f;
	PHASE phase = PHASE::INVISIBLE;

	std::function<void()> updateProc = [] {};

private:
	/// @brief kFrameMax�͈͓̔���frame_�𑝂₷
	inline void UpdateFrame()
	{
		frame_ = ++frame_ % kFrameMax;
	}

	inline void EndSceneChange()
	{
		phase = PHASE::INVISIBLE;
		updateProc = [] {};
	}

	void UpdateStart();
	void UpdateClose();
};
