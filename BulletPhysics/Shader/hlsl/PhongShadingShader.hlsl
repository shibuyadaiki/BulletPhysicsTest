matrix g_matW;
matrix g_matV;
matrix g_matP;

/*====���_�V�F�[�_�[�Ŏg�p====**/
float3 g_LightPos;	//���C�g�̍��W
float3 g_EyePos;	//�J�����̍��W

/*====�s�N�Z���V�F�[�_�[�Ŏg�p====**/
float4 g_AmbientLightColor;		//���̊�b�F
float4 g_DiffuseLightColor;		//���̊g�U���ːF
float4 g_SpecularLightColor;	//���̋��ʔ��ːF

float4 g_MaterialAmbient;		//���̂̎���b�F
float4 g_MaterialDiffuse;		//���̂̎��g�U���ːF
float4 g_MaterialSpecular;		//���̂̎����ʔ��ːF

float  g_SpecularPower = 100.0f; //���ʔ��˂̋��x
float  g_SpecularMin = 0.0f;     //���ʔ��˔͈͒l ��{0��OK

// �e�N�X�`���[
Texture2D g_Tex;

// �T���v���[�X�e�[�g
SamplerState  g_Sampler;

float4 g_vecLight;

float4 materialColor;

float4x4 boneMatrix[256];
float4x4 otherBoneMatrix[256];

float4 blendLevel;
// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS_IN
{
	float4 pos   : POSITION;   // ���_���W
	float3 normal : NORMAL;
	float2 texel : TEXCOORD;   // �e�N�Z��
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS_OUT
{
	float4 pos    : SV_POSITION;
	float3 normal : NORMAL;
	float2 texel  : TEXCOORD0;
	float3 L	  : TEXCOORD1;	//���_���W���烉�C�g���W�ւ̕���
	float3 V	  : TEXCOORD2;	//���_���W���王�_���W�ւ̕���
};

//���_�V�F�[�_�[�Q�t�H���V�F�[�f�B���O
VS_OUT VS_Main(VS_IN In)
{
	VS_OUT Out;
	Out = (VS_OUT)0;

	float4 localPos = In.pos;
		float4 W = mul(localPos, g_matW);	//���[���h�ϊ�
		float4 WV = mul(W, g_matV);			//�r���[�ϊ�
		float4 WVP = mul(WV, g_matP);		//�ˉe�ϊ�

		Out.pos = WVP;
	Out.normal = mul(In.normal, (float3x3)g_matW);
	Out.texel = float2(In.texel.x, 1 - In.texel.y);
	Out.L = g_LightPos - W;
	Out.V = g_EyePos - W;

	return Out;
}

//�s�N�Z���V�F�[�_�Q�t�H���V�F�[�f�B���O
float4 PS_Texture_Phong(VS_OUT In) : SV_TARGET
{
	float3 L = normalize(In.L);
	float3 V = normalize(In.V);
	float3 H = normalize(L + V);
	float3 N = normalize(In.normal);

	float4 baseColor = g_Tex.Sample(g_Sampler, In.texel);
	//�g�U���ˋ��x���v�Z����
	float diffuse = max(dot(N, L), 0.0f);
	//���ʔ��ˋ��x���v�Z����
	float specular = pow(max(dot(N, H), g_SpecularMin), g_SpecularPower);

	float4 totalAmbient = g_MaterialAmbient * g_AmbientLightColor;
		float4 totalDiffuse = g_MaterialDiffuse * g_DiffuseLightColor * diffuse;
		float4 totalSpecular = g_MaterialSpecular * g_SpecularLightColor * specular;

		float4 Out = totalAmbient + totalDiffuse + totalSpecular;
		Out.a = baseColor.a * g_MaterialDiffuse;
	return Out;
}

//�s�N�Z���V�F�[�_�Q�t�H���V�F�[�f�B���O���e�N�X�`��
float4 PS_Texture_PhongTex(VS_OUT In) : SV_TARGET
{
	float3 L = normalize(In.L);
	float3 V = normalize(In.V);
	float3 H = normalize(L + V);
	float3 N = normalize(In.normal);

	float4 baseColor = g_Tex.Sample(g_Sampler, In.texel);
	////�g�U���ˋ��x���v�Z����
	float diffuse = max(dot(N, L), 0.0f);
	////���ʔ��ˋ��x���v�Z����
	float specular = pow(max(dot(N, H), g_SpecularMin), g_SpecularPower);

	float3 totalAmbient = baseColor  * g_MaterialAmbient * g_AmbientLightColor;
	float3 totalDiffuse = baseColor.rgb  * g_MaterialDiffuse * g_DiffuseLightColor * diffuse;
	float3 totalSpecular = g_MaterialSpecular * g_SpecularLightColor * specular;

	float3 totalColor = totalAmbient + totalDiffuse + totalSpecular;
	float4 Out = float4(totalColor, baseColor.a);
	return Out;
}

// �G���g���[�|�C���g�ƃo�[�W�������w�肷��
technique11 TShader
{
	//�t�H���V�F�[�f�B���O
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS_Main()));
		SetGeometryShader(NULL);
		SetHullShader(NULL);
		SetDomainShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS_Texture_Phong()));
		SetComputeShader(NULL);
	}
	//�t�H���V�F�[�f�B���O���e�N�X�`��
	pass P1
	{
		SetVertexShader(CompileShader(vs_5_0, VS_Main()));
		SetGeometryShader(NULL);
		SetHullShader(NULL);
		SetDomainShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS_Texture_PhongTex()));
		SetComputeShader(NULL);
	}
}