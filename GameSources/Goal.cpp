/*!
@file Goal.cpp
@brief ゴール実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Goal::OnCreate()
	{
		//初期位置などの設定
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_scale);
		m_ptrTrans->SetPosition(m_position);
		m_ptrTrans->SetRotation(m_rotate);

		auto col = AddComponent<CollisionObb>();



		col->SetFixed(true);
		col->SetDrawActive(true);

		AddTag(L"Goal");

	}
	void Goal::OnUpdate()
	{
		// デルタタイムを取得する
		float delta = App::GetApp()->GetElapsedTime(); // 前フレームからの「経過時間」
		m_score += delta;

		m_ptrTrans->SetPosition(Vec3(m_position.x, m_position.y, m_position.z));
		m_position.z += 10.0f * delta * m_Speed;

		//ステージの取得
		auto stage = GetStage();

		////プレイヤーの参照
		auto ptrplayer = stage->GetSharedGameObject<Player>(L"Player");
		auto ptrplayerFlag = ptrplayer->m_SpeedUp;

		if (ptrplayerFlag == true)
		{
			m_Speed = 2.5f;
		}
		else {
			m_Speed = 1.0f;
		}


	}
}
//end basecross
