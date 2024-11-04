/*!
@file Goal.h
@brief ÉSÅ[Éã
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


		shared_ptr<CollisionObb> m_ptrColl;


	public:
		//ç\ízÇ∆îjä¸
		Goal(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Position,
			const Vec3& Rotate
		):
			GameObject(stage),
			m_scale(Scale),
			m_position(Position),
			m_rotate(Rotate)
		{
		}
		Goal::~Goal() {}

		//èâä˙âª
		virtual void OnCreate() override;
		//virtual void OnUpdate()override;
	};
}
//end basecross
