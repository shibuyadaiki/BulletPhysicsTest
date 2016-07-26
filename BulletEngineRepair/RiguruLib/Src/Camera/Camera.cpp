#include "Camera.h"
#include "../Math/Converter.h"
#include "../Other/Device.h"
#include "../Graphic/Graphic.h"
#include "../Math/V3Calculation.h"
const float CAMERA_ANGLE_SPEED = 0.003f * 60.0f;		// 旋回速度
const float CAMERA_PLAYER_TARGET_HEIGHT = 0.75f;	// プレイヤー座標からどれだけ高い位置を注視点とするか
const float CAMERA_PLAYER_LENGTH = 2.5f;	// プレイヤーとの距離
const float CAMERA_AI_PLAYER_LENGTH = 0.01f;
const float CAMERA_COLLISION_SIZE = 0.2f;	// カメラの当たり判定サイズ

Camera::Camera(CAMERA_ID cID_) :cID(cID_){
	Initialize();
}
Camera::~Camera(){

}

void Camera::Initialize(){
	mCameraParam.AngleH = 0;
	mCameraParam.AngleV = Math::radian(-0);
	mCameraParam.Eye = vector3(0, 0, 0);
	mCameraParam.Target = vector3(0, 0, 0);
	mCameraParam.Up = vector3(0, 1, 0);

}
//ポジションとビューをセット
void Camera::SetCamera(Vector3 cameraPos, Vector3 cameraView,Vector3 cameraUp){
	mCameraParam.Eye = cameraPos;//* Time::DeltaTime;
	mCameraParam.Target = cameraView;
	mCameraParam.Up = cameraUp;//* Time::DeltaTime;
	D3DXMatrixPerspectiveFovLH(&matProj, 3.1415926f / 4.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	// ビュー行列
	D3DXMatrixLookAtLH(&matView,
		&RConvert(&mCameraParam.Eye),
		&RConvert(&mCameraParam.Target),
		&RConvert(&mCameraParam.Up));
}

//ビューのマトリックスを取得
D3DXMATRIX Camera::returnView(){
	return matView;
}
//プロジェクションのマトリックスを取得
D3DXMATRIX Camera::returnProj(){
	return matProj;
}

CAMERA_PARAMETER* Camera::CameraParam(){
	return &mCameraParam;
}