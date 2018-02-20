//*****************************************************************************
//
// ���W�ϊ��ςݒ��_��2D�|���S����`�� [ScreenPolygon.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCREEN_POLYGON_H_
#define _SCREEN_POLYGON_H_

#include "Character.h"
#include "..\Engine.h"
#include "..\ResourcesManager.h"
#include "..\Shader\RHWShader.h"

#define MINIMAP_SIZE (SCREEN_HEIGHT / 3)

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class ScreenPolygon
{
private:
	RHWShader*	RHWshader;	// �ϊ��ςݗp�V�F�[�_�[

	void DrawObject(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DTEXTURE9 titleTexture, int level = 9, float alpha = 0.0f, bool needa = false);	// ���I�Ȃ��̂�`�悷��
	void MakeVertexDecl();																				// ���_�錾
	HRESULT MakeVertex(D3DXVECTOR2 pos, D3DXVECTOR2 size, LPDIRECT3DVERTEXBUFFER9* vertexBufferPoint);	// ���_�쐬
	HRESULT MakeTransVertex(D3DXVECTOR2 pos, D3DXVECTOR2 size, LPDIRECT3DVERTEXBUFFER9* vertexBufferPoint, float rot);	// ���_�쐬
	HRESULT MakeIndex();																				// �C���f�b�N�X�쐬

public:
	ResourcesManager*				resourcesManager;		// ���\�[�X�}�l�W�����g

	IDirect3DVertexDeclaration9*	vertexDecl;				// ���_�V�F�[�_�[�錾
	LPDIRECT3DINDEXBUFFER9			indexBuffer;			// ���_�C���f�b�N�X�o�b�t�@(���L)

	LPDIRECT3DVERTEXBUFFER9			UIminiMapVertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIminiMapTexture;		// �t�B�[���h�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9			UIminiMapPlayerVertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIminiMapPlayerTexture;			// �t�B�[���h�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9			UIminiMapEnemyVertexBuffer;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIminiMapEnemyTexture;			// �t�B�[���h�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9			UIHPVertexBuffer[3];	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIHPTexture;			// �t�B�[���h�e�N�X�`��
	int								HP;

	LPDIRECT3DVERTEXBUFFER9			UIpanVertexBuffer;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIpanTexture;			// �t�B�[���h�e�N�X�`��
	D3DXMATRIX						pan;					// ��]�s��

	LPDIRECT3DVERTEXBUFFER9			UIzenVertexBuffer;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIzenTexture;			// �t�B�[���h�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9			UIstopVertexBuffer;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIstopTexture;			// �t�B�[���h�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9			UIgouVertexBuffer;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIgouTexture;			// �t�B�[���h�e�N�X�`��
	LEVER_LEVEL						level;					// �D�̏��

	LPDIRECT3DVERTEXBUFFER9			UIleftVertexBuffer;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIleftTexture;			// �t�B�[���h�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9			UIrightVertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIrightTexture;			// �t�B�[���h�e�N�X�`��
	float							leftShooting;
	float							rightShooting;

	ScreenPolygon();
	~ScreenPolygon();

	void Draw();
	void Update(Character* player, Character* enemy);
};


#endif // !_SCREEN_POLYGON_H_