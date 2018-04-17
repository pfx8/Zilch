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
#include "../Engine.h"
#include "../Shader.h"
#include "../../Component/Camera.h"
#include "../../Component/Transform.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Model
{
private:
	enum MeshType					mMeshType;									// メッシュタイプ
	unsigned int							mCurAnimation = 0;						// 現在のアニメーション番号

	HRESULT loadModel(string const &path);									// モデルを読み込み
	void processNode(aiNode *node, const aiScene *scene);			// ノード処理

public:
	vector<Mesh*>						mMeshes;					// メッシュデータ
	vector<Animation*>				mAnimationes;			// アニメーションデータ
	vector<Bone*>						mBones;						// 骨データ
	vector<D3DXMATRIX>			mMatrix;						// 時間により各骨の変換行列

	Model(MeshType type, string const &path);
	~Model();

	void addAnimation(Animation* animation);		// アニメーションデータを読み込み
	void updateAnimation(float timeInSeconds);	// アニメーション更新
	void draw(Transform* trans, Camera* camera);	// モデルを描画する
};

#endif // !_MODEL_H_

