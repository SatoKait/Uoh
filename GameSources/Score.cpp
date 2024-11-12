/*!
@file Score.cpp
@brief ƒXƒRƒA‚ÌŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//‰Šú‰»
	void Score::OnCreate()
	{
		//auto& app = App::GetApp();
		//auto scene = app->GetScene<Scene>();
		//m_nowScore = scene->GetScore();

		const int numPlaces = 4;
		m_numberSprites.reserve(numPlaces);
		int place = 1000;

		for (int i = 0; i < numPlaces; i++)
		{
			auto stage = GetStage();
			auto number = stage->AddGameObject<ScoreSprite>();
			m_numberTrans = number->GetComponent<Transform>();
			m_numberTrans->SetPosition(200 * 0.5f - 50.0f * (numPlaces - i), -50 * 0.5f, 0.0f);
			number->UpdateValue(m_score / place % 10);
			place /= 10;
			m_numberSprites.push_back(number);
		}
	}

	void Score::OnDraw()
	{
		for (const auto& number : m_numberSprites)
		{
			number->OnDraw();
		}
	}

	//void Score::OnUpdate()
	//{

	//}
}
