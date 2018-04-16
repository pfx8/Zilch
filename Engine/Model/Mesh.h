//*****************************************************************************
//
// メッシュ処理 [Mesh..h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_H_
#define _MESH_H_

#include <unordered_map>

#include "Material.h"
#include "Bone.h"
#include "../Engine.h"
#include "../Shader.h"
#include "../../Component/Camera.h"
#include "../../Component/Transform.h"

struct VertexBone 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DXVECTOR2 tex;

	// プラスインフォメーション
	//D3DXVECTOR3 tangent;
	//D3DXVECTOR3 bitangent;

	// 骨
	unsigned int	boneID[NUM_BONES_PER_VEREX];		// 骨のID
	float				weights[NUM_BONES_PER_VEREX];		// 骨の重量
};

class Mesh
{
private:
	LPDIRECT3DVERTEXBUFFER9			mVertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9			mIndexBuffer;	// 頂点インデックスバッファ
	IDirect3DVertexDeclaration9*			mVertexDecl;		// 頂点シェーダー宣言

	void loadingMesh(aiMesh *mesh, const aiScene *scene);					// メッシュを読み込み
	HRESULT SetupMesh();																			// メッシュをセットアップ

public:
	// メッシュデータ
	vector<VertexBone>												mVertices;					// 頂点データ
	vector<unsigned int>									mIndices;					// インデックスデータ
	vector<Material*>											mMaterials;				// マテリアルデータ

	vector<Bone*>												mBones;						// 骨データ


	Mesh(aiMesh *mesh, const aiScene *scene);		// メッシュの初期化
	~Mesh();

	void draw(Transform* trans, Camera* camera);	// ドロー
};
#endif // !_MESH_H_
