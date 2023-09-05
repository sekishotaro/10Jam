/*****************************************************************//**
 * \file   Sound.h
 * \brief  音声データを扱うクラス
 *********************************************************************/

#pragma once

#include <DxLib.h>
#include <string>

 /// @brief 音声データを扱うクラス
class Sound
{
public:
	/// @brief ファイルから音声データを読み込む
	/// @param filePath 読み込む音声ファイルのパス
	/// @return -1ならエラー、それ以外ならサウンドハンドル
	inline static int LoadFile(const std::string& filePath)
	{
		return DxLib::LoadSoundMem(filePath.c_str());
	}

	/// @brief 読み込んだ音声データを再生する
	/// @param handle 再生する音声データのハンドル
	/// @param topPositionFlag データの先頭から再生するかどうか
	/// @param playType 再生形式。基本はDX_PLAYTYPE_LOOP(規定値)もしくはDX_PLAYTYPE_BACK
	/// @return エラーがあればtrue
	inline static bool Play(int handle, bool topPositionFlag = true, int playType = DX_PLAYTYPE_LOOP)
	{
		return -1 == DxLib::PlaySoundMem(handle, DX_PLAYTYPE_LOOP, topPositionFlag ? TRUE : FALSE);
	}

	/// @brief 音声の再生を停止する
	/// @param handle 停止する音声データのハンドル
	/// @return エラーがあればtrue
	inline static bool Stop(int handle)
	{
		return -1 == DxLib::StopSoundMem(handle);
	}

	/// @brief 音声データが再生中かどうか
	/// @param handle 確認する音声データのハンドル
	/// @param[out] error 【省略可】エラーがあるかどうかを格納するbool型変数
	/// @return 再生中ならtrue
	inline static bool IsPlaying(int handle, bool* error = nullptr)
	{
		const int ret = DxLib::CheckSoundMem(handle);
		if (error)
		{
			*error = (-1 == ret);
		}
		return 1 == ret;
	}
};
