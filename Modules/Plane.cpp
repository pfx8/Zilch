//*****************************************************************************
//
// 平面処理[Plane.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Plane.h"

#include "../ResourcesManager.h"
//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Plane::Plane()
{
	this->scala = 2;
	this->waveAngle = 0.0f;

	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//this->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ポインタ
	this->vertexBuffer = NULL;
	this->indexBuffer = NULL;
	this->titleTexture = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Plane::~Plane()
{
	// ポインタ
	RELEASE_POINT(this->vertexBuffer);
	RELEASE_POINT(this->titleTexture);
	RELEASE_POINT(this->indexBuffer);
}

//*****************************************************************************
//
// 座標を設定
//
//*****************************************************************************
HRESULT Plane::InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum)
{
	this->pos = pos;	// 位置
	this->planeNum = planeNum;
	this->planeSize = planeSize;

	MakeVertexDecl(this->planeSize, this->planeNum);	// 頂点宣言(shader)

	return S_OK;
}

//*****************************************************************************
//
// 頂点宣言(Shader)
//
//*****************************************************************************
HRESULT Plane::MakeVertexDecl(D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	this->vertexNum = (planeNum.x + 1) * (planeNum.y + 1);	// 総頂点数
	this->polygonNum = planeNum.x * planeNum.y * 2 + (planeNum.y - 1) * 4;		// ポリゴン数
	this->indexNum = (planeNum.x + 1) * 2 * planeNum.y + (planeNum.y - 1) * 2;	// インデックス数

	// 頂点シェーダー宣言
	{
		D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
		{
			{ 0,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(planeDecl, &this->vertexDecl);
	}

	// 頂点バッファ作成
	{
		if (FAILED(pDevice->CreateVertexBuffer(this->vertexNum * sizeof(VERTEX_3D), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &this->vertexBuffer, NULL)))
		{
			std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}

		VERTEX_3D* VertexBuffer;

		// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得する
		this->vertexBuffer->Lock(0, 0, (void**)&VertexBuffer, 0);

		// 頂点バッファの中身を埋める
		// 頂点座標(ローカル座標 = 形を形成してる)
		// もの自身の座標、世界での座標には関係ない
		// this->posFiledは世界での位置で

		for (int numY = 0; numY < (planeNum.y + 1); numY++)
		{
			for (int numX = 0; numX < (planeNum.x + 1); numX++)
			{
				// 頂点座標の設定
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.x = -(planeNum.x / 2.0f) * planeSize.x + numX * planeSize.x;
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.y = 0;
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.z = (planeNum.y / 2.0f) * planeSize.y - numY * planeSize.y;
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.w = 1.0f;
				// 法線ベクトルの設定
				//VertexBuffer[numY * (int(planeNum.x) + 1) + numX].normalVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// 反射光の設定
				//VertexBuffer[numY * (int(planeNum.x) + 1) + numX].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
				// テクスチャ1座標の設定
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texturePosition.x = numX * 1.0f;
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texturePosition.y = numY * 1.0f;
			}
		}

		// 頂点データをアンロックする
		this->vertexBuffer->Unlock();
	}

	// 頂点インデックスバッファ作成
	{
		if (FAILED(pDevice->CreateIndexBuffer(this->indexNum * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &this->indexBuffer, NULL)))
		{
			std::cout << "[Error] 頂点インデクスが生成できない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}

		WORD* vertexIndex = NULL;		// イデックスの中身を埋める

		this->indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する

		int index = 0;
		for (int numY = 0; numY < planeNum.y; numY++)
		{
			if (numY > 0)
			{// 縮退ポリゴンのためのダブりの設定
				vertexIndex[index] = (numY + 1) * (planeNum.x + 1);
				index++;
			}

			for (int nCntVtxX = 0; nCntVtxX < (planeNum.x + 1); nCntVtxX++)
			{
				vertexIndex[index] = (numY + 1) * (planeNum.x + 1) + nCntVtxX;
				index++;
				vertexIndex[index] = numY * (planeNum.x + 1) + nCntVtxX;
				index++;
			}

			if (numY < (planeNum.y - 1))
			{// 縮退ポリゴンのためのダブりの設定
				vertexIndex[index] = numY * (planeNum.x + 1) + planeNum.x;
				index++;
			}
		}

		this->indexBuffer->Unlock();	// インデックス データのロックを解除する
	}

	return S_OK;
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void Plane::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&this->worldMatrix);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxTranslate);
}

//*****************************************************************************
//
// テクスチャを描画する
//
//*****************************************************************************
void Plane::Draw()
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	SetWorldMatrix();

	pDevice->SetVertexDeclaration(this->vertexDecl);							// 頂点宣言を設定
	pDevice->SetStreamSource(0, this->vertexBuffer, 0, sizeof(VERTEX_3D));		// 頂点バッファをデバイスのデータストリームにバイナリ
	pDevice->SetIndices(this->indexBuffer);										// 頂点インデックスバッファを設定
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->vertexNum, 0, this->polygonNum);	// ポリゴンの描画
}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void Plane::Update()
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	this->waveAngle += (rand()%5 + 10) / 5.0f / 180.0f * D3DX_PI;

	if (this->waveAngle > D3DX_PI * 2.0f)
		this->waveAngle = 0.0f;

	VERTEX_3D* VertexBuffer;

	// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得する
	this->vertexBuffer->Lock(0, 0, (void**)&VertexBuffer, 0);

	// 頂点バッファの中身を埋める
	// 頂点座標(ローカル座標 = 形を形成してる)
	// もの自身の座標、世界での座標には関係ない
	// this->posFiledは世界での位置で

	for (int numY = 0; numY < (this->planeNum.y + 1); numY++)
	{
		for (int numX = 0; numX < (this->planeNum.x + 1); numX++)
		{
			// システム時間を取得
			float time = timeGetTime();
			time = time / 10000000000.0f;

			VertexBuffer[numY * (int(this->planeNum.x) + 1) + numX].position.y = 1.8f * (sinf(numY + numX + this->waveAngle) + sinf(numY + this->waveAngle) + sinf(numX + this->waveAngle)) / 3.0f;

			int signX;	// X符号位
			int signZ;	// Z符号位

			float sinX;	// 
			float sinZ;	// 

			switch (rand()%4)
			{
			case 0:
				signX = -1;
				signZ = -1;
				sinX = this->waveAngle - time;
				sinZ = this->waveAngle - time;
				break;
			case 1:
				signX = 1;
				signZ = -1;
				sinX = this->waveAngle + time;
				sinZ = this->waveAngle - time;
				break;
			case 2:
				signX = -1;
				signZ = 1;
				sinX = this->waveAngle - time;
				sinZ = this->waveAngle + time;
				break;
			case 3:
				signX = 1;
				signZ = 1;
				sinX = this->waveAngle + time;
				sinZ = this->waveAngle + time;
				break;
			}
			//VertexBuffer[numY * (int(this->planeNum.x) + 1) + numX].position.x += signX * 0.8f * sinf(sinX);
			//VertexBuffer[numY * (int(this->planeNum.x) + 1) + numX].position.z += signZ * 0.8f * sinf(sinZ);
		}
	}
}