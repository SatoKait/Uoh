/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//enum class CameraSelect {
	//	openingCamera,
	//	myCamera,
	//	objCamera,
	//};

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		// BGM	
		shared_ptr<SoundItem> m_stageBGM;	

		shared_ptr<SoundItem> m_BGM;

		shared_ptr<SingleView> m_View;//ビューの変数

		
		//OpeningCamera用のビュー
		//shared_ptr<SingleView> m_OpeningCameraView;
		////MyCamera用のビュー
		//shared_ptr<SingleView> m_MyCameraView;
		////ObjCamera用のビュー
		//shared_ptr<SingleView> m_ObjCameraView;
		//CameraSelect m_CameraSelect;
		int count;
		int m_SetCount;
		int m_Set2Count;
		//ステージの倍率
		float m_StageRation;
		//ステージの時間
	    float m_ToTalTime;
		float m_ToTalTime2;
	    float m_ToStartTime;
		float m_EndTime;
		bool  m_isStartFlag;
		bool  m_TimeFlag;
		bool  m_Flag;
		bool  m_DrawFlag;
		bool  m_EndFlag;
		bool m_isStartFlag;
		bool m_TimeFlag;
		bool m_Flag;
		bool DrawFlag;
		bool m_30secFlag;
		bool m_TimeUpFlag;
		float m_TimeUpAfter;
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
		void CreateComboSprite();
		//ゴール
		void CreateGoal();
		//時間
		void CreateTime();
		void CreateStageTime();
		void CreatePollCollision();
		void CreateFloatCircle();
		void CreateWave();
		//カメラについて
		void CreateMoveCamera();
		void CreateCameraman();
		void CameraSetting(const shared_ptr<GameObject>& ptrObj);

		void CreateNPC();

	public:
		bool m_GoalFlag;
		bool gaugeFlag;
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