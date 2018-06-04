//*****************************************************************************
//
// �A�E�g���C������ [outLine.fx]
//
// �R���p�C���͂��Ȃ�
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _OUTLINE_FX_
#define _OUTLINE_FX_

#include "publicValue.fx"
#include "lightingProcess.fx"

//*****************************************************************************
//
// �O���[�o���ϐ�
//
//*****************************************************************************
// �A�E�g���C����`�悷�鎞�A���_�x�N�g���Ɩ@���x�N�g�������������q��
float outlineFactor;

// �A�E�g���C���̑������R���g���[�����q
float outlineStrength;

// �A�E�g���C���J���[
float4 outlineColor;

//*****************************************************************************
//
// outLine���_�V�F�[�_�[����
//
//*****************************************************************************
outputVS outLineVS(inputVS iVS)
{
    // �߂�l��������
    outputVS oVS = (outputVS) 0;

    // outLine�����x�N�g�����v�Z
    // �܂��͒��_�̕����x�N�g�����v�Z
    float3 outLineDir = normalize(iVS.pos);
    // ���_�̕����x�N�g���Ɩ@���x�N�g���̊O�ς��v�Z
    float D = dot(outLineDir, iVS.nor);
    // outLine�̍ŏI�������v�Z
    outLineDir *= sign(D);
    outLineDir = outLineDir * outlineFactor + iVS.nor * (1 - outlineFactor);
    // ���_ + outLine�����x�N�g * outLine�������� = outLine���_�̏ꏊ
    float3 outLinePos = iVS.pos + outLineDir * outlineStrength;

    // ���_�ϊ�
    oVS.worldPos = mul(float4(outLinePos, 1.0), worldMatrix);
    oVS.pos = mul(mul(oVS.worldPos, viewMatrix), projectionMatrix);

    // �@���ύX
    oVS.nor = mul(float4(iVS.nor, 1.0), worldMatrix);
    // UV���W�ύX
    oVS.coord = iVS.coord;

    return oVS;
}

//*****************************************************************************
//
// outLine�s�N�Z���V�F�[�_�[����
//
//*****************************************************************************
float4 outLinePS(outputVS oVS) : COLOR
{
    // outLine�J���[��ݒ�
    return outlineColor;
}

#endif // !_PUBLIC_VALUE_FX_