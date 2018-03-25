//*****************************************************************************
//
// ���ʏ���[Plane.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _PLANE_H_
#define _PLANE_H_

struct PLANEVERTEX
{
	D3DXVECTOR3 position;		// ���_���W
	D3DXVECTOR3 normal;			// �@��
	D3DXVECTOR2 texture;		// �e�N�X�`�����W
	D3DXVECTOR3 tangent;		// �ڃx�N�g��
};

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Plane
{
private:
	RenderStatus	renderStatus = RS_withoutLight;	// �����_�����O���

	void SetWorldMatrix();	// ���[���h�ϊ�
	virtual HRESULT MakeVertexDecl(D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);	// ���_�錾

public:
	D3DXMATRIX		wMatrix;		// ���[���h�ϊ��}�g���b�N�X
	D3DXVECTOR3		pos;			// �ʒu
	D3DXVECTOR2		planeSize;
	D3DXVECTOR2		planeNum;

	int				vertexNum;		// ���_��
	int				polygonNum;		// �|���S����
	int				indexNum;		// �C���f�b�N�X��

	IDirect3DVertexDeclaration9*	vertexDecl;		// ���_�V�F�[�_�[�錾
	LPDIRECT3DVERTEXBUFFER9			vertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9			indexBuffer;	// ���_�C���f�b�N�X�o�b�t�@
	LPDIRECT3DTEXTURE9				tex;			// �t�B�[���h�e�N�X�`��
	LPDIRECT3DTEXTURE9				normalMap;		// �t�B�[���h�e�N�X�`��

	Plane();
	~Plane();

	virtual HRESULT InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);	// ���W��ݒ�
	virtual void Draw(Shader* shader2D, Camera* camera);				// �e�N�X�`����`�悷��(PixelShader)

	void Update();
};
#endif // !_PLANE_H_