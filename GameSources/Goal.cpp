/*!
@file Goal.cpp
@brief ƒS[ƒ‹À‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Goal::OnCreate()
	{
		//‰ŠúˆÊ’u‚È‚Ç‚Ìİ’è
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_scale);
		ptrTransform->SetPosition(m_position);
		ptrTransform->SetRotation(m_rotate);

		//m_ptrColl->SetFixed(true);
		//m_ptrColl->SetDrawActive(true);

		AddTag(L"Goal");

	}
}
//end basecross
