#pragma once
#include "../Other/DX11User.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4.h"

enum CAMERA_ID;
#include <memory>

// �J�����̃p�����[�^�\����
struct CAMERA_PARAMETER
{
	float		AngleH;				// �����p�x
	float		AngleV;				// �����p�x
	float		AngleHSub;			//�����p�x�̍���
	float		AngleVSub;			//�����p�x�̍���
	Vector3		Eye;				// �J�������W
	Vector3		Target;				// �����_���W
	Vector3		Up;					// �����
	Vector3		InputAngle;			// ����
};

class Camera{
public:
	Camera(CAMERA_ID cID_);
	~Camera();
	void Initialize();
	//�|�W�V�����ƃr���[���Z�b�g
	void SetCamera(Vector3 cameraPos, Vector3 cameraView,Vector3 cameraUp = vector3(0,1,0));
	//�r���[�̃}�g���b�N�X���擾
	D3DXMATRIX returnView();
	//�v���W�F�N�V�����̃}�g���b�N�X���擾
	D3DXMATRIX returnProj();
	CAMERA_PARAMETER* CameraParam();
private:
	D3DXMATRIX matView, matProj;
	CAMERA_PARAMETER mCameraParam;
	CAMERA_ID cID;
};