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
    // �e�N�X�`���ɂ���ĐF����
    float4 texColor = tex2D(texSampler, oVS.coord);
    float4 lightDir = normalize(float4(lightPos, 1.0f) - oVS.worldPos);

    float4 normal = float4(oVS.nor.x, oVS.nor.y, oVS.nor.z, 1.0f);

    // ���C�g�����x�N�g���Ɩ@���̊O�ς��v�Z���̌��ʂ�diffuse�ł�
    // �O�ς̒l���}�C�i�X�Ȃ�΃V���h�E�ɂ���(0)
    // max(x, y) x��y �̂����̑傫�����̒l��I���B�}�C�i�X�l��h��
    float diffuse = max(0, dot(float4(oVS.nor, 1.0f), -lightDir));
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
    float distance = length(float4(lightPos, 1.0f) - oVS.worldPos);
    float attenuation = 1.0f / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));
    float4 attColor = attenuation * lightColor;
    float4 texColorFin = texColor * attenuation;

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
    return texColorFin;
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