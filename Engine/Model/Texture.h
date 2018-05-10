//*****************************************************************************
//
// �e�N�X�`������ [Texture.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Engine/Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Texture
{
	friend class Model;
	friend class Material;

private:

public:
	string						mName;		// �e�N�X�`�����O
	LPDIRECT3DTEXTURE9			mTex;		// �e�N�X�`���|�C���^

	Texture(string name, string path);
	~Texture();

	HRESULT loadingTexture(string path);	// �e�N�X�`����ǂݍ���
};

#endif // !_TEXTURE_H_

