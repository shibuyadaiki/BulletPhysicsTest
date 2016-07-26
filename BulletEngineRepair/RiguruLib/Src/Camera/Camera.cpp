#include "Camera.h"
#include "../Math/Converter.h"
#include "../Other/Device.h"
#include "../Graphic/Graphic.h"
#include "../Math/V3Calculation.h"
const float CAMERA_ANGLE_SPEED = 0.003f * 60.0f;		// ���񑬓x
const float CAMERA_PLAYER_TARGET_HEIGHT = 0.75f;	// �v���C���[���W����ǂꂾ�������ʒu�𒍎��_�Ƃ��邩
const float CAMERA_PLAYER_LENGTH = 2.5f;	// �v���C���[�Ƃ̋���
const float CAMERA_AI_PLAYER_LENGTH = 0.01f;
const float CAMERA_COLLISION_SIZE = 0.2f;	// �J�����̓����蔻��T�C�Y

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
//�|�W�V�����ƃr���[���Z�b�g
void Camera::SetCamera(Vector3 cameraPos, Vector3 cameraView,Vector3 cameraUp){
	mCameraParam.Eye = cameraPos;//* Time::DeltaTime;
	mCameraParam.Target = cameraView;
	mCameraParam.Up = cameraUp;//* Time::DeltaTime;
	D3DXMatrixPerspectiveFovLH(&matProj, 3.1415926f / 4.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	// �r���[�s��
	D3DXMatrixLookAtLH(&matView,
		&RConvert(&mCameraParam.Eye),
		&RConvert(&mCameraParam.Target),
		&RConvert(&mCameraParam.Up));
}

//�r���[�̃}�g���b�N�X���擾
D3DXMATRIX Camera::returnView(){
	return matView;
}
//�v���W�F�N�V�����̃}�g���b�N�X���擾
D3DXMATRIX Camera::returnProj(){
	return matProj;
}

CAMERA_PARAMETER* Camera::CameraParam(){
	return &mCameraParam;
}