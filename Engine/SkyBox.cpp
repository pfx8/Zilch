//*****************************************************************************
//
// スカイボックス処理 [SkyBox.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "SkyBox.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
SkyBox::SkyBox(void)
{
	// 初期化
	this->vertexBuffer = NULL;
	this->indexBuffer = NULL;
	this->vertexDecl = NULL;

	this->tex = NULL;

	this->length = 0.0f;
	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SkyBox::~SkyBox(void)
{
	RELEASE_POINT(this->vertexBuffer);
	RELEASE_POINT(this->indexBuffer);
	RELEASE_POINT(this->vertexDecl);

	RELEASE_POINT(this->tex);
}

//*****************************************************************************
//
// スカイボックスを初期化
//
//*****************************************************************************
HRESULT SkyBox::InitSkyBox(float length)
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// 頂点設計
	{
		D3DVERTEXELEMENT9 boundingBoxDecl[] =	// 頂点データのレイアウトを定義
		{
			{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION },
			{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD },
			D3DDECL_END()
		};
		pD3DDevice->CreateVertexDeclaration(boundingBoxDecl, &this->vertexDecl);

		// オブジェクトの頂点バッファを生成
		if (FAILED(pD3DDevice->CreateVertexBuffer(16 * sizeof(SKYBOXVERTEX), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &this->vertexBuffer, NULL)))
		{
			// Debugウインドへ
			cout << "<Error> make [Skybox] vertex buffer ... failed!" << endl;
			return E_FAIL;
		}

		// 頂点作成
		SKYBOXVERTEX vertex[] =
		{
			// 前
			{ D3DXVECTOR3(-length / 2, length / 2, length / 2), D3DXVECTOR2(0.0f, 0.0f) },
			{ D3DXVECTOR3( length / 2, length / 2, length / 2), D3DXVECTOR2(0.25f, 0.0f) },
			{ D3DXVECTOR3(-length / 2, 0.0f,       length / 2), D3DXVECTOR2(0.0f, 1.0f) },
			{ D3DXVECTOR3( length / 2, 0.0f,       length / 2), D3DXVECTOR2(0.25f, 1.0f) },

			// 右
			{ D3DXVECTOR3(length / 2, length / 2,  length / 2), D3DXVECTOR2(0.25f, 0.0f) },
			{ D3DXVECTOR3(length / 2, length / 2, -length / 2), D3DXVECTOR2(0.5f, 0.0f) },
			{ D3DXVECTOR3(length / 2, 0.0f,        length / 2), D3DXVECTOR2(0.25f, 1.0f) },
			{ D3DXVECTOR3(length / 2, 0.0f,       -length / 2), D3DXVECTOR2(0.5f, 1.0f) },

			// 後ろ
			{ D3DXVECTOR3( length / 2, length / 2, -length / 2), D3DXVECTOR2(0.5f, 0.0f) },
			{ D3DXVECTOR3(-length / 2, length / 2, -length / 2), D3DXVECTOR2(0.75f, 0.0f) },
			{ D3DXVECTOR3( length / 2, 0.0f,       -length / 2), D3DXVECTOR2(0.5f, 1.0f) },
			{ D3DXVECTOR3(-length / 2, 0.0f,       -length / 2), D3DXVECTOR2(0.75f, 1.0f) },

			// 左
			{ D3DXVECTOR3(-length / 2, length / 2, -length / 2), D3DXVECTOR2(0.75f, 0.0f) },
			{ D3DXVECTOR3(-length / 2, length / 2,  length / 2), D3DXVECTOR2(1.0f, 0.0f) },
			{ D3DXVECTOR3(-length / 2, 0.0f,       -length / 2), D3DXVECTOR2(0.75f, 1.0f) },
			{ D3DXVECTOR3(-length / 2, 0.0f,        length / 2), D3DXVECTOR2(1.0f, 1.0f) },

			//// 上
			//{ D3DXVECTOR3( length / 2, length / 2,  length / 2), D3DXVECTOR2(0.8f, 0.0f) },
			//{ D3DXVECTOR3(-length / 2, length / 2,  length / 2), D3DXVECTOR2(1.0f, 0.0f) },
			//{ D3DXVECTOR3( length / 2, length / 2, -length / 2), D3DXVECTOR2(0.8f, 1.0f) },
			//{ D3DXVECTOR3(-length / 2, length / 2, -length / 2), D3DXVECTOR2(1.0f, 1.0f) },
		};

		VOID* vertexBuffer = nullptr;	// 頂点バッファポインタ作成

		// 頂点データの範囲をロックして頂点バッファメモリへのポインタを取得する
		if (FAILED(this->vertexBuffer->Lock(0, 0, (void**)&vertexBuffer, 0)))
		{
			// Debugウインドへ
			cout << "<Error> [Skybox] vertex buffer can't lock ... failed!" << endl;
			return E_FAIL;
		}
		memcpy(vertexBuffer, vertex, sizeof(vertex));	// 作成された頂点を臨時ポインタの中に入れる
		this->vertexBuffer->Unlock();					// 頂点データをアンロックする
	}

	// インデックス設計
	{
		//オブジェクトの頂点インデックスバッファを生成
		if (FAILED(pD3DDevice->CreateIndexBuffer(24 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &this->indexBuffer, NULL)))
		{
			// Debugウインドへ
			cout << "<Error> make [Skybox] vertex index buffer ... failed!" << endl;
			return E_FAIL;
		}

		// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する
		WORD* vertexIndex = nullptr;	// イデックスの中身を埋める
		if (FAILED(this->indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0)))
		{
			// Debugウインドへ
			cout << "<Error> [Skybox] index buffer can't lock ... failed!" << endl;
			return E_FAIL;
		}

		// 前
		vertexIndex[0] = 0, vertexIndex[1] = 1, vertexIndex[2] = 2;
		vertexIndex[3] = 1, vertexIndex[4] = 2, vertexIndex[5] = 3;

		// 右
		vertexIndex[6] = 4, vertexIndex[7] = 5, vertexIndex[8] = 6;
		vertexIndex[9] = 5, vertexIndex[10] = 6, vertexIndex[11] = 7;

		// 後ろ
		vertexIndex[12] = 8, vertexIndex[13] = 9, vertexIndex[14] = 10;
		vertexIndex[15] = 9, vertexIndex[16] = 10, vertexIndex[17] = 11;

		// 左
		vertexIndex[18] = 12, vertexIndex[19] = 13, vertexIndex[20] = 14;
		vertexIndex[21] = 13, vertexIndex[22] = 14, vertexIndex[23] = 15;

		//// 上
		//vertexIndex[24] = 16, vertexIndex[25] = 17, vertexIndex[26] = 18;
		//vertexIndex[27] = 17, vertexIndex[28] = 18, vertexIndex[29] = 19;

		// インデックス データのロックを解除する
		this->indexBuffer->Unlock();
	}

	return S_OK;
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void SkyBox::SetWorldMatrix(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	D3DXMATRIX mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&this->wMatrix);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->wMatrix, &this->wMatrix, &mtxTranslate);
}

//*****************************************************************************
//
// スカイボックスを描画
//
//*****************************************************************************
void SkyBox::draw(Shader* mShader, D3DXMATRIX* vMatrix, D3DXMATRIX* pMatrix)
{
	PDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// テクニックを設定
	mShader->mEffect->SetTechnique("render_no_light");

	// ワールド変換、ビューイング変換、プロジェクション変換マトリックス
	mShader->mEffect->SetValue("wMat", &this->wMatrix, sizeof(D3DXMATRIX));
	mShader->mEffect->SetValue("vMat", vMatrix, sizeof(D3DXMATRIX));
	mShader->mEffect->SetValue("pMat", pMatrix, sizeof(D3DXMATRIX));

	// テクスチャの設定
	mShader->mEffect->SetValue("tex", &this->tex, sizeof(LPDIRECT3DTEXTURE9));

	// 描画
	unsigned int passNum = 0;
	mShader->mEffect->Begin(&passNum, 0);
	// 各パスを実行する
	for (unsigned int count = 0; count < passNum; count++)
	{
		mShader->mEffect->BeginPass(0);

		pD3DDevice->SetVertexDeclaration(this->vertexDecl);							// 頂点宣言を設定
		pD3DDevice->SetStreamSource(0, this->vertexBuffer, 0, sizeof(SKYBOXVERTEX));	// 頂点バッファをデバイスのデータストリームにバイナリ
		pD3DDevice->SetIndices(this->indexBuffer);										// 頂点イデックスの設定
		pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 17, 0, 16);			// バウンディングボックスの描画

		mShader->mEffect->EndPass();
	}
	mShader->mEffect->End();
}