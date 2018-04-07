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
	if (this->mName != "DefaultMaterial")
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
	}
	else
	{
		this->mAmbient = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->mDiffuse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->mSpecular = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		cout << "[Warning] No Material" << endl;
	}

	// テクスチャを読み込み
	vector<Texture*> diffuseMaps = addTextureFromResources(mat, aiTextureType_DIFFUSE);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());	// 取得したdiffuseMapsをallTextureの後ろに追加
	//vector<Texture> normalMaps = loadMaterialTexture(material, aiTextureType_HEIGHT);
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
vector<Texture*>Material::addTextureFromResources(aiMaterial* mat, aiTextureType type)
{
	vector<Texture*> textures;	// 読み込んだテクスチャ

	for (unsigned int count = 0; count < mat->GetTextureCount(type); count++)
	{
		aiString str;																// モデルから読み込まれたテクスチャファイルの名前
		mat->getTexture(type, count, &str);					// テクスチャパスを読み込み

		//////////////////////////////////////////////////暫定対策//////////////////////////////////////////////////
		// テクスチャ名前を保存
		string fileName = str.C_Str();
		// 絶対パスならば、モデルの名前とテクスチャを取得
		if (fileName.find_first_of("\\") != string::npos)							// exp : c:\aaa\bbb\ccc.png -> bbb.png
		{
			fileName = fileName.substr(fileName.find_last_of("\\") + 1, fileName.find_first_of("."));
		}
		fileName = fileName.substr(0, fileName.find_first_of("."));		// exp : xxx.png -> xxx
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////

		bool skip = false;

		// もう読み込んだテクスチャならば、mTextureLoadedからもらう
		for (auto it : mTexturesLoaded)
		{
			if (strcmp(it->getTexPath().c_str(), fileName.c_str()) == 0)
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
			Resources* resource = getResources();
			Texture* texture = resource->getTexture(fileName.c_str());
			
			if (texture->mTex == nullptr)
			{
				cout << "[Error] Add <Texture> " << fileName.c_str() << " in <Material> ... failed!" << endl;
			}
			else
			{
				// テクスチャを保存
				textures.push_back(texture);
				this->mTexturesLoaded.push_back(texture);
				cout << "[Information] Add <Texture> " << fileName.c_str() << " in <Material> ... success!" << endl;
			}
		}
	}

	return textures;
}