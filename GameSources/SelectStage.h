/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class SelectStage : public Stage
	{
		InputHandler<SelectStage> m_InputHandler;
		void CreateViewLight(); //ビューの作成

	public:
		SelectStage() : Stage() {}
		virtual ~SelectStage() {}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//void CreateSelect();
		//void SwitchSelect();
	};

}
//end basecross
