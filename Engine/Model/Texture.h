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
	friend class Material;

private:
	string										mPath;		// �e�N�X�`���p�X

public:
	LPDIRECT3DTEXTURE9			mTex;		// �e�N�X�`���|�C���^

	Texture(string path);
	~Texture();

	HRESULT loadingTexture();		// �e�N�X�`����ǂݍ���

	string getTexPath()
	{
		return this->mPath;
	}
};

#endif // !_TEXTURE_H_

