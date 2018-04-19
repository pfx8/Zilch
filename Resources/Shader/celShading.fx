//*****************************************************************************
//
// �g�D�[���V�F�[�_�[���� [cekShader.fx]
//
// �R���p�C���͂��Ȃ�
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix worldMatrix;             // ���[���h�ϊ��s��
matrix viewMatrix;              // �r���[�C���O�ϊ��s��
matrix projectionMatrix;        // �v���W�F�N�V�����ϊ��s��

float3 lightDir = float3(-1.0f, 1.0f, 1.0f);   // ���C�g�����x�N�g��

float outLineFactor = 0.4;        // outLine��`�悷�鎞�A���_�x�N�g���Ɩ@���x�N�g�������������q��
float outLineStr = 0.01;          // outLine�̑������R���g���[�����q

texture diffuse;               // �e�N�X�`��
sampler diffuseSampler =       // �T���v���[
sampler_state
{
    Texture = <diffuse>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

//*****************************************************************************
//
// �v���g�^�C�v�錾
//
//*****************************************************************************
struct VSout
{
    float4 pos : POSITION0;
    float4 nor : NORMAL0;
    float2 coord : TEXCOORD0;
};

//*****************************************************************************
//
// outLine���_�V�F�[�_�[����
//
//*****************************************************************************
VSout outLineVS(float3 pos : POSITION0,
               float3 nor : NORMAL0,
               float2 coord : TEXCOORD0)
{
    // �߂�l��������
    VSout vout = (VSout) 0;

    // outLine�����x�N�g�����v�Z
    // �܂��͒��_�̕����x�N�g�����v�Z
    float3 outLineDir = normalize(pos);
    // ���_�̕����x�N�g���Ɩ@���x�N�g���̊O�ς��v�Z
    // 
    float D = dot(outLineDir, nor);
    outLineDir *= sign(D);
    // outLine�̍ŏI�������v�Z
    outLineDir = outLineDir * outLineFactor + nor * (1 - outLineFactor);

    // ���_ + outLine�����x�N�g * outLine�������� = outLine���_�̏ꏊ
    float3 outLinePos = pos + outLineDir * outLineStr;

    // ���_�ϊ�
    vout.pos = mul(mul(mul(float4(outLinePos, 1.0), worldMatrix), viewMatrix), projectionMatrix);
    // �@���ύX
    vout.nor = mul(float4(nor, 1.0), worldMatrix);
    // UV���W�ύX
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// outLine�s�N�Z���V�F�[�_�[����
//
//*****************************************************************************
float4 outLinePS(VSout vout) : COLOR
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);

    // �J���[�����ɂ���
    color = float4(0.0, 0.0, 0.0, 1.0);

    return color;
}

//*****************************************************************************
//
// ���f�����_�V�F�[�_�[����
//
//*****************************************************************************
VSout modelVS(float3 pos : POSITION0,
             float3 nor : NORMAL0,
             float2 coord : TEXCOORD0)
{
    // �߂�l��������
    VSout vout = (VSout) 0;

    // ���_�ϊ�
    vout.pos = mul(mul(mul(float4(pos, 1.0), worldMatrix), viewMatrix), projectionMatrix);
    // �@���ύX
    vout.nor = mul(float4(nor, 1.0), worldMatrix);
    // UV���W�ύX
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// ���f���s�N�Z���V�F�[�_�[����
//
//*****************************************************************************
float4 modelPS(VSout vout) : COLOR
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);

    // �e�N�X�`���ɂ���ĐF����
    color = tex2D(diffuseSampler, vout.coord);

    return color;
}

//*****************************************************************************
//
// �V�F�[�_�[�e�N�j�b�N
//
//*****************************************************************************
technique celShading
{
    // outLine
    pass P0
    {
        // Z�o�b�t�@
        ZEnable = TRUE;
        // �w�ʃJ�����O
        CullMode = CW;     // �|���S���̗���\��
        
        VertexShader = compile vs_3_0 outLineVS();
        PixelShader = compile ps_3_0 outLinePS();
    }
    
    // ���f��
    pass P1
    {
        // �t���b�g�V�F�[�f�B���O
        ShadeMode = FLAT;
        // Z�o�b�t�@
        ZEnable = TRUE;
        // �w�ʃJ�����O
        CullMode = CCW; // �|���S���̕\��\��
        // �A���t�@�u�����e�B���O
        AlphaBlendEnable = TRUE;
        
        VertexShader = compile vs_3_0 modelVS();
        PixelShader = compile ps_3_0 modelPS();
    }
}