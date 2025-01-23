/*!
@file Score.h
@brief  スコア
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//　　スコアクラス	
	//--------------------------------------------------------------------------------------
	class Score : public GameObject
	{
		vector<shared_ptr<ScoreSprite>> m_numberSprites;
		shared_ptr<ScoreSprite>number;

	public:
		shared_ptr<Transform> m_numberTrans;
        int m_score;
		int m_nowScore;

		// 構築と破棄
		Score::Score(const shared_ptr<Stage>& StagePtr
			) :
			GameObject(StagePtr),
			m_score(App::GetApp()->GetScene<Scene>()->m_Score),
			m_nowScore(0)
		{
		}

		Score:: ~Score(){}

		virtual void OnCreate() override; // 初期化
		virtual void OnDraw() override; // 描画
		virtual void OnUpdate() override; // 更新


		//void UpdateScore()
		//{
		//	int score = m_score;//スコアをメンバ変数から拝借して
		//	//ポリゴンそのものを書き換える事ができない
		//	int place = 10000000;
		//	for (auto& number : m_numberSprites)
		//	{
		//		number->UpdateValue(score / place % 10);
		//		place /= 10;//スコア自身から10削る//ここが右から削っていくみたいなものなので桁を用意した方が良い
		//	}
		//}
	};

	//--------------------------------------------------------------------------------------
	//　　Stageスコアクラス	
	//--------------------------------------------------------------------------------------
	class StageScore : public GameObject
	{
		vector<shared_ptr<ScoreSprite>> m_numberSprites;
		shared_ptr<ScoreSprite>number;

	public:
		shared_ptr<Transform> m_numberTrans;
		int m_score;
		int m_nowScore;
		int m_numPlaces;
		int m_numPlaces1;
		int m_numPlaces2;
	    int m_place;
		int m_place1;
		int m_place2;

		// 構築と破棄
		StageScore::StageScore(const shared_ptr<Stage>& StagePtr
		) :
			GameObject(StagePtr),
			m_score(App::GetApp()->GetScene<Scene>()->m_Score),
			m_nowScore(0),
			m_numPlaces(5),//これが5桁で
			m_place(10000),//00000を出すことが出来る
			m_numPlaces1(3),
			m_numPlaces2(4),
		    m_place1(100),
		    m_place2(100)
		{
		}

		StageScore:: ~StageScore() {}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
	};

	//--------------------------------------------------------------------------------------
	//　GaugeScoreスコアクラス	
	//--------------------------------------------------------------------------------------
	class GaugeScore : public GameObject
	{
		shared_ptr<Transform> m_ptrTrans;
		shared_ptr<ScoreSprite>score;
		//バックアップの頂点データ
		vector<VertexPositionColorTexture>m_BackupVertices;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_HpKey;
		bool m_Trace;
		float m_TotalTime;
		float m_Widthsize;
		int m_Hp_now ; //現在のHP
		int m_gauge;
		const int m_Reset = 90;
		const float m_Max_hp = 100; //HPの最大値
		

	public:
		int Count = 0;
		//構築と破壊
		GaugeScore::GaugeScore(const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec3& StartPos,
			const wstring& HpKey

		) :
			GameObject(StagePtr),
			m_Trace(Trace),
			m_StartScale(StartScale),
			m_StartPos(StartPos),
			m_TotalTime(0),
			m_HpKey(HpKey),
			m_Hp_now(50),
			m_gauge(50)

		{}

		GaugeScore::~GaugeScore() {}

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//　GaugeScoreEnemyスコアクラス	
	//--------------------------------------------------------------------------------------
	class GaugeScoreEnemy : public GameObject
	{
		shared_ptr<Transform> m_ptrTrans;
		shared_ptr<ScoreSprite>score;
		//バックアップの頂点データ
		vector<VertexPositionColorTexture>m_BackupVertices;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_HpKey;
		bool m_Trace;
		float m_TotalTime;
		float m_Widthsize;
		int m_Hp_now; //現在のHP
		int m_gauge;
		const int m_Reset = 90;
		const float m_Max_hp = 100; //HPの最大値


	public:
		int Count = 0;
		bool m_isLayerBackGroundFlag;
		//構築と破壊
		GaugeScoreEnemy::GaugeScoreEnemy(const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec3& StartPos,
			const wstring& HpKey

		) :
			GameObject(StagePtr),
			m_Trace(Trace),
			m_StartScale(StartScale),
			m_StartPos(StartPos),
			m_TotalTime(0),
			m_HpKey(HpKey),
			m_Hp_now(50),
			m_gauge(50),
			m_isLayerBackGroundFlag(false)

		{}

		GaugeScoreEnemy::~GaugeScoreEnemy() {}

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//　Gaugeスコアクラス	
	//--------------------------------------------------------------------------------------
	class OverGauge : public GameObject
	{
		shared_ptr<Transform> m_scoreTrans;
		shared_ptr<ScoreSprite>score;


		int m_Hp_now ; //現在のHP
		int m_gauge;
		const int m_Reset = 90;
		const float m_Max_hp = 100; //HPの最大値
		Vec3 m_Position;

	public:
		int Count = 0;
		//構築と破壊
		OverGauge::OverGauge(const shared_ptr<Stage>& StagePtr,
			Vec3 Pos

		) :
			GameObject(StagePtr),
			m_Position(Pos)
		{}

		OverGauge::~OverGauge() {}

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//　PlayerRusultScoreスコアクラス	
	//--------------------------------------------------------------------------------------
	class PlayerRusultScore : public GameObject
	{
		shared_ptr<Transform> m_ptrTrans;
		shared_ptr<ScoreSprite>score;
		//バックアップの頂点データ
		vector<VertexPositionColorTexture>m_BackupVertices;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_HpKey;
		bool m_Trace;
		float m_TotalTime;
		float m_Widthsize;
		float m_DeltaTime;
		bool m_StartFlag;
		int m_Hp_now; //現在のHP
		int m_gauge;
		const int m_Reset = 90;
		const float m_Max_hp = 100; //HPの最大値


	public:
		bool m_ChangeFlag;
		bool m_CreateFlag;
		bool m_UpdateStartFlag;
		int Count = 0;
		bool m_isLayerBackGroundFlag;
		float deltaTime;

		//構築と破壊
		PlayerRusultScore::PlayerRusultScore(const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec3& StartPos,
			const wstring& HpKey

		) :
			GameObject(StagePtr),
			m_Trace(Trace),
			m_StartScale(StartScale),
			m_StartPos(StartPos),
			m_TotalTime(0),
			m_DeltaTime(0.0f),
			m_HpKey(HpKey),
			m_Hp_now(50),
			m_gauge(50),
			m_isLayerBackGroundFlag(false),
			m_ChangeFlag(false),
			m_CreateFlag(false),
			m_StartFlag(false),
			deltaTime(0.0f),
			m_UpdateStartFlag(false)
		{}

		PlayerRusultScore::~PlayerRusultScore() {}

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		bool GetFlag()
		{
			return m_CreateFlag;
		}
	};

	//--------------------------------------------------------------------------------------
	//　NPCRusultScoreスコアクラス	
	//--------------------------------------------------------------------------------------
	class NPCRusultScore : public GameObject
	{
		shared_ptr<Transform> m_ptrTrans;
		shared_ptr<ScoreSprite>score;
		//バックアップの頂点データ
		vector<VertexPositionColorTexture>m_BackupVertices;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_HpKey;
		bool m_Trace;
		float m_TotalTime;
		float m_Widthsize;
		float m_DeltaTime;
		int m_Hp_now; //現在のHP
		int m_gauge;
		const int m_Reset = 90;
		const float m_Max_hp = 100; //HPの最大値


	public:
		int Count = 0;
		float m_Speed;
		bool m_isLayerBackGroundFlag;	
		bool m_EndChangeFlag;
		bool m_UpdateStartFlag;

		//構築と破壊
		NPCRusultScore::NPCRusultScore(const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec3& StartPos,
			const wstring& HpKey

		) :
			GameObject(StagePtr),
			m_Trace(Trace),
			m_StartScale(StartScale),
			m_StartPos(StartPos),
			m_TotalTime(0),
			m_DeltaTime(0.0f),
			m_HpKey(HpKey),
			m_Hp_now(50),
			m_gauge(50),
			m_isLayerBackGroundFlag(false),
			m_EndChangeFlag(false),
			m_Speed(5.0f),
			m_UpdateStartFlag(false)

		{}

		NPCRusultScore::~NPCRusultScore() {}

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};


	//--------------------------------------------------------------------------------------
	//　PlayerResultGaugeスコアクラス	
	//--------------------------------------------------------------------------------------
	class PlayerResultGauge : public GameObject
	{
		shared_ptr<Transform> m_ptrTrans;
		shared_ptr<ScoreSprite>score;
		//バックアップの頂点データ
		vector<VertexPositionColorTexture>m_BackupVertices;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_HpKey;
		bool m_Trace;
		bool m_ResultFlag;
		float m_TotalTime;
		float m_Widthsize;
		float m_DeltaTime;
		int m_Hp_now; //現在のHP
		int m_gauge;
		const int m_Reset = 90;
		const float m_Max_hp = 100; //HPの最大値


	public:
		int Count ;
		float m_Speed;
		bool m_isLayerBackGroundFlag;
		bool m_EndChangeFlag;

		//構築と破壊
		PlayerResultGauge::PlayerResultGauge(const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec3& StartPos,
			const wstring& HpKey

		) :
			GameObject(StagePtr),
			m_Trace(Trace),
			m_StartScale(StartScale),
			m_StartPos(StartPos),
			Count(0),
			m_TotalTime(0),
			m_DeltaTime(0.0f),
			m_HpKey(HpKey),
			m_Hp_now(50),
			m_gauge(50),
			m_isLayerBackGroundFlag(false),
			m_ResultFlag(false)
		{}

		PlayerResultGauge::~PlayerResultGauge() {}

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//　NPCResultGaugeスコアクラス	
	//--------------------------------------------------------------------------------------
	class NPCResultGauge : public GameObject
	{
		shared_ptr<GameStage> m_Stage;
		shared_ptr<Transform> m_ptrTrans;
		shared_ptr<ScoreSprite>score;
		//バックアップの頂点データ
		vector<VertexPositionColorTexture>m_BackupVertices;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_HpKey;
		bool m_Trace;
		bool m_ResultFlag;
		float m_TotalTime;
		float m_Widthsize;
		float m_DeltaTime;
		int m_Hp_now; //現在のHP
		int m_gauge;
		const int m_Reset = 90;
		const float m_Max_hp = 100; //HPの最大値


	public:
		int Count;
		float m_Speed;
		bool m_isLayerBackGroundFlag;
		bool m_EndChangeFlag;

		//構築と破壊
		NPCResultGauge::NPCResultGauge(const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec3& StartPos,
			const wstring& HpKey

		) :
			GameObject(StagePtr),
			m_Trace(Trace),
			m_StartScale(StartScale),
			m_StartPos(StartPos),
			Count(0),
			m_TotalTime(0),
			m_DeltaTime(0.0f),
			m_HpKey(HpKey),
			m_Hp_now(50),
			m_gauge(50),
			m_isLayerBackGroundFlag(false),
			m_ResultFlag(false)
		{}

		NPCResultGauge::~NPCResultGauge() {}

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};


}

//end basecross
