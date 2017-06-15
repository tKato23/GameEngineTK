//	ヘッダファイルのインクルード
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Enemy::Enemy()
{
	Initialize();
}

//	初期化処理
void Enemy::Initialize()
{
	//	自機パーツの読み込み
	m_Obj.resize(PARTS_NUM);

	m_Obj[PARTS_FOOT].LoadModelFile(L"Resources\\Foot.cmo");
	m_Obj[PARTS_BODY].LoadModelFile(L"Resources\\Body.cmo");
	m_Obj[PARTS_HEAD].LoadModelFile(L"Resources\\head.cmo");
	m_Obj[PARTS_ARM].LoadModelFile(L"Resources\\Arm.cmo");
	m_Obj[PARTS_GUN].LoadModelFile(L"Resources\\Gun.cmo");

	//	親子関係の構築(子パーツに親を設定)
	m_Obj[PARTS_BODY].SetObjParent(&m_Obj[PARTS_FOOT]);
	m_Obj[PARTS_HEAD].SetObjParent(&m_Obj[PARTS_BODY]);
	m_Obj[PARTS_ARM].SetObjParent(&m_Obj[PARTS_BODY]);
	m_Obj[PARTS_GUN].SetObjParent(&m_Obj[PARTS_ARM]);

	//	子パーツの親からのオフセット(座標のずれ)をセット
	m_Obj[PARTS_BODY].SetPosition(Vector3(0, 0.3f, 0));
	m_Obj[PARTS_HEAD].SetPosition(Vector3(0, 0.3f, 0));
	m_Obj[PARTS_ARM].SetPosition(Vector3(0.5f, 0.3f, -0.4f));
	m_Obj[PARTS_GUN].SetPosition(Vector3(0, 0.0f, -0.2));

	//	タイマーの初期化
	m_Timer = 0;
	m_DistAngle = 0;

	//	初期位置を決定
	Vector3 pos;

	pos.x = rand() % 10;
	pos.z = rand() % 10;

	SetEnemyPosition(pos);
}


//	更新処理
void Enemy::EnemyUpdate()
{

	m_Timer--;
	if (m_Timer < 0)
	{
		m_Timer = 60;

		//	目標角をランダムに抽選
		//	-0.5～+0.5の乱数
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		//	-90～+90の乱数
		rnd *= 180.0f;
		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	{
		//	自機の角度を回転
		Vector3 rot = getEnemyRot();

		//	今の角度と目標角度の差
		float angle = m_DistAngle - rot.y;
		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}
		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}
		//	補間
		rot.y += angle * 0.01f;

		SetEnemyRotation(rot);
	}
	//	機体の方向に進む
	//	移動ベクトル
	Vector3 moveV(0.0f, 0.0f, -0.1f);

	float angle = m_Obj[PARTS_FOOT].GetRotation().y;
	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	//	自機の座標を移動
	Vector3 pos = m_Obj[0].GetPosition();
	//head_pos += moveV;
	m_Obj[0].SetPosition(pos + moveV);


	for (std::vector<Obj3d>::iterator it = m_Obj.begin(); it != m_Obj.end(); it++)
	{
		it->Update();
	}
	
}

//	描画処理
void Enemy::EnemyDraw()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin(); it != m_Obj.end(); it++)
	{
		it->Draw();
	}
}

//	敵の座標を取得
DirectX::SimpleMath::Vector3 Enemy::getEnemyPos()
{
	return m_Obj[0].GetPosition();
}

//	敵の回転角を取得
DirectX::SimpleMath::Vector3 Enemy::getEnemyRot()
{
	return m_Obj[0].GetRotation();
}

void Enemy::SetEnemyPosition(const Vector3& pos)
{
	m_Obj[0].SetPosition(pos);
}

void Enemy::SetEnemyRotation(Vector3 rot)
{
	m_Obj[0].SetRotation(rot);
}


