/*!
@file StageSelect.h
@brief ステージセレクト
@authors SatouKaito
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class SelectStage : public Stage
	{
		InputHandler<SelectStage> m_InputHandler;
		shared_ptr<GameObject> m_SelectStage1;
		shared_ptr<GameObject> m_Ptr1;
		shared_ptr<GameObject> m_Ptr2;

		void CreateViewLight(); //ビューの作成
		void CreateSprite();
		void SwitchSelect();
		void CreateSelect();
		int m_select;

	public:
		SelectStage() : Stage() {}
		virtual ~SelectStage() {}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
	};

}
//end basecross
