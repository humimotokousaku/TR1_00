#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector2.h"
#include "Spring.h"
#include "Common.h"

const char kWindowTitle[] = "LE2B_22_フミモト_コウサク";

enum SpringType {
	TITLE,
	ASIXY,
	FREE,
	OBJWHILE
};
int springType = TITLE;

struct SpringInfo {
	Vector2 pos{ kWindowWidth / 2, kWindowHeight / 2 };
	Vector2 vel{ 0, 0 };
	float a;
	float acceleration = 1;
	float radius = 16;
	float mass = 10;
	float displacement = 200;
	float k = 0.1f;
	// 減衰振動
	float dampedVibration = 0.98f;
	int isDapedVibration = true;
};

struct Wave {
	Vector2 pos;
	float radius;
	float theta;
	float amplitude;
	float time;
	float velX;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// 画像読み込み
	int whiteRect = Novice::LoadTexture("white1x1.png");

	// 宣言
	/*Spring* spring;
	spring = new Spring();*/

	const int kWavePoint = 100;  

	float wavePointWhile = 12.8f;//kWindowWidth / kWavePoint;

	float firstSurface = kWindowHeight / 2;
	float maxAmplitude = 100;
	const float plus = 0.1f;

	bool isWave = false;
	float time = 0;

	//float a[kWavePoint];
	//for (int i = 0; i < kWavePoint; i++) {
	//	a[i] = 0.5f * M_PI * i;
	//}

	Wave sinWave[kWavePoint];
	for (int i = 0; i < kWavePoint; i++) {
		sinWave[i].pos.x = (i * wavePointWhile);
		sinWave[i].pos.y = firstSurface;
		sinWave[i].radius = 8.0f;
		sinWave[i].amplitude = 0;
		sinWave[i].theta = 0;
		sinWave[i].time = 0;
		sinWave[i].velX = 1;
	}

	// 周期
	float T = 120;
	// 波が進む速さ[m/s]
	float velX = 1;
	// 波長(今回は使わない)
	float λ = T * velX;
	// 振動数
	float hz = 1.0f / T;

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

		// 開始
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			isWave = true;
		}
		if (keys[DIK_UP]) {
			maxAmplitude += plus;
		}
		if (keys[DIK_DOWN]) {
			maxAmplitude -= plus;
		}
		if (keys[DIK_V]) {
				velX += 1.0f / 60.0f;
		}
		if (keys[DIK_T]) {
			T += 1;
		}

		if (isWave) {
			for (int i = 0; i < kWavePoint; i++) {	
				λ = T * velX;
				velX = λ / T;
				T = λ / velX;
				hz = 1.0f / T;
				//sinWave[i].pos.y = firstSurface + sinf(M_PI * 2 / 60 * time + a[i]/*(0.2f * M_PI * i)*//*sinWave[i].pos.x*/) * maxAmplitude;			
				//sinWave[i].pos.x = (wavePointWhile * i) + maxAmplitude * sinf(M_PI / 30 * sinWave[i].time);
				//sinWave[i].pos.y = firstSurface + maxAmplitude * sinf(M_PI / 30 * sinWave[i].time);
				//sinWave[i].time = (M_PI / 30) + (sinWave[i].pos.x / sinWave[i].velX);
				sinWave[i].pos.y = firstSurface + maxAmplitude * sinf(2 * static_cast<float>(M_PI) / T * (time - (sinWave[i].pos.x / velX)));
				sinWave[i].amplitude = sinWave[i].pos.y - firstSurface;
			}		
			time ++;
		}


		//if (springType != TITLE) {
		//	if (keys[DIK_B] && !preKeys[DIK_B]) {
		//		springType = TITLE;
		//	}
		//}
		//if (keys[DIK_R] && !preKeys[DIK_R]) {
		//	springType = TITLE;
		//}

		//switch (springType) {
		//case TITLE:
		//	if (keys[DIK_1] && !preKeys[DIK_1]) {
		//		springType = ASIXY;
		//	}
		//	if (keys[DIK_2] && !preKeys[DIK_2]) {
		//		springType = FREE;
		//	}
		//	if (keys[DIK_3] && !preKeys[DIK_3]) {
		//		springType = OBJWHILE;
		//	}
		//	break;
		//case ASIXY:
		//	// key入力
		//	if (keys[DIK_1] && !preKeys[DIK_1]) {
		//		if (!spring.isDapedVibration) {
		//			spring.isDapedVibration = true;
		//		}
		//		else {
		//			spring.isDapedVibration = false;
		//		}
		//	}

		//	// 減衰振動の処理
		//	if (spring.isDapedVibration) {
		//		spring.vel.y *= spring.dampedVibration;
		//	}

		//	// 加速度
		//	spring.a = -spring.k * (spring.pos.y - spring.displacement) / spring.mass;
		//	// 速度
		//	spring.vel.y += spring.a;
		//	// 重力
		//	spring.vel.y += spring.acceleration;
		//	// 位置
		//	spring.pos.y += spring.vel.y;

		//	break;
		//case FREE:

		//	break;
		//case OBJWHILE:

		//	break;
		//}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		for (int i = 0; i < kWavePoint; i ++) {
			Novice::DrawQuad(
				sinWave[i].pos.x, sinWave[i].pos.y,
				sinWave[i].pos.x + sinWave[i].radius, sinWave[i].pos.y,
				sinWave[i].pos.x, sinWave[i].pos.y + sinWave[i].radius,
				sinWave[i].pos.x + sinWave[i].radius, sinWave[i].pos.y + sinWave[i].radius,
				0, 0,
				32, 32,
				whiteRect,
				BLUE
			);
		}

		Novice::ScreenPrintf(0, 0, "nowAmplitude[0]:%f", sinWave[0].amplitude);
		Novice::ScreenPrintf(0, 20, "MaxAmplitude %f", maxAmplitude);
		Novice::ScreenPrintf(0, 40, "T:%f", T);
		Novice::ScreenPrintf(0, 60, "velX:%f", velX);
		Novice::ScreenPrintf(0, 80, "λ:%f", λ);
		Novice::ScreenPrintf(0, 100, "Hz:%f", hz);

		//switch (springType) {
		//case TITLE:

		//	break;
		//case ASIXY:
		//	//spring->Draw();

		//	Novice::DrawEllipse(spring.pos.x, spring.pos.y, spring.radius, spring.radius, 0.0f, WHITE, kFillModeSolid);
		//	// 基準点
		//	Novice::DrawLine(kWindowWidth / 2, 0, kWindowWidth / 2, spring.pos.y, BLACK);

		//	Novice::ScreenPrintf(0, 0, "B:TITLE");
		//	if (spring.isDapedVibration) {
		//		Novice::ScreenPrintf(100, 0, "1:DapedVivration ON");
		//	}
		//	else {
		//		Novice::ScreenPrintf(100, 0, "1:DapedVivration OFF");
		//	}

		//	break;
		//case FREE:

		//	Novice::ScreenPrintf(0, 0, "B:TITLE");
		//	break;
		//case OBJWHILE:

		//	Novice::ScreenPrintf(0, 0, "B:TITLE");
		//	break;
		//}


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
	//delete spring;
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
