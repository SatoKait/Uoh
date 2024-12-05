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
		// BGM	
		shared_ptr<SoundItem> m_stageBGM;	

		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SingleView> m_View;//ビューの変数

		//ステージの倍率
		float m_StageRation;
		//ステージの時間
	    float m_ToTalTime;
		float m_ToTalTime2;
		int m_ToStartTime;
		bool m_isStartFlag;
		bool m_TimeFlag;
		bool m_Flag;
		bool DrawFlag;
		wstring m_Number;

		// BGMの再生
		void CreateBGM();

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
		void CreateStageTime();
		void CreatePollCollision();
		void CreateFloatCircle();
		void CreateWave();
		void CreateMoveCamera();

		void CameraSetting(const shared_ptr<GameObject>& ptrObj);


	public:
		bool m_GoalFlag;
		//構築と破棄
		GameStage();
		virtual ~GameStage() 
		{
		}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//virtual void OnDestroy()override;

		
	};


}
//end basecross

