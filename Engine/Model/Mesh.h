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

//*****************************************************************************
//
// 構造体定義
//
//*****************************************************************************
// デフォルト頂点設計
struct Vertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DXVECTOR2 tex;

	// プラスインフォメーション
	//D3DXVECTOR3 tangent;
	//D3DXVECTOR3 bitangent;
};

// 骨付き頂点設計
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

//*****************************************************************************
//
//  列挙体定義
//
//*****************************************************************************
enum MeshType
{
	MT_default,
	MT_withBone,
};

//*****************************************************************************
//
// クラス定義
//
//*****************************************************************************
class Mesh
{
private:
	MeshType											mMeshType;		// メッシュタイプ
	LPDIRECT3DVERTEXBUFFER9			mVertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9			mIndexBuffer;	// 頂点インデックスバッファ
	IDirect3DVertexDeclaration9*			mVertexDecl;		// 頂点シェーダー宣言

	void createMesh(aiMesh *mesh, const aiScene *scene);										//	デフォルトメッシュを読み込み
	void createMeshWithBone(aiMesh *mesh, const aiScene *scene);						// 骨付きメッシュを読み込み
	HRESULT SetupMesh();																								// デフォルトメッシュをセットアップ
	HRESULT SetupMeshWithBone();																			// 骨付きメッシュをセットアップ

public:
	// メッシュデータ
	vector<VertexBone>										mVertices;					// 頂点データ
	vector<unsigned int>									mIndices;					// インデックスデータ
	vector<Material*>											mMaterials;				// マテリアルデータ
	vector<Bone*>												mBones;						// 骨データ

	Mesh(MeshType type, aiMesh *mesh, const aiScene *scene);		// メッシュの初期化
	~Mesh();

	void draw(Transform* trans, Camera* camera);	// ドロー
};
#endif // !_MESH_H_
