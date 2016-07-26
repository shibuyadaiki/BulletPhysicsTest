#pragma once
#include "../../Other/DX11User.h"
#include  "../../Other/D3D11User.h"
#include "../Shader/Shader.h"
#include "../Shader/LoadTexture.h"


class Line{
public:
	Line();
	~Line();
	void Release();
	HRESULT Load(); 
	void SetLine(const Vector3& startPos, const Vector3& endPos , const Vector3& color = vector3(0,0,0));
	void Draw(Shader* shader,CAMERA_ID cID);
private:
	// 頂点定義
	struct VERTEX
	{
		// 頂点座標
		D3DXVECTOR3   pos;
		// 法線
		D3DXVECTOR3   normal;
		// テクセル
		D3DXVECTOR2 texel;

		UINT boneIndex[4];
		UINT weight[4];
	};

	LoadTexture lt;
	std::vector<VERTEX> vertexVec;
};