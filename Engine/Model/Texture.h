//*****************************************************************************
//
// �e�N�X�`������ [Texture.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../Engine.h"

enum TextureType
{
	TT_diffuse,
	TT_effect,
};

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Texture
{
private:
	LPDIRECT3DTEXTURE9			mTex;		// �e�N�X�`���|�C���^
	TextureType					mType;		// �e�N�X�`���^�C�v
	string						mPath;		// �e�N�X�`���p�X
	LPDIRECT3DDEVICE9			mD3DDevice;		// D3D�f�o�C�X

public:
	Texture(string path, TextureType type);
	~Texture();

	HRESULT loadingTexture();		// �e�N�X�`����ǂݍ���
};

#endif // !_TEXTURE_H_

