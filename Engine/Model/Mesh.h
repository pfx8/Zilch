//*****************************************************************************
//
// メッシュ処理 [Mesh..h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_H_
#define _MESH_H_

#include "Material.h"
#include "Bone.h"

#include "..\Engine.h"
#include "..\Shader.h"

#include "..\..\Component\Camera.h"
#include "..\..\Component\Transform.h"

//*****************************************************************************
//
// 構造体定義
//
//*****************************************************************************
// 頂点設計
struct VertexDesign 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DXVECTOR2 tex;

	// プラスインフォメーション
	//D3DXVECTOR3 tangent;
	//D3DXVECTOR3 bitangent;

	// 骨
	unsigned int	boneID[NUM_BONES_PER_VEREX] { 0, 0, 0, };					// 骨のID
	float			weights[NUM_BONES_PER_VEREX] { 0.0f, 0.0f, 0.0f, 0.0f};		// 骨の重み

	// test data
	unsigned int boneNum { 0 };
};

struct MeshInfo
{
	unsigned int numVertices;
	unsigned int numFaces;
};

//*****************************************************************************
//
//  列挙体定義
//
//*****************************************************************************
typedef enum MeshType
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
	friend class MeshRender;
private:
	wstring							mModelPath;				// モデルパス
	D3DXVECTOR3						mBoundingBoxMax;		// バウンディングボックスマックス座標の最大値
	D3DXVECTOR3						mBoundingBoxMin;		// バウンディングボックスマックス座標の最小値
	LPDIRECT3DVERTEXBUFFER9			mVertexBuffer;			// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9			mIndexBuffer;			// 頂点インデックスバッファ
	IDirect3DVertexDeclaration9*	mVertexDecl;			// 頂点宣言
	MeshInfo						mMeshInfo;				// メッシュ情報

	void createMesh(aiMesh* mesh, vector<Bone*>& bones, const aiScene* scene);					// メッシュを読み込み
	HRESULT setupMesh();																		// メッシュをセットアップ
	HRESULT setupVertices();																	// 頂点をセットアップ
	HRESULT setupIndexes();																		// インデックスをセットアップ

	void createBoundingBox(D3DXVECTOR3 vertexPos, D3DXVECTOR3 &boxMax, D3DXVECTOR3 &boxMin);	// バウンディングボックスサイズを作り

public:
	wstring							mName;					// メッシュの名前
	vector<VertexDesign>			mVertices;				// 頂点データ
	vector<unsigned int>			mIndices;				// 頂点インデックスデータ
	vector<Material*>				mMaterials;				// マテリアルデータ

	Mesh(aiMesh* mesh, vector<Bone*>& bones, const aiScene* scene, wstring modelPath);				// メッシュの初期化
	~Mesh();

	void drawShadow(Shader* shader);						// メッシュのシャドウマップを描画
	void drawModel(Shader* shader);							// メッシュを描画
};

#endif // !_MESH_H_
