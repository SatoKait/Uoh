/*!
@file Wall.h
@brief “§–¾‚Ì•Ç’è‹`
@authors SatouKaito YoshidaTomoki
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Wall : public GameObject
	{
		shared_ptr<Transform>m_ptrTrans;
		Vec3 m_Position;
		Vec3 m_Scale;
		Vec3 m_Rotate;
		bool m_DrawFlag;

	public:
		Wall(const std::shared_ptr<Stage>& stage, const Vec3& Position,const Vec3& Scale,const Vec3& m_Rotate) :
			GameObject(stage),
			m_Position(Position),
			m_Scale(Scale),
			m_Rotate(m_Rotate),
			m_DrawFlag(false)

		{
		}

		void OnCreate();
	};
}

