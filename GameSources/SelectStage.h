/*!
@file StageSelect.h
@brief ステージセレクト
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class SelectStage : public Stage
	{
		InputHandler<SelectStage> m_InputHandler;
		shared_ptr<GameObject> m_SelectStage1;
		void CreateViewLight(); //ビューの作成
		void CreateSprite();
		void SwitchSelect();

		int m_select;

	public:
		SelectStage() : Stage() {}
		virtual ~SelectStage() {}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
	};

}
//end basecross
