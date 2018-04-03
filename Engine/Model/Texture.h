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

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Texture
{
	friend class Model;

private:
	LPDIRECT3DTEXTURE9			mTex;		// �e�N�X�`���|�C���^
	string						mPath;		// �e�N�X�`���p�X
	LPDIRECT3DDEVICE9			mD3DDevice;		// D3D�f�o�C�X

public:
	Texture(string path);
	~Texture();

	HRESULT loadingTexture();		// �e�N�X�`����ǂݍ���

	string getTexPath()
	{
		return this->mPath;
	}
};

#endif // !_TEXTURE_H_

