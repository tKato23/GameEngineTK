//	ヘッダファイルのインクルード
#include "Obj3d.h"
#include "VertexTypes.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	静的メンバ変数の定義
//	デバイス
Microsoft::WRL::ComPtr<ID3D11Device>           Obj3d::m_d3dDevice;

//	デバイスコンテキスト
Microsoft::WRL::ComPtr<ID3D11DeviceContext>    Obj3d::m_d3dContext;

//	カメラ
Camera* Obj3d::m_Camera;

//	汎用ステート設定
std::unique_ptr<DirectX::CommonStates> Obj3d::m_states;

//	エフェクトファクトリ
std::unique_ptr<DirectX::EffectFactory> Obj3d::m_factory;

std::map<std::wstring, std::unique_ptr<DirectX::Model>> Obj3d::s_modelarray;

void Obj3d::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice  = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera     = camera;

	//	汎用ステートを生成
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());
	//	エフェクトファクトリの作成
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	//	テクスチャのパスを指定
	m_factory->SetDirectory(L"Resources");
}

//	コンストラクタ
Obj3d::Obj3d()
{
	//	メンバ変数を初期化
	m_scale = Vector3(1, 1, 1);
	m_ObjParent = nullptr;

	//	デフォルトではオイラー角を使用
	m_UseQuaternion = false;
}

//	CMOモデルを読み込む処理
void Obj3d::LoadModelFile(const wchar_t*filename)
{

	// 同じ名前のモデルを読み込み済みでなければ
	if (s_modelarray.count(filename) == 0)
	{
		// モデルを読み込み、コンテナに登録（キーはファイル名）
		s_modelarray[filename] = Model::CreateFromCMO(m_d3dDevice.Get(), filename, *m_factory);
	}
	m_pModel = s_modelarray[filename].get();
}

//	更新
void Obj3d::Update()
{
	//	ワールドの行列を計算
	Matrix scalemat = Matrix::CreateScale(m_scale);
	Matrix rotmat;
	if (m_UseQuaternion)
	{//	クォータニオンで回転を計算
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{//	オイラー角で回転を計算
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmaX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
		rotmat = rotmatZ * rotmaX * rotmatY;
	}
	Matrix transmat = Matrix::CreateTranslation(m_translation);
	//	ワールド行列の合成
	m_world = scalemat * rotmat * transmat;
	//	親の行列を掛ける
	if (m_ObjParent)
	{
		m_world *= m_ObjParent->GetWorld();
	}
}

//	描画
void Obj3d::Draw()
{
	//	描画
	if (m_pModel)
	{
		m_pModel->Draw(m_d3dContext.Get(), *m_states, m_world, m_Camera->GetView(), m_Camera->GetProjection());
	}
}
