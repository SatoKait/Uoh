/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameOverStage : public Stage
	{
		shared_ptr<SoundItem> m_stageBGM;
		InputHandler<GameOverStage> m_InputHandler;

		void CreateViewLight();
		void CreateScore();
		void CreateSprite();
		void CreateBGM();


	public:
		GameOverStage() : Stage() {}
		virtual ~GameOverStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

	};


}
//end basecross
