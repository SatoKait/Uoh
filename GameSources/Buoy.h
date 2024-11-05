#pragma once
/*!
@file Buoy.h
@brief É|Å[ÉãÇÃíËã`
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Buoy : public GameObject
	{
		shared_ptr<Transform>m_ptrTrans;
		wstring m_meshResName;
		wstring m_Reskey;
		Vec3 m_Scale;

	public:
		Buoy(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_meshResName(L"DEFAULT_SPHERE"),
			m_Scale(0.1f),
			m_Reskey(L"RED_TX")
		{
		}

		void OnCreate();
	};

}
