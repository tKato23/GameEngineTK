//	多重インクルードの防止
#pragma once

//	ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"

//	プレイヤークラス
class Player :public Obj3d
{
private:
	//	自機パーツ
	enum PARTS
	{
		PARTS_FOOT,		//	足
		PARTS_BODY,		//	体
		PARTS_HEAD,		//	頭
		PARTS_ARM,		//	腕
		PARTS_GUN,		//	銃

		PARTS_NUM
	};

	//	プレイヤーのパーツ
	std::vector<Obj3d> m_Obj;

	//	自機のワールド行列
	DirectX::SimpleMath::Matrix head_world;

	//	重力をかけるためのメンバ変数
	float m_height;

	//	弾丸の速度ベクトル
	DirectX::SimpleMath::Vector3 m_BulletVel;

	bool m_FireFlag;

public:

	void Initialize();									//	初期化処理

	void PlayerUpdate(DirectX::Keyboard::State key, DirectX::Keyboard::KeyboardStateTracker tracker);	//	更新処理
	void PlayerDraw();									//	描画処理

	//	弾丸を発射
	void FireBullet();
	//	弾丸を再装着(リセット）
	void ResetBullet();

	DirectX::SimpleMath::Vector3 getPlayerPos();		//	プレイヤーの座標を取得
	DirectX::SimpleMath::Vector3 getPlayerRot();		//	プレイヤーの回転角を取得


};

