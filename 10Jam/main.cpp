#include <DxLib.h>
#include "SceneManager.h"
#include <SceneChanger.h>
#include <array>
#include "resource.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// ウィンドウのタイトルに表示する文字列
	constexpr char TITLE[] = "【井】（かこい）";

	// ウィンドウの大きさ
	constexpr int window_width = 1280;
	constexpr int window_height = 720;

	// Log.txtを出力しない
	SetOutApplicationLogValidFlag(FALSE);

	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);
	//アイコン設定
	SetWindowIconID(IDI_ICON1);
	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(window_width, window_height, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x30, 0x30, 0x30);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1; // エラーが起きたら直ちに終了
	}

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// デフォルトのフォントを変更
	constexpr int edgeSize = 2;
	ChangeFontFromHandle(LoadFontDataToHandle("Resources/FZゴンタかな_32.dft", edgeSize));

	// 文字描画にアンチエイリアスと枠線を付ける
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	// ビネッタ用
	const int vignette = LoadGraph("Resources/vignette.png");

	constexpr size_t keyCount = 256u;
	std::array<char, keyCount> keys{};
	std::array<char, keyCount> oldkeys{};

	SceneManager* sceneManager_ = SceneManager::GetInstance();
	sceneManager_->Initialize(SceneManager::SceneName::TITLE);

	// ゲームループ
	while (ProcessMessage() == 0 &&
		   CheckHitKey(KEY_INPUT_ESCAPE) != 1) 	{
		// 画面クリア
		ClearDrawScreen();

		// 最新のキーボード情報だったものは
		// 1フレーム前のキーボード情報として保存
		oldkeys = keys;

		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys.data());

		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		sceneManager_->Update();
		// 描画処理
		sceneManager_->Draw();

		// ビネッタ描画
		DrawExtendGraphF(0.f, 0.f, 1280.f, 720.f, vignette, TRUE);

		//---------  ここまでにプログラムを記述  ---------//

		// (ダブルバッファ)裏面
		ScreenFlip();

		// 16ミリ秒待機(疑似60FPS)
		WaitTimer(16);
	}

	DxLib_End();

	return 0;				// ソフトの終了
}