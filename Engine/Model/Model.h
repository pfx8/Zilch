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
#include "../Engine.h"
#include "../Material.h"
#include "../Resources.h"
#include "../Shader.h"

//--------------Assimp--------------//
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Model
{
private:
	HRESULT loadModel(string const &mPath);					// モデルを読み込み
	void processNode(aiNode *node, const aiScene *scene);	// ノード処理
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);	// メッシュ処理
	vector<Texture> loadMaterialTexture(aiMaterial *mat, aiTextureType mType, string typeName);		// マテリアルからテクスチャを読み込み

public:
	vector<Mesh>					mMeshes;					// メッシュデータ
	vector<Texture>				mTexturesLoaded;		// 読み込まれたテクスチャデータ

	Model(string const &mPath);
	~Model();

	void draw();	// モデルを描画する
};

#endif // !_MODEL_H_

