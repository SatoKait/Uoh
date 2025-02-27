/*!
@file GoalScene.h
@brief ƒS[ƒ‹ƒV[ƒ“‚ÌéŒ¾
@authors SatouKaito AndouTinami YoshidaTomoki
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class GoalScene : public Stage
	{
		shared_ptr<GameObject> crown;
		shared_ptr<SoundItem> m_stageBGM;
		InputHandler<GoalScene> m_InputHandler;

		void CreateViewLight();
		void CreateScore();
		void CreateSprite();
		void CreateBGM();

		float deg;
		float rad;
		float m_comY;
		bool m_flag;

	public:
		GoalScene() : Stage() {}
		virtual ~GoalScene() {}

		virtual void OnCreate() override;
	    virtual void OnUpdate() override;
		virtual void OnDestroy() override;

	};

	class Model2 : public GameObject {
		Vec3 m_StartPos;
		wstring m_TextureUse;
	public:
		//\’z‚Æ”jŠü
		Model2(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~Model2();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	class Model5 : public GameObject {
		Vec3 m_StartPos;
		wstring m_TextureUse;
	public:
		//\’z‚Æ”jŠü
		Model5(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~Model5();
		//‰Šú‰»
		virtual void OnCreate() override;
	};
}
//end basecross
