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

		vertexVec.clear();
		index.clear();
		
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
		// ���_�̎��f�[�^��ݒ�

		// ���_�o�b�t�@
		ID3D11Buffer* VertexBuffer = NULL;

		// ���_�o�b�t�@���쐬����
		Device::GetInstance().Getd3d11User()->CreateVertexBuffer(&VertexBuffer, vertexVec.data(), sizeof(VERTEX)* vertexSize, 0);


		for (int i = 0; i < vertexSize; i++)
			index.push_back(i);

		// �C���f�b�N�X�o�b�t�@
		ID3D11Buffer* IndexBuffer = NULL;

		// �C���f�b�N�X�o�b�t�@���쐬����B
		hr = Device::GetInstance().Getd3d11User()->CreateIndexBuffer(&IndexBuffer, index.data(), sizeof(UINT) * vertexSize, 0);


		Matrix4 ide = RCMatrix4::Identity();
		D3DXMATRIX matWorld = RConvert(&ide);
		// �s����G�t�F�N�g�ɐݒ�
		shader->SetMatrix("g_matW", &matWorld);
		shader->SetMatrix("g_matV", &Device::GetInstance().GetCamera(cID)->returnView());
		shader->SetMatrix("g_matP", &Device::GetInstance().GetCamera(cID)->returnProj());
		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		//Device::GetInstance().Getd3d11User()->SetBlendState(&Device::GetInstance().Getd3d11User()->GetAlignmentBlendDesc(), 1, FALSE);
		Device::GetInstance().Getd3d11User()->SetTopology(D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
		Device::GetInstance().Getd3d11User()->SetVertexBuffer(&VertexBuffer, &stride, &offset);
		Device::GetInstance().Getd3d11User()->SetIndexBuffer(IndexBuffer);
		shader->SetColor("materialColor", &D3DXCOLOR(1, 1, 1, 1));
		IndexBuffer->Release();
		VertexBuffer->Release();

		// �v���~�e�B�u �^�C�v����уf�[�^�̏����Ɋւ������ݒ�
		//Z�̎���STRIP
		shader->ShaderApply();
		Device::GetInstance().Getd3d11User()->DrawIndexed(vertexSize, 0, 0);
	}
}