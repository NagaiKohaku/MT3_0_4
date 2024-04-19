#include <Novice.h>
#include <cmath>

const char kWindowTitle[] = "LE2B_17_ナガイ_コハク_MT3_0_4 4x4行列の回転";

//4x4行列
struct Matrix4x4 {
	float m[4][4];
};

//3次元ベクトル
struct Vector3 {
	float x, y, z;
};

//X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

//Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

//Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

//行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

//4x4行列の表示
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

//表示幅:横
static const int kColumnWidth = 60;

//表示幅:縦
static const int kRowHeight = 20;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//回転量
	Vector3 rotate{ 0.4f,1.43f,-0.8f };

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

		//X軸回転行列
		Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
		
		//Y軸回転行列
		Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
		
		//Z軸回転行列
		Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
		
		//XYZ回転行列
		Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//X軸回転行列の内容の表示
		MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");

		//Y軸回転行列の内容の表示
		MatrixScreenPrintf(0, kRowHeight * 5, rotateYMatrix, "rotateYMatrix");

		//Z軸回転行列の内容の表示
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, rotateZMatrix, "rotateZMatrix");

		//XYZ回転行列の内容の表示
		MatrixScreenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");

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
	return 0;
}

//X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {

	Matrix4x4 result;

	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = std::cosf(radian);
	result.m[1][2] = std::sinf(radian);
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = -std::sinf(radian);
	result.m[2][2] = std::cosf(radian);
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

//Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {

	Matrix4x4 result;

	result.m[0][0] = std::cosf(radian);
	result.m[0][1] = 0;
	result.m[0][2] = -std::sinf(radian);
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = std::sinf(radian);
	result.m[2][1] = 0;
	result.m[2][2] = std::cosf(radian);
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

//Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {

	Matrix4x4 result;

	result.m[0][0] = std::cosf(radian);
	result.m[0][1] = std::sinf(radian);
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = -std::sinf(radian);
	result.m[1][1] = std::cosf(radian);
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

//行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = (m1.m[i][0] * m2.m[0][j]) + (m1.m[i][1] * m2.m[1][j]) + (m1.m[i][2] * m2.m[2][j]) + (m1.m[i][3] * m2.m[3][j]);
		}
	}

	return result;

}

//4x4行列の表示
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {

	//計算方法の表示
	Novice::ScreenPrintf(x, y, label);

	//行列の内容の表示
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%6.02f", matrix.m[row][column]
			);
		}
	}
}