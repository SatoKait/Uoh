/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class GoalScene : public Stage
	{
		void CreateViewLight();
		InputHandler<GoalScene> m_InputHandler;

	public:
		GoalScene() : Stage() {}
		virtual ~GoalScene() {}

		virtual void OnCreate() override;
		//virtual void OnUpdate() override;

	};


}
//end basecross
