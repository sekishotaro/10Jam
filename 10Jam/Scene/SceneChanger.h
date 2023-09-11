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
	/// インストラクタ
	/// </summary>
	SceneChanger();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneChanger();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ゲッター&setter
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
	/// @brief kFrameMaxの範囲内でframe_を増やす
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
