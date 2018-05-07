//*****************************************************************************
//
// �g�D�[���V�F�[�_�[���� [cekShader.fx]
//
// �R���p�C���͂��Ȃ�
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "publicValue.fx"
#include "lightingProcess.fx"
#include "outLine.fx"

//*****************************************************************************
//
// �O���[�o���ϐ�
//
//*****************************************************************************
// ���s��W��
matrix boneMatrices[87];

// �����_�����O�I��
int renderType;

// �f�B�t���[�Y�e�N�X�`���T���v���[
// �e�N�X�`��
texture tex;
// �T���v���[
sampler texSampler = sampler_state
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
// ���f�����_�V�F�[�_�[����
//
//*****************************************************************************
outputVS modelVS(inputVSWithBone iVS)
{
    // �߂�l��������
    outputVS oVS = (outputVS) 0;

    //// ���ɂ���Ē��_�ʒu���v�Z
    //matrix boneTrans = boneMatrices[boneID[0]] * weight[0];
    //boneTrans += boneMatrices[boneID[1]] * weight[1];
    //boneTrans += boneMatrices[boneID[2]] * weight[2];
    //boneTrans += boneMatrices[boneID[3]] * weight[3];

    //// ���_�ϊ�
    //float4 blendPos = mul(boneTrans, float4(pos, 1.0));
    //oVS.pos = mul(mul(mul(blendPos, worldMatrix), viewMatrix), projectionMatrix);
    //// �@���ύX
    //oVS.nor = normalize(mul(float4(nor, 1.0), rotMatrix));

    // ���_�ϊ�
    oVS.worldPos = mul(float4(iVS.pos, 1.0), worldMatrix);
    oVS.pos = mul(mul(oVS.worldPos, viewMatrix), projectionMatrix);
    // �@���ύX
    oVS.nor = normalize(mul(float4(iVS.nor, 1.0), rotMatrix));
    // UV���W�ύX
    oVS.coord = iVS.coord;

    return oVS;
}

//*****************************************************************************
//
// ���f���s�N�Z���V�F�[�_�[����
//
//*****************************************************************************
float4 modelPS(outputVS oVS) : COLOR
{
    float4 ambient;
    float4 diffuse;
    float4 specular;

    float4 lightDiffuse;

    // �e�N�X�`���ɂ���ĐF����
    float4 texColor = tex2D(texSampler, oVS.coord);
    // �@���̊e���ʂ�F�Ƃ��ďo��
    float4 normal = float4(oVS.nor.x, oVS.nor.y, oVS.nor.z, 1.0f);

    if (lightType == 0)
    {
        // �w�������C�g
        lightDiffuse = diffuseProcess(oVS.worldPos, oVS.nor) * lightColor;
        diffuse = diffuseProcess(oVS.worldPos, oVS.nor) * texColor;
    }
    else if (lightType == 1)
    {
        // �|�C���g���C�g
        lightDiffuse = attenuationProcess(oVS.worldPos) * lightColor;
        diffuse = attenuationProcess(oVS.worldPos) * texColor;

    }
    else if (lightType == 2)
    {
        // �t���b�V�����C�g

    }

    // �`����@�̂�I��
    if(renderType == 0)
    {
        // RT_DIFFUSE
        return lightDiffuse;
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
    return diffuse;
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