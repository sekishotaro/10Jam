#include <DxLib.h>
#include "SceneManager.h"
#include <SceneChanger.h>
#include <array>
#include "resource.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// �E�B���h�E�̃^�C�g���ɕ\�����镶����
	constexpr char TITLE[] = "�y��z�i�������j";

	// �E�B���h�E�̑傫��
	constexpr int window_width = 1280;
	constexpr int window_height = 720;

	// Log.txt���o�͂��Ȃ�
	SetOutApplicationLogValidFlag(FALSE);

	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);
	//�A�C�R���ݒ�
	SetWindowIconID(IDI_ICON1);
	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(window_width, window_height, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x30, 0x30, 0x30);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1; // �G���[���N�����璼���ɏI��
	}

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �f�t�H���g�̃t�H���g��ύX
	constexpr int edgeSize = 2;
	ChangeFontFromHandle(LoadFontDataToHandle("Resources/FZ�S���^����_32.dft", edgeSize));

	// �����`��ɃA���`�G�C���A�X�Ƙg����t����
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	// �r�l�b�^�p
	const int vignette = LoadGraph("Resources/vignette.png");

	constexpr size_t keyCount = 256u;
	std::array<char, keyCount> keys{};
	std::array<char, keyCount> oldkeys{};

	SceneManager* sceneManager_ = SceneManager::GetInstance();
	sceneManager_->Initialize(SceneManager::SceneName::TITLE);

	// �Q�[�����[�v
	while (ProcessMessage() == 0 &&
		   CheckHitKey(KEY_INPUT_ESCAPE) != 1) 	{
		// ��ʃN���A
		ClearDrawScreen();

		// �ŐV�̃L�[�{�[�h��񂾂������̂�
		// 1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		oldkeys = keys;

		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys.data());

		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		sceneManager_->Update();
		// �`�揈��
		sceneManager_->Draw();

		// �r�l�b�^�`��
		DrawExtendGraphF(0.f, 0.f, 1280.f, 720.f, vignette, TRUE);

		//---------  �����܂łɃv���O�������L�q  ---------//

		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 16�~���b�ҋ@(�^��60FPS)
		WaitTimer(16);
	}

	DxLib_End();

	return 0;				// �\�t�g�̏I��
}