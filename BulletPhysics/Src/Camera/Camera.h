#pragma once
#include "../Other/DX11User.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4.h"

enum CAMERA_ID;
#include <memory>

// カメラのパラメータ構造体
struct CAMERA_PARAMETER
{
	float		AngleH;				// 水平角度
	float		AngleV;				// 垂直角度
	float		AngleHSub;			//水平角度の差分
	float		AngleVSub;			//水平角度の差分
	Vector3		Eye;				// カメラ座標
	Vector3		Target;				// 注視点座標
	Vector3		Up;					// 上方向
	Vector3		InputAngle;			// 入力
};

class Camera{
public:
	Camera(CAMERA_ID cID_);
	~Camera();
	void Initialize();
	//ポジションとビューをセット
	void SetCamera(Vector3 cameraPos, Vector3 cameraView,Vector3 cameraUp = vector3(0,1,0));
	//ビューのマトリックスを取得
	D3DXMATRIX returnView();
	//プロジェクションのマトリックスを取得
	D3DXMATRIX returnProj();
	CAMERA_PARAMETER* CameraParam();
private:
	D3DXMATRIX matView, matProj;
	CAMERA_PARAMETER mCameraParam;
	CAMERA_ID cID;
};