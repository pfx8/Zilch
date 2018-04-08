//*****************************************************************************
//
// �e�X�g�V�F�[�_�[���� [test.fx]
//
// �R���p�C���͂��Ȃ�
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
float4 worldMatrix;            // ���[���h�ϊ��s��
float4 viewMatrix;              // �r���[�C���O�ϊ��s��
float4 projectionMatrix;    // �v���W�F�N�V�����ϊ��s��

texture diffuse;                                   // �e�N�X�`��
sampler diffuseSampler =                // �T���v���[
sampler_state
{
    Texture = <diffuse>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

struct VSout
{
    float4 pos : POSITION0;
    float4 nor : NORMAL0;
    float2 coord : TEXCOORD0;
};

//*****************************************************************************
//
// ���_�V�F�[�_�[����
//
//*****************************************************************************
VSout vertexShader(float3 pos : POSITION,
             float3 nor : NORMAL,
             float2 coord : TEXCOORD)
{
    // �߂�l��������
    VSout vout = (VSout) 0;

    // ���_�ύX
    float4 vtx = mul(float4(pos, 1.0), worldMatrix);
    vtx = mul(vtx, viewMatrix);
    vtx = mul(vtx, projectionMatrix);
    vout.pos = vtx;

    // �@���ύX
    vout.nor = mul(float4(nor, 1.0), worldMatrix);

    // UV���W�ύX
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// �s�N�Z���V�F�[�_�[����
//
//*****************************************************************************
float4 pixelShader(VSout vout) : COLOR
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);

    // �J���[���v�Z
    color = float4(1.0, 0.0, 0.0, 1.0);
    //color = tex2D(diffuseSampler, vout.coord);

    return color;
}

technique defaultRender
{
    pass P0
    {
        VertexShader = compile vs_3_0 vertexShader();
        PixelShader = compile ps_3_0 pixelShader();
    }
}