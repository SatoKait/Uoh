/*!
@file TitleStage.h
@brief タイトルステージ
@authors SatouKaito AndouTinami YoshidaTomoki
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleStage : public Stage
	{
		// BGM
		shared_ptr<SoundItem> m_stageBGM;
		shared_ptr<SoundItem> m_stageBGM2;

		InputHandler<TitleStage> m_InputHandler;
		shared_ptr<GameObject> m_SelectStage1;
		shared_ptr<GameObject> flyingfish;

		void CreateViewLight(); //ビューの作成
		void CreateSprite();
		void CreateBGM();

		float m_comX;
		float m_comY;
		float deg;
		float deg2;
		float rad;
		float rad2;
		bool m_flag;
		float m_Flag;

	public:
		TitleStage() : Stage() {}
		virtual ~TitleStage() {}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		virtual void OnDestroy() override;
	};

	class Model1 : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_StartRot;
		bool m_TextureUse;

		bool m_flag;
		float m_comX;

	public:
		//構築と破棄
		Model1(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& StartRot);
		virtual ~Model1();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void ChangeAnimation(const wstring& animationName);
	};

}
//end basecross
