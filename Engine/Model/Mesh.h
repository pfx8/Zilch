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
	float				weights[NUM_BONES_PER_VEREX];		// 骨の重み
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
	MeshType							mMeshType;			// メッシュタイプ
	D3DXVECTOR3						mBoundingBoxMax;		// バウンディングボックスマックス座標の最大値
	D3DXVECTOR3						mBoundingBoxMin;		// バウンディングボックスマックス座標の最小値
	LPDIRECT3DVERTEXBUFFER9			mVertexBuffer;		// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9			mIndexBuffer;		// 頂点インデックスバッファ
	IDirect3DVertexDeclaration9*		mVertexDecl;			// 頂点シェーダー宣言

	void createMesh(aiMesh *mesh, const aiScene *scene);										//	デフォルトメッシュを読み込み
	void createMeshWithBone(aiMesh *mesh, vector<D3DXMATRIX>* transforms, const aiScene *scene);						// 骨付きメッシュを読み込み
	HRESULT SetupMesh();																								// デフォルトメッシュをセットアップ
	HRESULT SetupMeshWithBone();																			// 骨付きメッシュをセットアップ

	void createBoundingBox(D3DXVECTOR3 vertexPos, D3DXVECTOR3 &boxMax, D3DXVECTOR3 &boxMin);		// バウンディングボックスサイズを作り

public:
	// メッシュデータ
	vector<VertexBone>				mVertices;				// 頂点データ
	vector<unsigned int>				mIndices;				// 頂点インデックスデータ
	vector<Material*>					mMaterials;				// マテリアルデータ

	Mesh(MeshType type, aiMesh *mesh, vector<D3DXMATRIX>* transforms, const aiScene *scene);		// メッシュの初期化
	~Mesh();

	void draw(Transform* trans, Camera* camera);	// ドロー
};
#endif // !_MESH_H_
