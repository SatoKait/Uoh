/*!
@file Character.h
@brief ”wŒi‚ÌéŒ¾
@authors SatouKaito
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Skybox : public GameObject
	{
	public :
		Skybox(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{
		}

		void OnCreate() override;
		//void OnUpdate() override;
	};

}
//end basecross
