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
			m_place1(100),
			m_place2(100)
		{
		}

		StageScore:: ~StageScore() {}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
	};

	//--------------------------------------------------------------------------------------
	//　Targetsスコアクラス	
	//--------------------------------------------------------------------------------------
	class TargetsScore : public GameObject
	{
		vector<shared_ptr<ScoreSprite>> m_numberSprites;
		shared_ptr<ScoreSprite>number;

	public:
		shared_ptr<Transform> m_numberTrans;
		int m_score;
		int m_nowScore;

		// 構築と破棄
		TargetsScore::TargetsScore(const shared_ptr<Stage>& StagePtr
		) :
			GameObject(StagePtr),
			m_score(1000)
		{
		}

		TargetsScore:: ~TargetsScore() {}

		virtual void OnCreate() override; // 初期化
	};


}
//end basecross
