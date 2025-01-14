#pragma once
/*!
@file Pole.h
@brief ƒ|[ƒ‹‚Ì’è‹`
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Pole : public GameObject
	{
		shared_ptr<Transform>m_ptrTrans;
		wstring m_meshResName;
		wstring m_Reskey;
		Vec3 m_Scale;

	public:
		Pole(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_meshResName(L"POLL_MESH"),
			m_Scale(0.1f),
			m_Reskey(L"RED_TX")
		{
		}

		void OnCreate();
	};

}
