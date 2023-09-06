#include "ScrollManager.h"
DirectX::XMFLOAT2 ScrollManager::move = {};
ScrollManager* ScrollManager::GetInstance() {
	static ScrollManager instance;
	return &instance;
}
