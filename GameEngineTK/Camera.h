/// <summary>
/// カメラを制御するクラス
/// </summary>

//	多重インクルードの防止
#pragma once

//	ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>

class Camera
{
public:
	//	コンストラクタ
	Camera(int width, int height);
	//	デストラクタ
	virtual ~Camera();

	//	更新
	virtual void Update();

	//	ビュー行列の取得
	const DirectX::SimpleMath::Matrix& GetView();

	//	射影行列の取得
	const DirectX::SimpleMath::Matrix& GetProjection();

	//	視点座標のセット
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);

	//	参照点のセット
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);

	//	上方向ベクトルのセット
	void SetUpVec(const DirectX::SimpleMath::Vector3& upvec);

	//	垂直方向視野角のセット
	void SetFovY(float fovY);

	//	アスペクト比のセット
	void SetAspect(float aspect);

	//	ニアクリップのセット
	void SetNearClip(float nearclip);

	//	ファークリップのセット
	void SetFarClip(float farclip);

protected:
	//	カメラの位置(視点座標）
	DirectX::SimpleMath::Vector3 m_eyepos;
	//	カメラの見ている先(注視点/参照点)
	DirectX::SimpleMath::Vector3 m_refpos;
	//	カメラの上方向ベクトル
	DirectX::SimpleMath::Vector3 m_upvec;
	//	ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	//	垂直方向視野角
	float m_fovY;
	//	アスペクト比(横縦の比率）
	float m_aspect;
	// ニアクリップ(手前の表示限界距離)
	float m_nearclip;
	//	ファークリップ(奥の表示限界距離)
	float m_farclip;
	//	射影行列
	DirectX::SimpleMath::Matrix m_proj;
};