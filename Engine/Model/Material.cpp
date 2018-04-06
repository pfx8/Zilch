//*****************************************************************************
//
// マテリアル処理 [Material.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Material.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Material::Material(aiMaterial* mat)
{
	this->mShininess = 1.0f;				// デフォルト値

	loadingMaterial(mat);
}

//*****************************************************************************
//
// マテリアルを読み込み
//
//*****************************************************************************
void Material::loadingMaterial(aiMaterial* mat)
{
	// このマテリアルのテクスチャコンテナ
	vector<Texture*> textures;

	// マテリアルの名前を取得
	aiString name;
	mat->Get(AI_MATKEY_NAME, name);
	this->mName = name.C_Str();
	
	// マテリアルがあれば、マテリアル属性を取得
	if (mName != "DefaultMaterial")
	{
		aiColor3D ambient(0.0f, 0.0f, 0.0f);
		aiColor3D diffuse(0.0f, 0.0f, 0.0f);
		aiColor3D specular(0.0f, 0.0f, 0.0f);

		mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
		mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);
	
		this->mAmbient = D3DXVECTOR3(ambient.r, ambient.g, ambient.b);
		this->mDiffuse = D3DXVECTOR3(diffuse.r, diffuse.g, diffuse.b);
		this->mSpecular = D3DXVECTOR3(specular.r, specular.g, specular.b);

		cout << "\t[Information] Loading <Material> " << mName << " ... success!" << endl;
	}
	else
	{
		this->mAmbient = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->mDiffuse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->mSpecular = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		cout << "\t[Warning] No Material" << endl;
	}

	// テクスチャを読み込み
	vector<Texture*> diffuseMaps = loadMaterialTexture(mat, aiTextureType_DIFFUSE, "diffuseTexture");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());	// 取得したdiffuseMapsをallTextureの後ろに追加
	//vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "specularTexture");
	//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());	// 取得したspecularMapsをallTextureの後ろに追加
	//vector<Texture> normalMaps = loadMaterialTexture(material, aiTextureType_HEIGHT, "normalTexture");
	//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());		// 取得したnormalMapsをallTextureの後ろに追加
	//vector<Texture> heightMaps = loadMaterialTexture(material, aiTextureType_AMBIENT, "heightTexture");
	//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());		// 取得したnormalMapsをallTextureの後ろに追加
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Material::~Material()
{

}

//*****************************************************************************
//
// マテリアルによってテクスチャを読み込み
//
//*****************************************************************************
vector<Texture*>Material::loadMaterialTexture(aiMaterial* mat, aiTextureType mType, string typeName)
{
	vector<Texture*> textures;	// 読み込んだテクスチャ

	for (unsigned int count = 0; count < mat->GetTextureCount(mType); count++)
	{
		aiString str;															// モデルから読み込まれたテクスチャファイルの名前
		mat->getTexture(mType, count, &str);			// テクスチャパスを読み込み
		string path = "Resources/Texture/Hixo/" + string(str.C_Str());		// テクスチャの前にパスをつき

		bool skip = false;

		// もう読み込んだテクスチャならば、mTextureLoadedからもらう
		for (auto it : mTexturesLoaded)
		{
			if (strcmp(it->getTexPath().c_str(), path.c_str()) == 0)
			{
				textures.push_back(it);
				skip = true;
				break;
			}
		}

		// 新しいテクスチャならば読み込む
		if (!skip)
		{
			// テクスチャまだ読み込まなっかたら読み込む
			Texture* texture = new Texture(path.data());

			// テクスチャタイプ属性を切り捨てる(warning)

			// テクスチャを読み込み
			textures.push_back(texture);
			this->mTexturesLoaded.push_back(texture);
		}
	}

	return textures;
}