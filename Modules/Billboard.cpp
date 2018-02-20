//*****************************************************************************
//
// ビルボード処理 [billboard.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "billboard.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
BillBoard::BillBoard()
{
	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->moveSpeedVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->accelerarion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->isUse = true;

	this->titleTexture = NULL;
	this->vertexBuffer = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
BillBoard::~BillBoard()
{
	RELEASE_POINT(this->titleTexture);
	RELEASE_POINT(this->vertexBuffer);
}

//*****************************************************************************
//
// 初期化処理
//
//*****************************************************************************
void BillBoard::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexBillboard();
}

//*****************************************************************************
//
// 更新処理
//
//*****************************************************************************
void BillBoard::Update()
{
	// 垂直位置の計算 
	this->moveSpeedVec.y += this->accelerarion.y;
	this->pos.y += 0.5f * this->moveSpeedVec.y * ONE_FRAME_TIME;

	// 水平移動
	this->moveSpeedVec.x += this->accelerarion.x;
	this->moveSpeedVec.z += this->accelerarion.z;
	this->pos.x += this->moveSpeedVec.x;
	this->pos.z += this->moveSpeedVec.z;

	// 地図の範囲を超えたら、弾を消す
	if (this->pos.y <= 0.0f)
	{
		// 消したら数値を全部初期化
		this->isUse = false;
		this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->moveSpeedVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		// 頂点情報の作成
		MakeVertexBillboard();
	}
}

//*****************************************************************************
//
// 描画処理
//
//*****************************************************************************
void BillBoard::Draw(D3DXMATRIX viewMatrix)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ビューマトリックスを取得
	mtxView = viewMatrix;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&this->worldMatrix);

	// ポリゴンを正面に向ける
	this->worldMatrix._11 = mtxView._11;
	this->worldMatrix._21 = mtxView._12;
	this->worldMatrix._12 = mtxView._21;
	this->worldMatrix._31 = mtxView._13;
	this->worldMatrix._13 = mtxView._31;
	this->worldMatrix._22 = mtxView._22;
	this->worldMatrix._32 = mtxView._23;
	this->worldMatrix._23 = mtxView._32;
	this->worldMatrix._33 = mtxView._33;

	// スケールを反映
	D3DXMatrixScaling(&mtxScale, this->scl.x, this->scl.y, this->scl.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxScale);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &this->worldMatrix);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(BILLBOARDVERTEX));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_BILLBOARDVERTEX);

	// テクスチャの設定
	//pDevice->SetTexture(0, texture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*****************************************************************************
//
// 頂点作成
//
//*****************************************************************************
HRESULT BillBoard::MakeVertexBillboard()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(BILLBOARDVERTEX) * 4,	// 頂点データ用に確保するバッファサイズ(バイト単位)
											D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
											FVF_BILLBOARDVERTEX,		// 使用する頂点フォーマット
											D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
											&this->vertexBuffer,		// 頂点バッファインターフェースへのポインタ
											NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		BILLBOARDVERTEX *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		this->vertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].position = pos + D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[1].position = pos + D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[2].position = pos + D3DXVECTOR3(BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[3].position = pos + D3DXVECTOR3(BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);

		// 法線の設定
		pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点データをアンロックする
		this->vertexBuffer->Unlock();
	}

	return S_OK;
}

//*****************************************************************************
//
// 頂点座標の設定
//
//*****************************************************************************
void BillBoard::SetVertexBillboardByship(float sizeX, float sizeY, Character* ship, bool isLeft)
{
	this->isUse = true;

	this->pos = ship->pos + ship->lookVector * 3.0f;
	this->moveSpeedVec = -ship->lookVector * sizeX;

	if (isLeft == true)
	{
		this->accelerarion = -ship->rightVector * 3;
	}
	else
	{
		this->accelerarion = ship->rightVector * 3;
	}

	// 座標更新
	{
		//頂点バッファの中身を埋める
		BILLBOARDVERTEX *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		this->vertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].position = pos + D3DXVECTOR3(-sizeX / 2, -sizeY / 2, 0.0f);
		pVtx[1].position = pos + D3DXVECTOR3(-sizeX / 2,  sizeY / 2, 0.0f);
		pVtx[2].position = pos + D3DXVECTOR3( sizeX / 2, -sizeY / 2, 0.0f);
		pVtx[3].position = pos + D3DXVECTOR3( sizeX / 2,  sizeY / 2, 0.0f);

		// 頂点データをアンロックする
		this->vertexBuffer->Unlock();
	}
}