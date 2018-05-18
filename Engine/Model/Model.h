//*****************************************************************************
//
// モデル処理 [Model.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MODEL_H_
#define _MODEL_H_

#include "Mesh.h"
#include "Material.h"
#include "Animation.h"

#include "..\Engine.h"
#include "..\Shader.h"

#include "..\..\Component\Camera.h"
#include "..\..\Component\Transform.h"

//*****************************************************************************
//
// 構造体定義
//
//*****************************************************************************
struct ModelInfo
{
	unsigned int numMeshes;
	unsigned int numMaterials;
	unsigned int numAnimations;
	unsigned int numTextures;
	unsigned int numLights;
	unsigned int numCameras;
};


//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Model
{
	friend class MeshRender;
private:
	HRESULT loadModel(wstring const& wPath);						// モデルを読み込み
	void processNode(aiNode *node, const aiScene *scene);			// ノード処理

	ModelInfo						mModelInfo;						// モデル情報構造体

public:
	unsigned int					mCurAnimation = 0;				// 現在のアニメーション番号
	wstring							mPath;							// モデルパス
	vector<Mesh*>					mMeshes;						// メッシュデータ
	vector<Animation*>				mAnimationes;					// アニメーションデータ
	vector<Bone*>					mBones;							// 骨データ
	vector<D3DXMATRIX>				mTransforms;					// 各骨の変換行列

	Model(wstring const& wPath);
	~Model();

	void checkAnimation(const aiScene* scene);						// モデルはアニメーションを含めてるかどうかをチェック
	void addAnimation(Animation* animation);						// アニメーションデータを読み込み
	void updateAnimation(float timeInSeconds);						// アニメーション更新

	void drawShadow(Shader* shader);								// モデルのシャドウマップを描画
	void drawModel(Shader* shader);									// モデルを描画

	void checkBone(aiMesh* mesh);									// 骨あるかどうかをチェック
	void createBone(aiMesh* mesh);									// 骨データを解析して保存
	void traverseNode(Node* node, unsigned int level);				// 骨ノードをトラバース
};

#endif // !_MODEL_H_

