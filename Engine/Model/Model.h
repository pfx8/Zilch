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
	HRESULT loadModel(string const &path);									// モデルを読み込み
	void processNode(aiNode *node, const aiScene *scene);			// ノード処理

public:
	vector<Mesh*>					mMeshes;					// メッシュデータ

	Model(string const &mPath);
	~Model();

	void draw(Transform* trans, Camera* camera);	// モデルを描画する
};

#endif // !_MODEL_H_

