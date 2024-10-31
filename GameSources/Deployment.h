/*!
@file Deployment.h
@brief マップの定義
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Deployment : public GameObject
	{
	public:
		Deployment(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)

		{
		}

		void OnCreate();
	};

}
