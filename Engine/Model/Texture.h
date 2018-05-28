//*****************************************************************************
//
// �e�N�X�`������ [Texture.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "..\Engine.h"

//*****************************************************************************
//
// �񋓑�
//
//*****************************************************************************
enum TexType
{
	TT_diffuse,
	TT_height,
	TT_specular,
};

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
	TexType						mType;			// �e�N�X�`���^�C�v
	wstring						mName;			// �e�N�X�`�����O
	wstring						mPath;			// �e�N�X�`���p�X
	LPDIRECT3DTEXTURE9			mTex;			// �e�N�X�`���|�C���^

	Texture(wstring path, TexType type);
	~Texture();

	HRESULT loadingTexture(wstring path);		// �e�N�X�`����ǂݍ���
};

#endif // !_TEXTURE_H_

