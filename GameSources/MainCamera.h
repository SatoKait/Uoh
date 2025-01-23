/*!
@file MainCamera.h
@brief カメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	MyCameraカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	class MainCamera :public Camera {

		weak_ptr<Transform> m_targetTrans;
		weak_ptr<GameObject> m_Target;
		//shared_ptr<Player> m_Player;
		shared_ptr<Stage> m_stage;

		float m_angleY;
		float m_distance;
		float m_height;
		float m_camDis;
		Vec3 m_playerAngle;

	public:
		Vec2 m_ret;
		float m_MoveFlag;
		MainCamera(float angleY);
		MainCamera();
		virtual ~MainCamera() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		shared_ptr <GameObject> GetTarget()const
		{
			return m_Target.lock();
		}

		void SetTarget(const shared_ptr <GameObject>& target);
		void SetAngleY(const float& angle)
		{
			m_angleY = angle;
		}
    
		float m_at;
	};
}
//end basecross
