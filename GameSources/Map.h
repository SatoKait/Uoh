/*!
@file Map.h
@brief マップの定義
@authors YoshidaTomoki
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Map : public GameObject
	{
	public:
		Map(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)

		{
		}

		void OnCreate();
	};

}
