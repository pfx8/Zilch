//*****************************************************************************
//
// �}�e���A������ [Material.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Material
{
private:


public:
	D3DMATERIAL9*	materialPoint;	// �}�e���A�����ւ̃|�C���^
	DWORD			materialNum;		// �}�e���A�����̐�
	LPD3DXBUFFER	materialBuffer;	// �}�e���A���o�b�t�@

	Material();
	~Material();
};

#endif // !_MATERIAL_H
