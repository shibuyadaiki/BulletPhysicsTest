#pragma once
#include "../Other/DX11User.h"
#include "MathUtility.h"
#include "MatrixUtility.h"
#include "Vector2Utility.h"
#include "Vector3Utility.h"
#include "Quaternion.h"
#include <bullet/LinearMath/btIDebugDraw.h>  

	//D3DXVECTOR2に変換
D3DXVECTOR2 RConvert(Vector2* v);
//D3DXVECTOR3に変換
D3DXVECTOR3 RConvert(Vector3* v);
//D3DXMATRIXに変換
D3DXMATRIX RConvert(Matrix4* m);
//D3DXQUATERNIONに変換
D3DXQUATERNION RConvert(Quaternion* q);

//Vector2に変換
Vector2 RConvert(D3DXVECTOR2* v);
//Vector3に変換
Vector3 RConvert(D3DXVECTOR3* v);
//Matrix4に変換
Matrix4 RConvert(D3DXMATRIX* m);
//Quaternionに変換
Quaternion RConvert(D3DXQUATERNION* q);

//座標変換  
Vector3 RConvertB(const btVector3 &inv);
//座標変換  
btVector3 RConvertB(const Vector3 &inv);
//座標変換(左手座標系に変換)
Vector3 RConvertBR(const btVector3 &inv);
//Quaternionに変換
Quaternion RConvertB(const btQuaternion& q);
//D3DXQUATERNIONに変換
btQuaternion RConvertB(const Quaternion& q);