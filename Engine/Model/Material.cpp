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
	this->shininess = 1.0f;				// デフォルト値

	loadingMaterial(mat);
}

//*****************************************************************************
//
// マテリアルを読み込み
//
//*****************************************************************************
void Material::loadingMaterial(aiMaterial* mat)
{
	// マテリアルの名前を取得
	aiString name;
	mat->Get(AI_MATKEY_NAME, name);
	this->name = name.C_Str();

	// マテリアルがあれば、マテリアル属性を取得
	if (this->name != "DefaultMaterial")
	{
		aiColor3D ambient(0.0f, 0.0f, 0.0f);
		aiColor3D diffuse(0.0f, 0.0f, 0.0f);
		aiColor3D specular(0.0f, 0.0f, 0.0f);

		mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
		mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);
	
		this->ambient = D3DXVECTOR3(ambient.r, ambient.g, ambient.b);
		this->diffuse = D3DXVECTOR3(diffuse.r, diffuse.g, diffuse.b);
		this->specular = D3DXVECTOR3(specular.r, specular.g, specular.b);

		cout << "      <Material Name> : [" << name.C_Str() << "]" << endl;
	}
	else
	{
		this->ambient = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->diffuse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->specular = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		cout << "[Warning] No Material" << endl;
	}

	// テクスチャを読み込み
	addTextureFromResources(mat, aiTextureType_DIFFUSE);
	//addTextureFromResources(mat, aiTextureType_HEIGHT); // normalMap
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
void Material::addTextureFromResources(aiMaterial* mat, aiTextureType type)
{
	for (unsigned int count = 0; count < mat->GetTextureCount(type); count++)
	{
		aiString str;																// モデルから読み込まれたテクスチャファイルの名前
		mat->getTexture(type, count, &str);					// テクスチャパスを読み込み

		//////////////////////////////////////////////////暫定対策//////////////////////////////////////////////////
		// テクスチャ名前を保存
		string fileName = str.C_Str();

		//cout << "<Test1> : " << fileName << endl;
		// 絶対パスならば、モデルの名前とテクスチャを取得
		if (fileName.find("\\") != string::npos)							// exp : c:\aaa\bbb\ccc.png -> ccc.png
		{
			fileName = fileName.substr(fileName.find_last_of("\\")+1, fileName.find_last_of("."));
			//cout << "<Test2> : " << fileName << endl;
		}
		fileName = fileName.substr(0, fileName.find_first_of("."));		// exp : xxx.png -> xxx
		//cout << "<Test3> : " << fileName << endl;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
			this->textures.push_back(texture);
			cout << "         <Texture Name> : [" << fileName.c_str() << "]" << endl;
		}
		
	}
}