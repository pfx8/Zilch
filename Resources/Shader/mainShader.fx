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
#include "outLineProcess.fx"

//*****************************************************************************
//
// �O���[�o���ϐ�
//
//*****************************************************************************
// ���s��W��
matrix boneMatrices[87];

// �����_�����O�I��
int renderingMode;

//*****************************************************************************
//
// �T���v���[
//
//*****************************************************************************
// �f�B�t���[�Y�e�N�X�`��
texture tex;
// �f�B�t���[�Y�e�N�X�`���T���v���[
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
    //float4 diffuse;
    //float4 specular;
    float4 finColor;

    float4 ambient = float4(0.3, 0.3, 0.3, 1.0);

    // ���C�g�x�N�g�����v�Z
    float4 lightDir = normalize(float4(lightPos, 1.0f) - oVS.worldPos);
    // �r���[�x�N�g��
    float4 viewDir = float4(cameraPos, 1.0) - oVS.worldPos;
    //
    float4 halfDir = normalize(lightDir + viewDir);

    float4 specular = float4(0.0, 1.0, 0.0, 1.0);

    // �X�y�L�����[�v�Z
    float spec = max(0, dot(float4(oVS.nor, 1.0f), halfDir));
    spec = pow(spec, shininess);
    float w = fwidth(spec) * 2.0;
    if (spec < 0.5 + w)
    {
        spec = lerp(0, 1, smoothstep(0.5 - w, 0.5 + w, spec));
    }
    else
    {
        spec = 1;
    }

    // ���C�g�ɂ���ăf�B�t���[�Y���v�Z
    float diff = diffuseByLightType(lightDir, oVS.nor, oVS.worldPos);

    // �e�N�X�`���ɂ���ĐF����
    float4 texColor = tex2D(texSampler, oVS.coord);
    // �@���̊e���ʂ�F�Ƃ��ďo��
    float4 normal = float4(oVS.nor.x, oVS.nor.y, oVS.nor.z, 1.0f);
    // �f�B�t���[�Y
    float4 diffuse = diff * lightColor * texColor;
    // �X�y�L�����[
    //float4 specular = spec * lightColor * texColor;

    // �`����@�̂�I��
    if(renderingMode == 0)
    {
         // RM_TEXTURE
        return texColor;
    }
    else if (renderingMode == 1)
    {
        // RM_DIFFUSE
        //diffuse = diff * lightColor;
        //diffuse.w = 1.0;
        //return diffuse;

        float lightStrength = 0.1;
        float4 ambient1 = lightStrength * lightColor;

        float4 lightDir = normalize(float4(lightPos, 1.0) - oVS.worldPos);
        float diff = max(dot(float4(oVS.nor, 1.0), lightDir), 0.0);
        float4 diffuse1 = diff * lightColor;

        float4 cameraDir = normalize(float4(cameraPos, 1.0) - oVS.worldPos);
        float4 reflectDir = reflect(-lightDir, float4(oVS.nor, 1.0));
        float specular1 = pow(max(dot(cameraDir, reflectDir), 0.0), 128);

        finColor = (ambient + diffuse1 + specular1) * float4(1.0, 0.0, 0.0, 1.0);
        finColor.w = 1.0;

        return finColor;
    }
    else if (renderingMode == 2)
    {
        // RM_SPECULAR
        return specular;
    }
    else if(renderingMode == 3)
    {
        // RM_NORMAL
        return normal;
    }

    // RT_SHADING -- �V�F�[�f�B���O
    float4 fin = diffuse /*+ specular*/ + ambient;

    // �ڃe�N�X�`�������𓧖�
    if(texColor.w != 0.0)
    {
        fin.w = 1.0;
    }

    return fin;
}

//*****************************************************************************
//
// �V�F�[�_�[�e�N�j�b�N
//
// FX�t�@�C�����O�Ɠ���
//
//*****************************************************************************
technique mainShader
{
    // outLine
    pass P0
    {
        // �A���t�@�u�����e�B���O
        AlphaBlendEnable = FALSE;
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
        AlphaBlendEnable = TRUE;
        // �ړ�������
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        // �}���`�E�T���v�����O�̐ݒ�
        MultiSampleAntialias = TRUE;
        // Z�o�b�t�@
        ZEnable = TRUE;
        // �w�ʃJ�����O
        CullMode = CCW; // �|���S���̕\��\��
        
        VertexShader = compile vs_3_0 modelVS();
        PixelShader = compile ps_3_0 modelPS();
    }
}