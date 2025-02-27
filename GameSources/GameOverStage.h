/*!
@file Character.h
@brief ƒQ[ƒ€ƒI[ƒo[éŒ¾
@authors SatouKaito AndouTinami YoshidaTomoki
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
		float trans;
		bool m_flag;
		bool m_flag2;

	public:
		GameOverStage() : Stage() {}
		virtual ~GameOverStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

	};

	class Model3 : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_StartRot;
		bool m_TextureUse;

	public:
		//\’z‚Æ”jŠü
		Model3(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& StartRot);
		virtual ~Model3();
		//‰Šú‰»
		virtual void OnCreate() override;
	};

	class Model4 : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_StartRot;
		bool m_TextureUse;

	public:
		//\’z‚Æ”jŠü
		Model4(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& StartRot);
		virtual ~Model4();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end basecross
