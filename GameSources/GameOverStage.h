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
		shared_ptr<GameObject> flyingfish;

		void CreateViewLight();
		void CreateScore();
		void CreateSprite();
		void CreateBGM();

		float deg;
		float rad;
		bool m_flag;

	public:
		GameOverStage() : Stage() {}
		virtual ~GameOverStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

	};

	class Model4 : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_StartRot;
		bool m_TextureUse;

	public:
		//構築と破棄
		Model4(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& StartRot);
		virtual ~Model4();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end basecross
