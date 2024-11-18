/*!
@file TitleStage.h
@brief タイトルステージ
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
		void CreateViewLight(); //ビューの作成
		void CreateSprite();
		void CreateBGM();

	public:
		TitleStage() : Stage() {}
		virtual ~TitleStage() {}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		virtual void OnDestroy() override;
	};

}
//end basecross
