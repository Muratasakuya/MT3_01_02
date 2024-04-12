#include <Novice.h>
#include "Camera.h"
#include "Grid.h"
#include "Sphere.h"

const char kWindowTitle[] = "LC1B_28_ムラタ_サクヤ_MT3_01_02";

#pragma warning(push)
#pragma warning(disable:28251)
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#pragma warning(pop)

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// 変数宣言
	Camera* camera = new Camera();
	Grid* grid = new Grid();
	Sphere* sphere = new Sphere();

	// カメラの変数の初期化
	camera->Init();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// カメラの更新処理
		camera->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッド線の描画
		grid->DrawGid(
			camera->GetViewMatrix(), camera->GetProjectionMatrix(), camera->GetViewportMatrix()
		);

		// 球の描画
		sphere->DrawSphere(
			camera->GetViewMatrix(), camera->GetProjectionMatrix(), camera->GetViewportMatrix()
		);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();

	// 作成したインスタンスの開放
	delete camera;
	delete grid;
	delete sphere;

	return 0;
}
