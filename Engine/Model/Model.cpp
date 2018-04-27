//*****************************************************************************
//
// モデル処理 [Model.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Model.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Model::Model(MeshType type, string const &path)
{
	// メッシュタイプを取得
	this->mMeshType = type;
	// モデルの名前を取得
	string fileName = path.substr(path.find_last_of("/") + 1, path.find_first_of("."));	// exp c:/aaa/bbb/ccc.fbx -> ccc
	this->mName = fileName;

	switch (this->mMeshType)
	{
	case MT_default:
		cout << "<Model><default> : " << fileName;
		break;
	case MT_withBone:
		cout << "<Model><withBone> : " << fileName;
		break;
	}

	loadModel(path);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Model::~Model()
{
	// delete vector
}

//*****************************************************************************
//
// モデルをロードする
//
//*****************************************************************************
HRESULT Model::loadModel(string const &path)
{
	Assimp::Importer import;			// Assimpのインポートを作る
	const aiScene *scene = import.ReadFile(path, aiProcessPreset_TargetRealtime_Quality | aiProcess_FixInfacingNormals | aiProcess_ConvertToLeftHanded);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "[Error] Assimp::" << import.GetErrorString() << endl;
		return E_FAIL;
	}

	// ルートノードから処理を始める
	processNode(scene->mRootNode, scene);

	cout << " loading ... success!" << endl;

	return S_OK;
}

//*****************************************************************************
//
// ノード処理
//
//*****************************************************************************
void Model::processNode(aiNode *node, const aiScene *scene)
{
	// もし今のノードにメッシュがあれば処理する
	for (unsigned int count = 0; count < node->mNumMeshes; count++)
	{
		// sceneのmMeshesは本当のメッシュデータ、一歩でnodeのmMesherはメッシュのインデックス
		aiMesh* aiMesh = scene->mMeshes[node->mMeshes[count]];
		this->mMeshes.push_back(new Mesh(this->mMeshType, aiMesh, this->mBones, scene));
	}

	// ノードメッセージを保存

	// 子供ノードを同じように処理する
	for (unsigned int count = 0; count < node->mNumChildren; count++)
	{
		processNode(node->mChildren[count], scene);
	}
}

//*****************************************************************************
//
// アニメーションデータを読み込み
//
//*****************************************************************************
void Model::addAnimation(Animation* animation)
{
	this->mAnimationes.push_back(animation);
}

//*****************************************************************************
//
// アニメーション更新
//
//*****************************************************************************
void Model::updateAnimation(float timeInSeconds)
{
	this->mAnimationes[this->mCurAnimation]->updateBoneTransforms(timeInSeconds, this->mBones, this->mTransforms);
}

//*****************************************************************************
//
// モデルのシャドウマップを描画
//
//*****************************************************************************
void Model::draw(Shader* shader)
{
	drawImGui();

	// 各メッシュのシャドウマップを描画
	for (auto it : mMeshes)
	{
		it->draw(shader);
	}
}

//*****************************************************************************
//
// モデルの情報をImGuiで出す
//
//*****************************************************************************
void Model::drawImGui()
{
	// モデル情報ウインドを作り
	ImGui::Begin(u8"モデル情報");
	ImGui::TextColored(ImVec4(1, 1, 1, 1), "<Model> : [%s]", this->mName.c_str());

	// ツリーノードの使う方法を設定
	ImGui::SetNextTreeNodeOpen(false, ImGuiSetCond_Once);
	// メッシュのグル―プを作るり
	if (ImGui::TreeNode(u8"メッシュ"))
	{
		unsigned msehNum = 0;
		unsigned int meshesNum = 1;
		for (auto it : this->mMeshes)
		{
			ImGui::Text("<Mesh><No.%.2d> : [%s]", meshesNum, it->mName.c_str());
			meshesNum++;

			// material
			unsigned int materialsNum = 1;
			for (auto it1 : it->mMaterials)
			{
				ImGui::Text("   <Material><No.%.2d> : [%s]", materialsNum, it1->mName.c_str());
				materialsNum++;

				// texture
				unsigned int texturesNum = 1;
				for (auto it2 : it1->mTextures)
				{
					ImGui::Text("      <Texture><No.%.2d> : [%s]", texturesNum, it2->mName.c_str());
					texturesNum++;
				}
			}
		}
		// グル―プツリーをポップ
		ImGui::TreePop();
	}

	// ツリーノードの使う方法を設定
	ImGui::SetNextTreeNodeOpen(false, ImGuiSetCond_Once);
	// ------------------Todo---------------------
	// 骨の情報をアニメーションからメッシュに移動
	//--------------------------------------------
	// 骨ツリーのグル―プを作るり
	if (ImGui::TreeNode(u8"ボーン"))
	{
		unsigned int level = 0;
		traverseNode(*(this->mAnimationes.at(0)->mNode.end() - 1), level);
		ImGui::TreePop();
	}

	ImGui::End();
}

//*****************************************************************************
//
// ノードをトラバース
//
//*****************************************************************************
void Model::traverseNode(Node* node, unsigned int level)
{
	string space;

	for (unsigned count = 0; count < level; count++)
	{
		space += "  ";
	}

	ImGui::Text("<Model>%s + [%s]", space.c_str(), node->mName.c_str());

	for (auto it : node->mChildren)
	{
		traverseNode(it, level + 1);
	}
}

//*****************************************************************************
//
// モデルを描画
//
//*****************************************************************************
void Model::draw(Shader* shader, Transform* trans, Camera* camera)
{
	D3DXMATRIX mat[87] = { };

	unsigned int count = 0;
	for (auto it : this->mBones)
	{
		mat[count] = it->mFinaTransform;
		//cout << "<Test><Mat> : " << it->mFinaTransform._11 << ", " << it->mFinaTransform._12 << ", " << it->mFinaTransform._13 << endl;
		count++;
	}

	// 骨の行列をシェーダーに渡す
	HRESULT hr;
	hr = shader->mEffect->SetMatrixArray("boneMatrices", mat, 87);

	// 各メッシュを描画
	for (auto it : mMeshes)
	{
		it->draw(shader, trans, camera);
	}
}