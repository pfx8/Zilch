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
Material::Material(aiMaterial* mat, Model* model)
{
	// 所属モデルポインタを取得
	this->mParentModel = model;

	// デフォルト値
	this->mShininess = 40.0f;

	loadingMaterial(mat);

	// Debugウインドへ
	wcout << "<Scene> loading <Material> " << this->mName << " ... sucessed!" << endl;
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
	this->mName = stringUTF8ToUnicode(name.C_Str());

	// マテリアルがあれば、マテリアル属性を取得
	if (name.C_Str() != "DefaultMaterial")
	{
		aiColor3D ambient = { 0.0f, 0.0f, 0.0f };
		aiColor3D diffuse = { 0.0f, 0.0f, 0.0f };
		aiColor3D specular = { 0.0f, 0.0f, 0.0f };

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

		// Debugウインドへ
		cout << "<Warning> no material" << endl;
	}

	// ディフューズテクスチャを読み込み
	addTextureFromResources(mat, aiTextureType_DIFFUSE);
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
		// 読み込みマック
		bool skip = false;
		Resources* resource = getResources();

		// テクスチャパスを読み込み
		aiString path;
		mat->getTexture(type, count, &path);
		//cout << "<Test path>" << path.C_Str() << endl;

		// aiStringの文字コードはstringのutf-8
		wstring wPath = stringUTF8ToUnicode(path.C_Str());
		//wcout << "<Test wPath>" << wPath << endl;
		wPath = searchTexturePath(wPath);

		// 名前で判断する、新しいテクスチャだけを読み込み
		wstring name = pathToFileName(wPath);
		for (auto it : this->mParentModel->mTextures)
		{
			if (it->mName == name)
			{
				skip = true;
				this->mTextures.push_back(it);
				break;
			}
		}

		// テククシャを読み込んで取得する
		if (skip == false)
		{
			resource->createTexture(wPath);
			Texture* texture = resource->getTexture(name);
			this->mTextures.push_back(texture);
			this->mParentModel->mTextures.push_back(texture);
		}

	}
}

//*****************************************************************************
//
// Assimpから読み込まれたテクスチャパスを絶対パスに変換
//
//*****************************************************************************
wstring Material::searchTexturePath(wstring texturePathFromAssimp)
{
	bool skip = false;

	// 最終パス
	wstring filePath;
	// 臨時パス
	wstring tempPath;

	// モデルの名前を取得
	wstring modelName = pathToFileName(this->mParentModel->mPath);

	// 方法1
	// 指定パス
	// Resources\Texture\(モデルファイル名前)フォルダを探す
	wstring fileName = texturePathFromAssimp.substr(texturePathFromAssimp.find_last_of(L'\\') + 1, texturePathFromAssimp.find_last_of(L'.'));	// exp: c:\aaa\bbb\ccc.png -> ccc.png
	tempPath = L"Resources\\Texture\\" + modelName + L'\\' + fileName;

	// 無効なパスかどうかをチェック
	if (PathFileExists(tempPath.c_str()))
	{
		filePath = tempPath;
		skip = true;
	}


	// 方法2
	// 絶対パス
	if (skip == false)
	{
		// 無効なパスかどうかをチェック
		if (PathFileExists(texturePathFromAssimp.c_str()))
		{
			filePath = texturePathFromAssimp;
			skip = true;
		}
	}

	// 方法3
	// 同じファイル
	if(skip == false)
	{
		tempPath = this->mParentModel->mPath;
		tempPath = tempPath.substr(0, tempPath.find_last_of(L"\\"));
		tempPath = tempPath + L"\\" + texturePathFromAssimp;

		if (PathFileExists(tempPath.c_str()))
		{
			filePath = tempPath;
			skip = true;
		}
	}

	// 方法4
	// 相対パス
	if (skip == false)
	{
		tempPath = texturePathFromAssimp;
		int fileCount = 1;

		while (1)
		{
			if (tempPath.find(L'\\') != string::npos)
			{
				tempPath = tempPath.substr(0, tempPath.find_last_of(L"\\"));
				fileCount++;
			}
			else
			{
				break;
			}
		}

		wstring mainPath = this->mParentModel->mPath;
		for (unsigned int count = 0; count < fileCount; count++)
		{
			mainPath = mainPath.substr(0, mainPath.find_last_of(L"\\"));
		}

		wstring texPath = texturePathFromAssimp;

		//wcout << "<Test Path>" << mainPath << endl;
		//wcout << "<Test tesPath>" << texPath << endl;

		texPath = texPath.substr(texPath.find_first_of(L"\\"), texPath.size());

		filePath = mainPath + texPath;
	}

	return filePath;
}