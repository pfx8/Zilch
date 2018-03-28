//*****************************************************************************
//
// ���C�g���� [Light.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Light
{
private:

public:
	float				attenuation;	// ���C�g�̌����l
	D3DXVECTOR3			pos;			// ���C�g�̈ʒu
	D3DXVECTOR4			ambient;		// ���l
	D3DXVECTOR4			diffuse;		// �g�U���˒l
	D3DXVECTOR4			specular;		// ���ʔ��˒l
	

	Light();	
	~Light();
};
#endif // !_LIGHT_H_
