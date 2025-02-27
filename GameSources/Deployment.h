/*!
@file Deployment.h
@brief オブジェクト配置宣言
@authors YoshidaTomoki
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Deployment : public GameObject
	{
		//Vec3 m_stratPos;
		float m_Speed;
		float m_Side;
		float m_Warp;

	public:
		Deployment(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			//m_stratPos(m_Side,0.0f, m_Warp),
			m_Speed(1.0f),
			m_Side(0.0f),
			m_Warp(0.0f)
		{
		}

		void OnCreate();
		//void OnUpdate();
	};

}

namespace basecross {
	class Deployment2: public GameObject
	{
		//Vec3 m_stratPos;
		float m_Speed;
		float m_Side;
		float m_Warp;

	public:
		Deployment2(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			//m_stratPos(m_Side,0.0f, m_Warp),
			m_Speed(1.0f),
			m_Side(0.0f),
			m_Warp(0.0f)
		{
		}

		void OnCreate();
		//void OnUpdate();
	};
}

