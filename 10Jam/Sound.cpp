#include "Sound.h"

int Sound::LoadFile(const std::string& filePath)
{
	auto result = handles.try_emplace(filePath, nullptr);

	// もともとなければ
	if (result.second)
	{
		result.first->second = std::make_unique<int>(DxLib::LoadSoundMem(filePath.c_str()));
	}

	return *result.first->second;
}
