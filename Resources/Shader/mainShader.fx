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
// �e�N�X�`���ƃT���v���[
//
//*****************************************************************************
// �f�B�t���[�Y�}�b�v
texture diffuseMap;
sampler diffuseMapSampler = sampler_state
{
    Texture = <diffuseMap>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

// �m�[�}���}�b�v
texture heightMap;
sampler heightMapSampler = sampler_state
{
    Texture = <heightMap>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

// �X�y�L�����[�}�b�v
texture specularMap;
sampler specularMapSampler = sampler_state
{
    Texture = <specularMap>;
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

    // TBN�s��v�Z
    float3 T = mul(float4(iVS.tan, 0.0), worldMatrix).rgb;
    T = normalize(T);
    float3 N = mul(float4(iVS.tan, 0.0), worldMatrix).rgb;
    N = normalize(N);

    T = normalize(T - dot(T, N) * N);
    float3 B = cross(T, N);
    float3x3 TBN = float3x3(T, B, N);

    // ���_�ϊ�
    oVS.worldPos = mul(float4(iVS.pos, 1.0), worldMatrix);
    oVS.pos = mul(mul(oVS.worldPos, viewMatrix), projectionMatrix);
    // �@���ύX
    oVS.nor = normalize(mul(float4(iVS.nor, 1.0), norMatrix));
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
    // ��{�ϐ���p�ӂ���
    float3 ambient;
    float3 specular;
    float3 diffuse;
    float4 finColor;

    float4 lightDir = normalize(float4(lightPos, 1.0f) - oVS.worldPos);
    float4 cameraDir = float4(cameraPos, 1.0) - oVS.worldPos;
    float4 normalColor = float4(oVS.nor.x, oVS.nor.y, oVS.nor.z, 1.0f);

    // �}�b�v�e�N�X�`����������擾
    float4 diffuseMapColor = tex2D(diffuseMapSampler, oVS.coord);
    float4 heightMapColor = tex2D(heightMapSampler, oVS.coord);
    float4 specularMapColor = tex2D(specularMapSampler, oVS.coord);

    // �e���ʂ��v�Z
    ambient = ambientProcess();
    diffuse = diffuseByLightType(lightDir, oVS.nor, oVS.worldPos);
    specular = specularProcess(cameraDir, lightDir, oVS.nor);

    // ���C�g�ɂ���ăf�B�t���[�Y���v�Z
    float diff = diffuseByLightType(lightDir, oVS.nor, oVS.worldPos);

    // �e�����_�����O���[�h
    if(renderingMode == 0)
    {
        // RM_TEXTURE
        finColor = diffuseMapColor;
    }
    else if (renderingMode == 1)
    {
        // RM_DIFFUSE
        finColor = float4(diffuse, 1.0);
    }
    else if (renderingMode == 2)
    {
        // RM_SPECULAR
        finColor = float4(specular, 1.0);
    }
    else if(renderingMode == 3)
    {
        // RM_NORMAL
        finColor = normalColor;
    }
    else
    {
        // RT_SHADING
        finColor = float4((ambient + diffuse + specular), 1.0) * diffuseMapColor;
        
        //finColor = float4((ambient + diffuse), 1.0) * diffuseMapColor;
        //finColor += float4(specular, 1.0) * specularMapColor;

        // �e�N�X�`���������s�N�Z���̏ꍇ�A�ŏI�F�̃A���t�@�l��0�ɂ���
        if(diffuseMapColor.w == 0.0)
        {
            finColor.w = 0.0;
        }
    }

    return finColor;
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