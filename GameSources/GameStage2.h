/*!
@file GameStage2.h
@brief タイトルステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameStage2 : public Stage
	{
		InputHandler<GameStage2> m_InputHandler;
		shared_ptr<GameObject> m_SelectStage1;
		void CreateViewLight(); //ビューの作成
		void CreateSprite();

	public:
		GameStage2() : Stage() {}
		virtual ~GameStage2() {}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
	};

}
//end basecross
