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
		float m_ToTalTime;

		//ビューの作成
		void CreateViewLight();
		// プレイヤーの作成
		void CreatePlayer();
		//壁
		void CreateWall();
		//ステージ
		void CreateGround();
		//障害物
		void CreateObstacle();
		//スプライト
		void CreateTraceSprite();
		//ゴール
		void CreateGoal();
		//時間
		void CreateTime();
		shared_ptr<SingleView> m_View;//ビューの変数

	public:
		//構築と破棄
		GameStage();
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		
	};


}
//end basecross

