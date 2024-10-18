/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ステージの倍率
		float m_StageRation;

		//ビューの作成
		void CreateViewLight();
		//ステージ
		void CreateGround();
		//障害物
		void CreateObstacle();

	public:
		//構築と破棄
		GameStage();
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
	};


}
//end basecross

