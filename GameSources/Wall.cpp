/*!
@file Wall.cpp
@brief “§–¾‚Ì•Ç‚ÌŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Wall::OnCreate() {
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_Scale);
		m_ptrTrans->SetPosition(m_Position);

		auto col = AddComponent<CollisionObb>();
		col->SetDrawActive(true);
		col->SetFixed(true);
	}
}
