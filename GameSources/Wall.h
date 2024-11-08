#pragma once
/*!
@file Wall.h
@brief “§–¾‚Ì•Ç’è‹`
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Wall : public GameObject
	{
		shared_ptr<Transform>m_ptrTrans;
		Vec3 m_Position;
		Vec3 m_Scale;


	public:
		Wall(const std::shared_ptr<Stage>& stage, const Vec3& Position,const Vec3& Scale) :
			GameObject(stage),
			m_Position(Position),
			m_Scale(Scale)

		{
		}

		void OnCreate();
	};
}

