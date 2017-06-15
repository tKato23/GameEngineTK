//	ヘッダファイルのインクルード
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	初期化処理
void Player::Initialize()
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

	//	変数の初期化
	m_height = 0.0f;

	//	弾丸用フラグ
	m_FireFlag = false;
}


//	更新処理
void Player::PlayerUpdate(DirectX::Keyboard::State key, DirectX::Keyboard::KeyboardStateTracker tracker)
{
	//	パーツギミック
	{

		//float angle = m_Obj[PARTS_ARM].GetRotation().z;
		//m_Obj[PARTS_ARM].SetRotation(Vector3(0, 0, angle + 0.03f));

		float pos = m_Obj[PARTS_ARM].GetPosition().z;
		m_Obj[PARTS_ARM].SetPosition(Vector3(0.5f, 0.3f, pos - 0.5f));

		m_Obj[PARTS_FOOT].SetPosition(
			Vector3(m_Obj[PARTS_FOOT].GetPosition().x,
				m_height,
				m_Obj[PARTS_FOOT].GetPosition().z));
	}

	//	機体に重力を加える
	m_height -= 0.05f;

	//	地面を貫通しないようにする
	if (m_height <= 0)
	{
		m_height = 0;
	}

	//	左旋回処理
	if (key.A)
	{
		//	自機の角度を回転
		//head_rot += 0.03f;
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(Vector3(0, angle + 0.03f, 0));
	}

	//	左旋回処理
	if (key.D)
	{
		//	自機の角度を回転
		//head_rot += -0.03f;
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(Vector3(0, angle - 0.03f, 0));
	}

	//	前進処理
	if (key.W)
	{
		//	移動ベクトル
		Vector3 moveV(0.0f, 0.0f, -0.1f);

		Matrix world;

		//	移動ベクトルを自機の角度分回転させる
		moveV = Vector3::TransformNormal(moveV, world);

		float angle = m_Obj[0].GetRotation().y;

		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);

		//	自機の座標を移動
		Vector3 pos = m_Obj[0].GetPosition();
		//head_pos += moveV;
		m_Obj[0].SetPosition(pos + moveV);

		//	機体を前傾させる
		m_Obj[PARTS_FOOT].SetRotation(Vector3(
			-0.4f,
			m_Obj[PARTS_FOOT].GetRotation().y,
			m_Obj[PARTS_FOOT].GetRotation().z)
		);
	}
	//	前傾姿勢を戻す
	else
	{
		//	
		m_Obj[PARTS_FOOT].SetRotation(
			Vector3(0.0f,
				m_Obj[PARTS_FOOT].GetRotation().y,
				m_Obj[PARTS_FOOT].GetRotation().z)
		);
	}


	//	後退処理
	if (key.S)
	{
		//	移動ベクトル
		Vector3 moveV(0.0f, 0.0f, 0.1f);

		Matrix world;

		//	移動ベクトルを自機の角度分回転させる
		moveV = Vector3::TransformNormal(moveV, world );

		float angle = m_Obj[0].GetRotation().y;

		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);

		//	自機の座標を移動
		Vector3 pos = m_Obj[0].GetPosition();
		//head_pos += moveV;
		m_Obj[0].SetPosition(pos + moveV);
	}

	//	Fキーが押されたら腕が飛ぶ
	if (key.F)
	{
		float pos = m_Obj[PARTS_ARM].GetPosition().z;
		m_Obj[PARTS_ARM].SetPosition(Vector3(0.5f, 0.3f, pos - 0.5f));
	}
	else
	{
		m_Obj[PARTS_ARM].SetPosition(Vector3(0.5f, 0.3f, -0.4f));
	}

	//	スペースキーが押されたら上昇処理を行う
	//if (key.Space)
	//{
	//	m_height += 0.3f;

	//	float pos = m_Obj[PARTS_FOOT].GetPosition().z;
	//	m_Obj[PARTS_FOOT].SetPosition(
	//		Vector3(m_Obj[PARTS_FOOT].GetPosition().x,
	//			m_height,
	//			m_Obj[PARTS_FOOT].GetPosition().z));

	//	//	一定の高さを超えないようにする
	//	if (m_Obj[PARTS_FOOT].GetPosition().y >= 20.0f)
	//	{
	//		m_height = 20.0f;
	//	}
	//}

	//	巨大化(Enterキー)
	if (tracker.IsKeyPressed(Keyboard::Keys::Enter))
	{
		if (m_Obj[1].GetScale() == Vector3(2.0f, 2.0f, 2.0f))
		{
			for (int i = 0; i < PARTS_NUM; i++)
			{
				m_Obj[i].SetScale(Vector3(1.0f, 1.0f, 1.0f));

			}
		}
		else
		{
			for (int i = 0; i < PARTS_NUM; i++)
			{
				m_Obj[i].SetScale(Vector3(2.0f, 2.0f, 2.0f));
			}
		}
	}

	if (m_FireFlag)
	{
		//	弾丸パーツの前進処理
		{
			//	弾丸パーツの座標を移動
			Vector3 pos = m_Obj[PARTS_GUN].GetPosition();
			m_Obj[PARTS_GUN].SetPosition(pos + m_BulletVel);
		}
	}

	if (tracker.IsKeyPressed(Keyboard::Keys::Space))
	{
		if (!m_FireFlag)
		{
			FireBullet();
		}
		else
		{
			ResetBullet();
		}
	}

	for (std::vector<Obj3d>::iterator it = m_Obj.begin(); it != m_Obj.end(); it++)
	{
		it->Update();
	}
}

//	描画処理
void Player::PlayerDraw()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin(); it != m_Obj.end(); it++)
	{
		it->Draw();
	}
}

void Player::FireBullet()
{
	if (!m_FireFlag)
	{
		//	発射するパーツのワールド行列を取得
		Matrix worldm = m_Obj[PARTS_GUN].GetWorld();

		//	抽出した情報をしまっておく変数
		Vector3 scale;			//	ワールドスケーリング
		Quaternion rotation;	//	ワールド回転
		Vector3 translation;	//	ワールド座標

		//	ワールド行列から各要素を抽出
		worldm.Decompose(scale, rotation, translation);

		//	親パーツから分離、独立させる
		m_Obj[PARTS_GUN].SetObjParent(nullptr);
		m_Obj[PARTS_GUN].SetScale(scale);
		m_Obj[PARTS_GUN].SetRotationQ(rotation);
		m_Obj[PARTS_GUN].SetPosition(translation);

		//	弾丸パーツの速度を設定
		m_BulletVel = Vector3(0, 0, -0.1f);
		//	パーツの向きに合わせて速度ベクトルを回転
		m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

		m_FireFlag = true;
	}
}

void Player::ResetBullet()
{
	if (m_FireFlag)
	{
		m_Obj[PARTS_GUN].SetObjParent(&m_Obj[PARTS_ARM]);

		m_Obj[PARTS_GUN].SetScale(Vector3(1, 1, 1));
		m_Obj[PARTS_GUN].SetRotation(Vector3(0, 0, 0));
		m_Obj[PARTS_GUN].SetPosition(Vector3(0, 0.0f, -0.2));

		m_FireFlag = false;
	}
}

//	プレイヤーの座標を取得
DirectX::SimpleMath::Vector3 Player::getPlayerPos()
{
	return m_Obj[PARTS_FOOT].GetPosition();
}

//	プレイヤーの回転角を取得
DirectX::SimpleMath::Vector3 Player::getPlayerRot()
{
	return m_Obj[PARTS_FOOT].GetRotation();
}


