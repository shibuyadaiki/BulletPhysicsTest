#include "Line.h"
#include "../../Other/Device.h"
#include <iostream>
#include <fstream>
#include "../Rgr/RgrLoader.h"
#include "../../Math/MathUtility.h"
#include "../../Math/Converter.h"
using namespace std;


Line::Line(){
}

Line::~Line(){
}

void Line::Release(){
}

HRESULT Line::Load(){
	return S_OK;
}
void Line::SetLine(const Vector3& startPos, const Vector3& endPos,const Vector3& color) {
	vertexVec.push_back({
		(D3DXVECTOR3(startPos.x,startPos.y,startPos.z)),
		(D3DXVECTOR3(color.x,color.y,color.z)),
		(D3DXVECTOR2(1, 1)),
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	});
	vertexVec.push_back({
		(D3DXVECTOR3(endPos.x,endPos.y,endPos.z)),
		(D3DXVECTOR3(color.x,color.y,color.z)),
		(D3DXVECTOR2(1, 1)),
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	});
}
void Line::Draw(Shader* shader, CAMERA_ID cID){
	if (vertexVec.size() != 0) {
		HRESULT hr = E_FAIL;

		int vertexSize = vertexVec.size();
		// 頂点の実データを設定

		// 頂点バッファ
		ID3D11Buffer* VertexBuffer = NULL;

		// 頂点バッファを作成する
		Device::GetInstance().Getd3d11User()->CreateVertexBuffer(&VertexBuffer, vertexVec.data(), sizeof(VERTEX)* vertexSize, 0);

		Matrix4 ide = RCMatrix4::Identity();
		D3DXMATRIX matWorld = RConvert(&ide);
		// 行列をエフェクトに設定
		shader->SetMatrix("g_matW", &matWorld);
		shader->SetMatrix("g_matV", &Device::GetInstance().GetCamera(cID)->returnView());
		shader->SetMatrix("g_matP", &Device::GetInstance().GetCamera(cID)->returnProj());
		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		//Device::GetInstance().Getd3d11User()->SetBlendState(&Device::GetInstance().Getd3d11User()->GetAlignmentBlendDesc(), 1, FALSE);
		Device::GetInstance().Getd3d11User()->SetTopology(D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
		Device::GetInstance().Getd3d11User()->SetVertexBuffer(&VertexBuffer, &stride, &offset);
		shader->SetColor("materialColor", &D3DXCOLOR(1, 1, 1, 1));

		vertexVec.clear();
		VertexBuffer->Release();

		// プリミティブ タイプおよびデータの順序に関する情報を設定
		//Zの時はSTRIP
		shader->ShaderApply();
		Device::GetInstance().Getd3d11User()->DrawAuto(vertexSize,0);
	}
}