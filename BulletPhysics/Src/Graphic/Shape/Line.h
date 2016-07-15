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
	// ���_��`
	struct VERTEX
	{
		// ���_���W
		D3DXVECTOR3   pos;
		// �@��
		D3DXVECTOR3   normal;
		// �e�N�Z��
		D3DXVECTOR2 texel;

		UINT boneIndex[4];
		UINT weight[4];
	};

	std::vector<int> indexSize;
	LoadTexture lt;
	std::vector<Vector3> lineList;
	std::vector<Vector3> colorList;
};