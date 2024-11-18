/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class GoalScene : public Stage
	{
		shared_ptr<SoundItem> m_stageBGM;
		InputHandler<GoalScene> m_InputHandler;

		void CreateViewLight();
		void CreateScore();
		void CreateSprite();
		void CreateBGM();


	public:
		GoalScene() : Stage() {}
		virtual ~GoalScene() {}

		virtual void OnCreate() override;
	    virtual void OnUpdate() override;
		virtual void OnDestroy() override;

	};


}
//end basecross
