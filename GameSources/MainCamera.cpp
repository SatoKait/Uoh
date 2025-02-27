/*!
@file MainCamera.cpp
@brief カメラ実体
@authors SatouKaito YoshidaTomoki
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	MyCameraカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	//構築と破棄
	MainCamera::MainCamera(float angleY) :
		m_angleY(angleY),
		m_distance(13.0f),//6.0
		m_height(1.5f),  //2.5
		m_camDis(5.0f)   //5.0
	{
	}
	MainCamera::MainCamera() :
		m_angleY(90.0f),
		m_distance(6.0f),//6.0
		m_height(1.5f),  //2.5
		m_camDis(5.0f)   //5.0
	{
	}

	void MainCamera::OnCreate() {
		m_MoveFlag = false;
	}

	void MainCamera::OnUpdate() {

		auto delta = App::GetApp()->GetElapsedTime();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto speed = 120.0f;

		if (abs(m_ret.x) > 0.4) {
			m_angleY -= speed * delta * m_ret.x;
		}


		//ディグリー角からラジアン角に直す
		auto rad = XMConvertToRadians(m_angleY);
		Vec3 radVec(cos(rad), 0.0f, sin(rad));

		Vec3 frontVec(cos(XM_PI + rad), 0.0f, sin(XM_PI + rad));

		//カメラの注視点の設定
		auto targetTrans = m_targetTrans.lock();
		auto at = targetTrans->GetPosition();

		at += frontVec * m_camDis;
		m_at = at.y;
		//SetAt(at);

		//カメラの座標点を設定
		auto eye = at + radVec * m_distance;
		eye.y = at.y + m_height;
		SetEye(eye);

	}

	void MainCamera::SetTarget(const shared_ptr <GameObject>& target)
	{
		m_targetTrans = target->GetComponent<Transform>();
	}

}
//end basecross
