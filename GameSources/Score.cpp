/*!
@file Score.cpp
@brief ƒXƒRƒA‚ÌÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//‰Šú‰»
	void Score::OnCreate()
	{
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

	void Score::OnDraw()
	{
		//for (const auto& number : m_numberSprites)
		//{
		//	number->OnDraw();
		//}
	}

	void Score::OnUpdate()
	{	
		auto stage = GetStage();
		m_score = App::GetApp()->GetScene<Scene>()->GetScore();

		const int numPlaces = 5;
		m_numberSprites.reserve(numPlaces);
		int place = 10000;
		for (int i = 0; i < numPlaces; i++)
		{
			m_numberTrans = number->GetComponent<Transform>();
			m_numberTrans->SetPosition(200 * 0.5f - 50.0f * (numPlaces - i), -50 * 0.5f, 0.0f);
			number->UpdateValue(m_score / place % 10);
			place /= 10;
			m_numberSprites.push_back(number);
		}

	}
}
