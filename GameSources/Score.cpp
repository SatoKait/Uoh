/*!
@file Score.cpp
@brief スコアの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Score::OnCreate()
	{
		//m_Trans = GetComponent<Transform>();
		//m_Trans->SetPosition(m_Position);



		const int numPlaces = 5;
		m_numberSprites.reserve(numPlaces);
		int place = 10000;

		for (int i = 0; i < numPlaces; i++)
		{
			auto stage = GetStage();
			number = stage->AddGameObject<ScoreSprite>();
			m_numberTrans = number->GetComponent<Transform>();
			m_numberTrans->SetPosition(-50 * 0.5f - 50.0f * (numPlaces - i), 800 * 0.5f, 0.0f);
			number->UpdateValue(m_score / place % 10);
			place /= 10;
			m_numberSprites.push_back(number);
		}
	}

	void Score::OnDraw()
	{
		//200 * 0.5f - 50.0f * (numPlaces - i), -50 * 0.5f, 0.0f
		//for (const auto& number : m_numberSprites)
		//{
		//	number->OnDraw();
		//}
	}

	void Score::OnUpdate()
	{	auto stage = GetStage();
	    m_score = App::GetApp()->GetScene<Scene>()->GetScore();//更新で最新の数字を見る
		int place = 10000;	
		for (int i = 0; i < m_numberSprites.size(); ++i) {
			
			int digit = (m_score / place) % 10;// 現在の桁の数字を計算
			m_numberSprites[i]->UpdateValue(digit);// スプライトの数字を更新
			place /= 10;// 次の桁に移動
		}
	}
}

namespace basecross {

	//初期化
	void StageScore::OnCreate()
	{
		//m_Trans = GetComponent<Transform>();
		//m_Trans->SetPosition(m_Position);

		const int numPlaces = 5;
		m_numberSprites.reserve(numPlaces);
		int place = 10000;

		for (int i = 0; i < numPlaces; i++)
		{
			auto stage = GetStage();
			number = stage->AddGameObject<ScoreSprite>();
			m_numberTrans = number->GetComponent<Transform>();
			m_numberTrans->SetPosition(200 * 0.5f - 50.0f * (numPlaces - i), -50 * 0.5f, 0.0f);
			number->UpdateValue(m_score / place % 10);
			place /= 10;
			m_numberSprites.push_back(number);
		}
	}

	void StageScore::OnUpdate()
	{
		auto stage = GetStage();
		m_score = App::GetApp()->GetScene<Scene>()->GetScore();//更新で最新の数字を見る
		int place = 10000;
		for (int i = 0; i < m_numberSprites.size(); ++i) {

			int digit = (m_score / place) % 10;// 現在の桁の数字を計算
			m_numberSprites[i]->UpdateValue(digit);// スプライトの数字を更新
			place /= 10;// 次の桁に移動
		}
	}
}

namespace basecross {

	//初期化
	void TargetsScore::OnCreate()
	{
		//m_Trans = GetComponent<Transform>();
		//m_Trans->SetPosition(m_Position);

		const int numPlaces = 5;
		m_numberSprites.reserve(numPlaces);
		int place = 10000;

		for (int i = 0; i < numPlaces; i++)
		{
			auto stage = GetStage();
			number = stage->AddGameObject<ScoreSprite>();
			m_numberTrans = number->GetComponent<Transform>();
			m_numberTrans->SetPosition(500 * 0.5f - 50.0f * (numPlaces - i), 800 * 0.5f, 0.0f);
			number->UpdateValue(m_score / place % 10);
			place /= 10;
			m_numberSprites.push_back(number);
		}
	}
}

