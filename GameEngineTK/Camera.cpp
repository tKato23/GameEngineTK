//	ヘッダファイルのインクルード
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	コンストラクタ
Camera::Camera(int width, int height)
{
	//	メンバ変数の初期化
	m_eyepos = Vector3(0, 0, 5);
	m_refpos = Vector3(0, 0, 0);
	m_upvec = Vector3(0, 1, 0);

	m_fovY = XMConvertToRadians(60.0f);
	m_aspect = (float)width / height;
	m_nearclip = 0.1f;
	m_farclip = 1000.0f;

	//	ビュー行列の生成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//	射影行列の生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

//	デストラクタ
Camera::~Camera()
{

}

//	更新
void Camera::Update()
{
	//	ビュー行列の生成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//	射影行列の生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

//	ビュー行列を取得する関数
const Matrix& Camera::GetView()
{
	return m_view;
}

//	射影行列を取得する関数
const Matrix& Camera::GetProjection()
{
	return m_proj;
}

//	視点座標のセットする関数
void Camera::SetEyePos(const Vector3& eyepos)
{
	m_eyepos = eyepos;
}

//	参照点のセット
void Camera::SetRefPos(const Vector3& refpos)
{
	m_refpos = refpos;
}

//	上方向ベクトルのセット
void Camera::SetUpVec(const DirectX::SimpleMath::Vector3 & upvec)
{
	m_upvec = upvec;
}

//	垂直方向視野角のセット
void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

//	アスペクト比のセット
void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

//	ニアクリップのセット
void Camera::SetNearClip(float nearclip)
{
	m_nearclip = nearclip;
}

//	ファークリップのセット
void Camera::SetFarClip(float farclip)
{
	m_farclip = farclip;
}
