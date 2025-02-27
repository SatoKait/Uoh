/*!
@file Goal.h
@brief ÉSÅ[Éã
@authors SatouKaito
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Goal : public GameObject
	{
		Vec3 m_scale;
		Vec3 m_position;
		Vec3 m_rotate;
	public:
		static Vec3 position;

		float m_Speed;
		float m_score;
		shared_ptr<CollisionObb> m_ptrColl;

		shared_ptr<Transform> m_ptrTrans;

	public:
		//ç\ízÇ∆îjä¸
		Goal(const shared_ptr<Stage>& stage,
			const Vec3& Position,
			const Vec3& Scale,
			const Vec3& Rotate
		):
			GameObject(stage),
			m_scale(Scale),
			m_position(Position),
			m_rotate(Rotate),
			m_Speed(1.0f)
		{
		}
		Goal::~Goal() {}

		//èâä˙âª
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};
}
//end basecross
