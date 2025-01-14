#pragma once
/*!
@file Block.h
@brief ブロッククラスの定義
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Block : public GameObject
	{
		wstring m_meshResName;
	public:
		Block(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_meshResName(L"DEFAULT_CUBE")

		{
		}

		void OnCreate();
	};

}
