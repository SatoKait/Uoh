/*!
@file Wall.cpp
@brief “§–¾‚Ì•Ç‚ÌŽÀ‘Ì
@authors SatouKaito YoshidaTomoki
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Wall::OnCreate() {
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_Scale);
		m_ptrTrans->SetPosition(m_Position);
		m_ptrTrans->SetRotation(m_Rotate);

		auto col = AddComponent<CollisionObb>();
		col->SetDrawActive(m_DrawFlag);
		col->SetFixed(true);
	}
}
