//#include "Spring.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
//#include "Novice.h"
//#include "Common.h"
//
//Spring::Spring() {
//	pos_.x = (float)kWindowWidth / 2;
//	pos_.y = (float)kWindowHeight / 2 - 100;
//	speed_.x = 0.0f;
//	speed_.y = 0.0f;
//	radius_ = 16.0f;
//	mass_ = 100.0f;
//	acceleration_ = 0.8f;
//	a_ = 0.0f;
//	// 力
//	F_ = mass_ * acceleration_;
//	// ばね定数
//	k_ = 10.0f;
//
//	// 根本
//	startSpring_.x = (float)kWindowWidth / 2;
//	startSpring_.y = (float)kWindowHeight / 2;
//
//	// ばねの自然長からの変位
//	dy_ = 0;
//}
//Spring::~Spring() {
//
//}
//
//void Spring::Initialize() {
//	pos_.x = (float)kWindowWidth / 2;
//	pos_.y = (float)kWindowHeight / 2;
//	speed_.x = 0.0f;
//	speed_.y = 0.0f;
//	radius_ = 16.0f;
//	mass_ = 10.0f;
//	acceleration_ = 0.8f;
//	// 力
//	F_ = mass_ * acceleration_;
//	// ばね定数
//	k_ = 10.0f;
//	// ばねの自然長からの変位
//	dy_ = 0;
//
//	startSpring_.x = (float)kWindowWidth / 2;
//	startSpring_.y = (float)kWindowHeight / 2;
//}
//void Spring::Update() {
//	// 変位
//	//dy_ = (startSpring_.y - pos_.y);
//	// ばねの力
//	F_ = -(k_ * dy_);
//
//	// 質量
//	float m = k_ * dy_ / acceleration_;
//
//	// 
//	dy_ = m * acceleration_ / k_;
//
//	//speed_.y += a_;
//	//pos_.y += speed_.y;
//
//
//}
//
//void Spring::Draw() {
//	// ばねの先端
//	Novice::DrawEllipse(pos_.x,pos_.y, radius_, radius_, 0.0f, BLUE, kFillModeSolid);
//	// 基準点
//	Novice::DrawLine(0, startSpring_.y, 1280, startSpring_.y, WHITE);
//
//	Novice::ScreenPrintf(0, 0, "%f", dy_);
//	Novice::ScreenPrintf(0, 20, "%f", pos_.y);
//	Novice::ScreenPrintf(0, 40, "%f", F_);
//}