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
		int GameScore;

		// 構築と破棄
		Score(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_score(App::GetApp()->GetScene<Scene>()->m_Score),
			m_nowScore(0)
		{
		}
		virtual ~Score()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnDraw() override; // 描画
		virtual void OnUpdate() override; // 更新


		void UpdateScore()
		{
			int score = m_score;//スコアをメンバ変数から拝借して
			//ポリゴンそのものを書き換える事ができない
			int place = 10000000;
			for (auto& number : m_numberSprites)
			{
				number->UpdateValue(score / place % 10);
				place /= 10;//スコア自身から10削る//ここが右から削っていくみたいなものなので桁を用意した方が良い
			}
		}
	};
}
//end basecross
