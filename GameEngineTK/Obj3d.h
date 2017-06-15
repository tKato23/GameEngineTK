/// <summary>
/// 3Dオブジェクトのクラス
/// </summary>

#pragma once

//	ヘッダファイルのインクルード
#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

#include "Camera.h"

#include <map>

class Obj3d
{
public:
	//	静的メンバ関数
	static void InitializeStatic(
		Microsoft::WRL::ComPtr<ID3D11Device>            d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>     d3dContext,
		Camera* camera);

private:
	//	静的メンバ変数

	//	デバイス
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;

	//	デバイスコンテキスト
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;

	//	カメラ
	static Camera* m_Camera;

	//	汎用ステート設定
	static std::unique_ptr<DirectX::CommonStates> m_states;

	//	エフェクトファクトリ
	static std::unique_ptr<DirectX::EffectFactory> m_factory;


	// 読み込み済みモデルコンテナ
	static std::map<std::wstring, std::unique_ptr<DirectX::Model>> s_modelarray;

public:
	//	コンストラクタ
	Obj3d();

	//	更新
	void Update();
	//	描画
	void Draw();

	// ファイルからモデルを読み込む
	void LoadModelFile(const wchar_t*filename = nullptr);

	//	setter

	//	スケーリング(XYZ)
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	//	回転角(XYZ)
	void SetRotation(const DirectX::SimpleMath::Vector3& rot) { m_rotation = rot; m_UseQuaternion = false; }
	//	回転角(クォータニオン)
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rot) { m_rotationQ = rot; m_UseQuaternion = true; }
	//	平行移動(XYZ)
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_translation = pos; }
	//	親の3Dオブジェクト
	void SetObjParent(Obj3d* ObjParent) { m_ObjParent = ObjParent; }

	//	getter
	//	スケーリング(XYZ)
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	//	回転角(XYZ)
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
	//	平行移動(XYZ)
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_translation; }

	//	ワールド行列
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }

private:
	//	メンバ変数

	// モデルデータへのポインタ
	const DirectX::Model* m_pModel;
	//	スケーリング(XYZ)
	DirectX::SimpleMath::Vector3 m_scale;
	//	回転角(XYZオイラー角)
	DirectX::SimpleMath::Vector3 m_rotation;

	//	回転角(クォータニオン）
	DirectX::SimpleMath::Quaternion m_rotationQ;

	//	平行移動(XYZ)
	DirectX::SimpleMath::Vector3 m_translation;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	//	親のObj3Dへのポインタ
	Obj3d* m_ObjParent;
	//	回転をクォータニオンで扱うフラグ
	bool m_UseQuaternion;
};
