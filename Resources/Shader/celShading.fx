//*****************************************************************************
//
// �g�D�[���V�F�[�_�[���� [cekShader.fx]
//
// �R���p�C���͂��Ȃ�
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix rotMatrix;         // ��]�s��
matrix worldMatrix;       // ���[���h�ϊ��s��
matrix viewMatrix;        // �r���[�C���O�ϊ��s��
matrix projectionMatrix;  // �v���W�F�N�V�����ϊ��s��

matrix boneMatrices[87];  // ���s��W��

float3 lightPos;   // ���C�g�ʒu
float4 lightColor; // ���C�g�J���[
// ���C�g�����v���p�e�B
float lightConstant;
float lightLinear;
float lightQuadratic;

float outLineFactor = 0.1f;  // outLine��`�悷�鎞�A���_�x�N�g���Ɩ@���x�N�g�������������q��
float outLineStr = 0.01f;    // outLine�̑������R���g���[�����q

float3 amibent;   // ����
float3 diffuse;   // �g�U���ˌ�
float3 specular;  // ���ʔ��ˌ�
float  shininess; // ����

int renderType;   // �����_�����O�I��

texture tex;          // �e�N�X�`��
sampler texSampler =  // �T���v���[
sampler_state
{
    Texture = <tex>;
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
    float3 nor : NORMAL0;
    float2 coord : TEXCOORD0;
    float4 worldPos : TEXCOORD1;
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
    vout.worldPos = mul(float4(outLinePos, 1.0), worldMatrix);
    vout.pos = mul(mul(vout.worldPos, viewMatrix), projectionMatrix);

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
    return float4(0.0f, 0.0f, 0.0f, 1.0f);
}

//*****************************************************************************
//
// ���f�����_�V�F�[�_�[����
//
//*****************************************************************************
VSout modelVS(float3 pos : POSITION0,
              float3 nor : NORMAL0,
              float2 coord : TEXCOORD0,
              float4 weight : BLENDWEIGHT,
              float4 boneID : BLENDINDICES)
{
    // �߂�l��������
    VSout vout = (VSout) 0;

    //// ���ɂ���Ē��_�ʒu���v�Z
    //matrix boneTrans = boneMatrices[boneID[0]] * weight[0];
    //boneTrans += boneMatrices[boneID[1]] * weight[1];
    //boneTrans += boneMatrices[boneID[2]] * weight[2];
    //boneTrans += boneMatrices[boneID[3]] * weight[3];

    //// ���_�ϊ�
    //float4 blendPos = mul(boneTrans, float4(pos, 1.0));
    //vout.pos = mul(mul(mul(blendPos, worldMatrix), viewMatrix), projectionMatrix);
    //// �@���ύX
    //vout.nor = normalize(mul(float4(nor, 1.0), rotMatrix));

    // ���_�ϊ�
    vout.worldPos = mul(float4(pos, 1.0), worldMatrix);
    vout.pos = mul(mul(vout.worldPos, viewMatrix), projectionMatrix);
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
    float4 texColor = tex2D(texSampler, vout.coord);
    float4 lightDir = normalize(float4(lightPos, 1.0f) - vout.worldPos);

    float4 normal = float4(vout.nor.x, vout.nor.y, vout.nor.z, 1.0f);

    // ���C�g�����x�N�g���Ɩ@���̊O�ς��v�Z���̌��ʂ�diffuse�ł�
    // �O�ς̒l���}�C�i�X�Ȃ�΃V���h�E�ɂ���(0)
    // max(x, y) x��y �̂����̑傫�����̒l��I���B�}�C�i�X�l��h��
    float diffuse = max(0, dot(float4(vout.nor, 1.0f), -lightDir));
    // �V���h�E�ƐF�𕪗�
    //if (diffuse < 0.05f)
    //{
    //    //�@diffuse
    //    texColor *= 1.0f;
    //}
    //else
    //{
    //    // �V���h�E
    //    texColor *= 0.6f;
    //}

    // �����l���v�Z
    float distance = length(float4(lightPos, 1.0f) - vout.worldPos);
    float attenuation = 1.0f / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));
    float4 attColor = attenuation * lightColor;
    texColor *= attenuation;

    // �`����@�̂�I��
    if(renderType == 0)
    {
        // RT_DIFFUSE
        return float4(attenuation, attenuation, attenuation, attenuation);
    }
    else if(renderType == 1)
    {
        // RT_NORMAL
        return normal;
    }
    else if(renderType == 2)
    {
        // RT_TEXTURE
        return texColor;
    }

    // RT_SHADING -- �f�t�H���g
    return texColor;
}

//*****************************************************************************
//
// �V�F�[�_�[�e�N�j�b�N
//
// FX�t�@�C�����O�Ɠ���
//
//*****************************************************************************
technique celShading
{
    // outLine
    pass P0
    {
        // �A���t�@�u�����e�B���O
        AlphaBlendEnable = FALSE;
        // �t���b�g�V�F�[�f�B���O
        ShadeMode = GOURAUD;
        // �}���`�E�T���v�����O�̐ݒ�
        MultiSampleAntialias = TRUE;
        // Z�o�b�t�@
        ZEnable = TRUE;
        // �w�ʃJ�����O
        CullMode = CW; // �|���S���̗���\��
        
        VertexShader = compile vs_3_0 outLineVS();
        PixelShader = compile ps_3_0 outLinePS();
    }
    
    // ���f��
    pass P1
    {
        // �A���t�@�u�����e�B���O
        AlphaBlendEnable = FALSE;
        // �}���`�E�T���v�����O�̐ݒ�
        MultiSampleAntialias = TRUE;
        // �t���b�g�V�F�[�f�B���O
        ShadeMode = GOURAUD;
        // Z�o�b�t�@
        ZEnable = TRUE;
        // �w�ʃJ�����O
        CullMode = CCW; // �|���S���̕\��\��
        
        VertexShader = compile vs_3_0 modelVS();
        PixelShader = compile ps_3_0 modelPS();
    }
}