//*****************************************************************************
//
// リソース管理 [Resources.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include "Engine.h"
#include "Shader.h"
#include "Model\Mesh.h"
#include "Model\Model.h"
#include "Model\Texture.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Resources
{
private:

public:
	unordered_map<wstring, Model*>		mModels;
	unordered_map<wstring, Texture*>	mTextures;
	unordered_map<wstring, Shader*>		mShaders;

	Resources(void);
	~Resources(void);
	
	void createModel(const wstring path);
	Model* getModel(wstring name);
	void createTexture(const wstring modelName, const wstring texPath, TexType type);
	Texture* getTexture(const wstring modelName, const wstring texName);
	void createShader(const wstring path);
	Shader* getShader(wstring techniqueName);
};

#endif // !_RESOURCES_H_

