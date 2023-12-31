/*****************************************************************//**
 * \file   Sound.h
 * \brief  音声データを扱うクラス
 *********************************************************************/

#pragma once

#include <DxLib.h>
#include <string>
#include <unordered_map>
#include <memory>

 /// @brief 音声データを扱うクラス
class Sound
{
private:
	Sound(const Sound&) = delete;
	Sound& operator=(const Sound&) = delete;
	Sound();

public:
	/// @brief シングルトンのインスタンスを取得する
	inline static Sound* Ins()
	{
		static Sound p{};
		return &p;
	}

	/// @brief Ins関数を呼ぶ
	inline static Sound* GetInstance()
	{
		return Ins();
	}

private:
	/// @brief 読み込んだデータのハンドルたち
	std::unordered_map<std::string, std::unique_ptr<int>> handles;

public:
	/// @brief ファイルから音声データを読み込む
	/// @param filePath 読み込む音声ファイルのパス
	/// @return -1ならエラー、それ以外ならサウンドハンドル
	int LoadFile(const std::string& filePath);

	/// @brief 音量を変更
	/// @param handle 音声データのハンドル
	/// @param volume 変更後の音量(0 ~ 255)
	/// @return エラーがあればtrue
	inline bool Volume(int handle, uint8_t volume)
	{
		return -1 == DxLib::SetVolumeSoundMem(int(volume), handle);
	}

	/// @brief 読み込んだ音声データを再生する
	/// @param handle 再生する音声データのハンドル
	/// @param topPositionFlag データの先頭から再生するかどうか
	/// @param playType 再生形式。基本はDX_PLAYTYPE_LOOP(規定値)もしくはDX_PLAYTYPE_BACK
	/// @return エラーがあればtrue
	inline bool Play(int handle, bool topPositionFlag = true, int playType = DX_PLAYTYPE_LOOP)
	{
		return -1 == DxLib::PlaySoundMem(handle, playType, topPositionFlag ? TRUE : FALSE);
	}

	/// @brief 音声の再生を停止する
	/// @param handle 停止する音声データのハンドル
	/// @return エラーがあればtrue
	inline bool Stop(int handle)
	{
		return -1 == DxLib::StopSoundMem(handle);
	}

	/// @brief 音声データが再生中かどうか
	/// @param handle 確認する音声データのハンドル
	/// @param[out] error 【省略可】エラーがあるかどうかを格納するbool型変数
	/// @return 再生中ならtrue
	inline bool IsPlaying(int handle, bool* error = nullptr)
	{
		const int ret = DxLib::CheckSoundMem(handle);
		if (error)
		{
			*error = (-1 == ret);
		}
		return 1 == ret;
	}
};
