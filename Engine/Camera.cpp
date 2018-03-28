//*****************************************************************************
//
// カメラ処理 [Camera.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Camera.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Camera::Camera()
{
	this->field = D3DXToRadian(45);
	this->ratio = (float)SCREEN_WIDTH / SCREEN_HEIGHT;;
	this->rangeStart = 0.1f;
	this->rangeEnd = 2500;

	this->posEye	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->posAt		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->beforeAngle = 0.0f;

	this->upVector		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->lookVector	= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	this->rightVector	= D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

	this->offsetFromTargetMin = 15.0f;
	this->offsetFromTargetMax = 75.0f;
	this->verticalRadiansMin = cosf(D3DXToRadian(15.0f));
	this->verticalRadiansMax = cosf(D3DXToRadian(75.0f));

	this->rotateSpeedHorizonal = 2.0f;
	this->rotateSpeedVertical = 1.0f;
	this->zoomSpeed = 2.0f;

	this->whereIsCamera = WIC_freedom;

	D3DXMatrixIdentity(&vMatrix);
	D3DXMatrixIdentity(&pMatrix);

	this->message = new DebugMessage();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Camera::~Camera()
{
	RELEASE_CLASS_POINT(this->message);
}

//*****************************************************************************
//
// カメラを初期化する
//
//*****************************************************************************
void Camera::InitCameraByPlayer(Character* player)
{	
	this->posEye = D3DXVECTOR3(0.0f, 10.0f, -35.0f);
	this->posAt = D3DXVECTOR3(0.0f, 7.5f, 0.0f);

	this->offSetFromPlayer = player->model->pos - this->posEye;
	this->offSetFromPlayerBack = player->model->pos - this->posEye; // プレーヤー後ろになる座標を保存

	SetViewport();		// ビューポートを設定
}


//*****************************************************************************
//
// カメラ更新
//
//*****************************************************************************
void Camera::Update(Character* player)
{
	// カメラ操作更新
	CameraContrlUpdate(player);

	D3DXVECTOR3 temp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// カメラ位置を更新
	switch (whereIsCamera)
	{
	case WIC_freedom:
		this->posEye = player->model->pos - this->offSetFromPlayer;
		this->posAt = player->model->pos + D3DXVECTOR3(0.0f, 5.0f, 0.0f);
		
		// 注視方向ベクトル
		temp = player->model->pos - this->posEye;

		break;
	case WIC_left:
		this->posAt = player->model->pos - player->model->rightVector * 20.0f;
		this->posEye = player->model->pos + D3DXVECTOR3(0.0f, 5.0f, 0.0f) - player->model->rightVector * 1.5f;

		// 注視方向ベクトル
		temp = -player->model->rightVector;

		break;
	case WIC_right:
		this->posAt = player->model->pos + player->model->rightVector * 20.0f;
		this->posEye = player->model->pos + D3DXVECTOR3(0.0f, 5.0f, 0.0f) + player->model->rightVector * 1.5f;

		// 注視方向ベクトル
		temp = player->model->rightVector;

		break;
	case WIC_playerBack:
		this->posEye = player->model->pos - this->offSetFromPlayerBack;
		this->posAt = player->model->pos + D3DXVECTOR3(0.0f, 5.0f, 0.0f);

		// 注視方向ベクトル
		temp = player->model->pos - this->posEye;

		// フリーカメラに戻る
		this->whereIsCamera = WIC_freedom;
		this->offSetFromPlayer = this->offSetFromPlayerBack;

		break;
	}

	// カメラベクトルを更新
	D3DXVec3Normalize(&this->lookVector, &temp);
	D3DXVec3Cross(&this->rightVector, &this->lookVector, &player->model->upVector);
	D3DXVec3Normalize(&this->rightVector, &this->rightVector);
	D3DXVec3Cross(&this->upVector, &this->rightVector, &this->lookVector);
	D3DXVec3Normalize(&this->upVector, &this->upVector);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&this->vMatrix, &this->posEye, &this->posAt, &this->upVector);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&this->pMatrix,
								this->field,   		// ビュー平面の視野角
								this->ratio,		// ビュー平面のアスペクト比
								this->rangeStart,	// ヒュー平面のNearZ値
								this->rangeEnd);	// ビュー平面のFarZ値
}

//*****************************************************************************
//
// カメラ操作更新
//
//*****************************************************************************
void Camera::CameraContrlUpdate(Character* player)
{
	// 射撃モードに変更
	bool isButton = false;

	isButton = (GetKeyboardTrigger(DIK_R) || IsButtonTriggered(0, BUTTON_L1));
	if (isButton)
	{
		if (this->whereIsCamera == WIC_left)
		{
			this->whereIsCamera = WIC_freedom;
		}
		else
		{
			this->whereIsCamera = WIC_left;
		}

	}
	isButton = (GetKeyboardTrigger(DIK_T) || IsButtonTriggered(0, BUTTON_R1));
	if (isButton)
	{
		if (this->whereIsCamera == WIC_right)
		{
			this->whereIsCamera = WIC_freedom;
		}
		else
		{
			this->whereIsCamera = WIC_right;
		}

	}

	//if (GetKeyboardPress(DIK_I))	// カメラを上に移動
	//{
	//	Rotation(player, 0, D3DXToRadian(1.0f));
	//}
	//else if (GetKeyboardPress(DIK_K))	// カメラを下に移動
	//{
	//	Rotation(player, 0, D3DXToRadian(-1.0f));
	//}

	isButton = (GetKeyboardPress(DIK_J) || IsButtonPressed(0, RIGHT_STICK_LEFT));
	if (isButton && this->whereIsCamera == WIC_freedom)	// 左回転
	{
		Rotation(player, D3DXToRadian(1.0f), 0);
	}
	isButton = (GetKeyboardPress(DIK_L) || IsButtonPressed(0, RIGHT_STICK_RIGHT));
	if (isButton && this->whereIsCamera == WIC_freedom)	// 右回転
	{
		Rotation(player, D3DXToRadian(-1.0f), 0);
	}

	isButton = (GetKeyboardPress(DIK_Q) || IsButtonPressed(0, BUTTON_TRIANGLE));
	if (isButton && this->whereIsCamera == WIC_freedom)	// ゾーンを拡大
	{
		Zoom(zoomSpeed);
	}
	isButton = (GetKeyboardPress(DIK_E) || IsButtonPressed(0, BUTTON_CROSS));
	if (isButton && this->whereIsCamera == WIC_freedom)	// ゾーンを縮小
	{
		Zoom(-zoomSpeed);
	}

	// プレーヤーの後ろに戻る
	if (GetKeyboardTrigger(DIK_Z) || IsButtonTriggered(0, BUTTON_CIRCLE))
	{
		this->whereIsCamera = WIC_playerBack;

		// もしプレーヤーが回転されたら
		// 水平(playerBcak)
		float angle = this->beforeAngle + player->model->rot.y;

		D3DXMATRIX HorizonalMatrixBack;
		D3DXMatrixRotationAxis(&HorizonalMatrixBack, &player->model->upVector, angle);							// 回転行列を作る
		D3DXVec3TransformCoord(&this->offSetFromPlayerBack, &this->offSetFromPlayerBack, &HorizonalMatrixBack);	// カメラの新しい座標を計算する

		this->beforeAngle -= angle;
	}
}

//*****************************************************************************
//
// 回転操作
//
//*****************************************************************************
void Camera::Rotation(Character* player, float radiansHorizonal, float radiansVertical)
{
	// 水平
	D3DXMATRIX HorizonalMatrix;
	D3DXMatrixRotationAxis(&HorizonalMatrix, &player->model->upVector, radiansHorizonal);			// 回転行列を作る
	D3DXVec3TransformCoord(&this->offSetFromPlayer, &this->offSetFromPlayer, &HorizonalMatrix);	// カメラの新しい座標を計算する

	// 垂直
	D3DXMATRIX VerticalMatrix;
	D3DXMatrixRotationAxis(&VerticalMatrix, &player->model->rightVector, radiansVertical);			// 回転行列を作る
	D3DXVECTOR3 tempOffset = D3DXVECTOR3(1.0f, 1.0f, 1.0f);				
	D3DXVec3TransformCoord(&tempOffset, &tempOffset, &VerticalMatrix);	// 移動後の座標を計算
	D3DXVec3Normalize(&tempOffset, &tempOffset);						// 法線を正規化
	float radianToPlayerUp = D3DXVec3Dot(&tempOffset, &player->model->upVector);	// カメラの移動範囲を制限するため、プレーヤーの垂直ベクトルと内積を計算する
	if (radianToPlayerUp < this->verticalRadiansMax && radianToPlayerUp > this->verticalRadiansMin)
	{
		this->offSetFromPlayer = tempOffset;
	}
}

//*****************************************************************************
//
// ズーム操作
//
//*****************************************************************************
void Camera::Zoom(float distance)
{
	D3DXVECTOR3 zoomDistance = this->lookVector * distance;			// 変更量を計算
	D3DXVECTOR3	tempOffset = this->offSetFromPlayer + zoomDistance;	// 新しい偏り量を計算

	float radians = D3DXVec3Length(&tempOffset);	// 半径を計算
	if (radians < this->offsetFromTargetMax && radians > this->offsetFromTargetMin)
	{
		// 半径は範囲内ならば、偏り量を更新
		this->offSetFromPlayer = tempOffset;
	}
}

//*****************************************************************************
//
// ビューポートを設定
//
//*****************************************************************************
void Camera::SetViewport()
{
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = SCREEN_WIDTH;
	vp.Height = SCREEN_HEIGHT;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;

	GetDevice()->SetViewport(&vp);	// ヒューポットを設定
}

//*****************************************************************************
//
// 座標をメッセージに渡して、画面に描画する
//
//*****************************************************************************
void Camera::OutputMessage(int row)
{
	message->DrawPosMessage("at  ", this->posAt, D3DXVECTOR2(0, float((row + 0) * 18)));
	message->DrawPosMessage("pos  ", this->posEye, D3DXVECTOR2(0, float((row + 1) * 18)));
	message->DrawPosMessage("look  ", this->lookVector, D3DXVECTOR2(0, float((row + 2) * 18)));
	message->DrawPosMessage("offset", this->offSetFromPlayer, D3DXVECTOR2(0, float((row + 3) * 18)));
}
