//*****************************************************************************
//
// �g�D�[���V�F�[�_�[���� [cekShader.fx]
//
// �R���p�C���͂��Ȃ�
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix rotMatrix;               // ��]�s��
matrix worldMatrix;             // ���[���h�ϊ��s��
matrix viewMatrix;              // �r���[�C���O�ϊ��s��
matrix projectionMatrix;        // �v���W�F�N�V�����ϊ��s��

float3 lightDir = float3(-1.0f, 1.0f, 1.0f);   // ���C�g�����x�N�g��
float4 lightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);    // ���C�g�J���[

float outLineFactor = 0.4f;     // outLine��`�悷�鎞�A���_�x�N�g���Ɩ@���x�N�g�������������q��
float outLineStr = 0.01f;       // outLine�̑������R���g���[�����q

int colorSteps = 2;            // �J���[�̃��x��
float diffuseRange = 0.5f;      // diffuse�J���[�ƃV���h�E�̕�������

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
    // outLine�J���[��ݒ�
    return float4(170.0f / 255.0f, 123.0f / 255.0f, 65.0f / 255.0f, 1.0);
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
    vout.nor = normalize(mul(float4(nor, 1.0), rotMatrix));
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
    // �e�N�X�`���ɂ���ĐF����
    float4 color = tex2D(diffuseSampler, vout.coord);

    // ���C�g�����x�N�g���Ɩ@���̊O�ς��v�Z���̌��ʂ�diffuse�ł�
    // �O�ς̒l���}�C�i�X�Ȃ�΃V���h�E�ɂ���(0)
    float diffuse = max(0, dot(vout.nor.xyz, -lightDir));

    // �Վ� -- �V���h�E�̖��邳�𑝉�
    diffuse = (diffuse + 1) / 2;

    // �F��[0, 1]�ɂ���A�Ȃ��Ȃ��RGB�l�͈̔͂�0.0~1.0
    smoothstep(0, 1, diffuse);

    //
    float toon = floor(diffuse * colorSteps) / colorSteps;

    // 
    diffuse = lerp(diffuse, toon, diffuse);

    // �ŏI�F���o��
    color *= lightColor * diffuse;

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