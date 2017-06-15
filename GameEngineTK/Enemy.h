//	多重インクルードの防止
#pragma once

//	ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <vector>
#include "Obj3d.h"

//	敵クラス
class Enemy :public Obj3d
{
private:
	//	敵パーツ
	enum PARTS
	{
		PARTS_FOOT,		//	足
		PARTS_BODY,		//	体
		PARTS_HEAD,		//	頭
		PARTS_ARM,		//	腕
		PARTS_GUN,		//	銃

		PARTS_NUM
	};

	//	敵のパーツ
	std::vector<Obj3d> m_Obj;

	//	自機のワールド行列
	DirectX::SimpleMath::Matrix head_world;

	int m_Timer;										//	タイマー
	//	目標角度
	float m_DistAngle;

public:
	Enemy();

	void Initialize();									//	初期化処理

	void EnemyUpdate();									//	更新処理
	void EnemyDraw();									//	描画処理

	DirectX::SimpleMath::Vector3 getEnemyPos();			//	敵の座標を取得
	DirectX::SimpleMath::Vector3 getEnemyRot();			//	敵の回転角を取得

	void SetEnemyPosition(const DirectX::SimpleMath::Vector3& pos);	//	敵の座標を設定
	void SetEnemyRotation(DirectX::SimpleMath::Vector3 rot);	//	敵の座標を設定
};

