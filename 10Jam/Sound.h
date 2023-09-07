/*****************************************************************//**
 * \file   Sound.h
 * \brief  �����f�[�^�������N���X
 *********************************************************************/

#pragma once

#include <DxLib.h>
#include <string>
#include <unordered_map>
#include <memory>

 /// @brief �����f�[�^�������N���X
class Sound
{
private:
	Sound(const Sound&) = delete;
	Sound& operator=(const Sound&) = delete;
	Sound() = default;

public:
	/// @brief �V���O���g���̃C���X�^���X���擾����
	inline static Sound* Ins()
	{
		static Sound p{};
		return &p;
	}

	/// @brief Ins�֐����Ă�
	inline static Sound* GetInstance()
	{
		return Ins();
	}

private:
	/// @brief �ǂݍ��񂾃f�[�^�̃n���h������
	std::unordered_map<std::string, std::unique_ptr<int>> handles;

public:
	/// @brief �t�@�C�����特���f�[�^��ǂݍ���
	/// @param filePath �ǂݍ��މ����t�@�C���̃p�X
	/// @return -1�Ȃ�G���[�A����ȊO�Ȃ�T�E���h�n���h��
	int LoadFile(const std::string& filePath);

	/// @brief �ǂݍ��񂾉����f�[�^���Đ�����
	/// @param handle �Đ����鉹���f�[�^�̃n���h��
	/// @param topPositionFlag �f�[�^�̐擪����Đ����邩�ǂ���
	/// @param playType �Đ��`���B��{��DX_PLAYTYPE_LOOP(�K��l)��������DX_PLAYTYPE_BACK
	/// @return �G���[�������true
	inline bool Play(int handle, bool topPositionFlag = true, int playType = DX_PLAYTYPE_LOOP)
	{
		return -1 == DxLib::PlaySoundMem(handle, DX_PLAYTYPE_LOOP, topPositionFlag ? TRUE : FALSE);
	}

	/// @brief �����̍Đ����~����
	/// @param handle ��~���鉹���f�[�^�̃n���h��
	/// @return �G���[�������true
	inline bool Stop(int handle)
	{
		return -1 == DxLib::StopSoundMem(handle);
	}

	/// @brief �����f�[�^���Đ������ǂ���
	/// @param handle �m�F���鉹���f�[�^�̃n���h��
	/// @param[out] error �y�ȗ��z�G���[�����邩�ǂ������i�[����bool�^�ϐ�
	/// @return �Đ����Ȃ�true
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
