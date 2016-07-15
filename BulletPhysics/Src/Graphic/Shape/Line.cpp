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
	lineList.push_back(startPos);
	lineList.push_back(endPos);
	colorList.push_back(color);
	colorList.push_back(color);
}
void Line::Draw(Shader* shader, CAMERA_ID cID){
	if (lineList.size() != 0) {
		HRESULT hr = E_FAIL;
		std::vector<char> fileNameVec;
		char slash = '\\';

		std::vector<VERTEX> vertexVec;

		int count = 0;
		for (auto i : lineList) {
			vertexVec.push_back({
				(D3DXVECTOR3(i.x,i.y,i.z)),
				(D3DXVECTOR3(colorList[count].x,colorList[count].y,colorList[count].z)),
				(D3DXVECTOR2(1, 1)),
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			});
			count++;
		}
		lineList.clear();
		colorList.clear();

		int vertexSize = vertexVec.size();
		// 頂点の実データを設定
		VERTEX* v = new VERTEX[vertexSize];
		for (int i = 0; i < vertexSize; i++)
			v[i] = vertexVec[i];

		// 頂点バッファ
		ID3D11Buffer* VertexBuffer = NULL;

		// 頂点バッファを作成する
		Device::GetInstance().Getd3d11User()->CreateVertexBuffer(&VertexBuffer, v, sizeof(VERTEX)* vertexSize, 0);

		delete(v);

		UINT* index = new UINT[vertexSize];

		for (int i = 0; i < vertexSize; i++)
			index[i] = i;

		// インデックスバッファ
		ID3D11Buffer* IndexBuffer = NULL;

		// インデックスバッファを作成する。
		hr = Device::GetInstance().Getd3d11User()->CreateIndexBuffer(&IndexBuffer, index, sizeof(UINT) * vertexSize, 0);

		delete(index);

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
		Device::GetInstance().Getd3d11User()->SetIndexBuffer(IndexBuffer);
		shader->SetColor("materialColor", &D3DXCOLOR(1, 1, 1, 1));
		IndexBuffer->Release();
		VertexBuffer->Release();

		// プリミティブ タイプおよびデータの順序に関する情報を設定
		//Zの時はSTRIP
		shader->ShaderApply();
		Device::GetInstance().Getd3d11User()->DrawIndexed(vertexSize, 0, 0);
	}
}