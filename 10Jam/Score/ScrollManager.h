#pragma once
#include"DirectXMath.h"

class ScrollManager {
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
public:
	static ScrollManager* GetInstance();

	XMFLOAT2 GetMove() { return move; }

	void SetMove(const XMFLOAT2 move) { this->move = move; }

	void Reset() { move = {}; }

private:
	static XMFLOAT2 move;
private:
	~ScrollManager() = default;
	ScrollManager() = default;
	ScrollManager(const ScrollManager&) = delete;
	void operator =(const ScrollManager&) = delete;
};

