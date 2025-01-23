/*!
@file NPC.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include <cstdlib>  // rand()とsrand()を使用するために必要
#include <ctime>    // time()を使用するために必要

namespace basecross {
	NPC::NPC(shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		Actor(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_CircleCount(0),
		m_Time(0.0f)
	{
	}

	NPC::~NPC() {};

	// 初期化
	void NPC::OnCreate()
	{
		AddTag(L"NPC");
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		auto m_ptrAction = AddComponent<Action>();
		const float debug = 0.3f, lotsec = 0.5f,
			deg180 = XM_PI, deg90 = XM_PIDIV2, deg45 = XM_PIDIV4,
			jump = 9.5f, UpTime = 1.4f, DownTime = 1.8f, JumpTime = UpTime + DownTime;
		bool debugFlag = false, JumpFlag[6] = { 0 };
		srand(static_cast<unsigned int>(time(0)));

		bool JumpTrue[6];
		for (int i = 0; i < 6; i++)
		{
			JumpTrue[i] = rand() % 2;
			std::cout << JumpTrue[i];

		}

		if (debugFlag == false)
		{
			m_ptrAction->AddMoveBy(4.0f, Vec3(0.0f));
			m_ptrAction->AddMoveBy(2.0f, Vec3(-15.0f, 0, 7.0f));
			m_ptrAction->AddMoveBy(UpTime, Vec3(0.0f, jump, 8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear); // 1
			m_ptrAction->AddMoveBy(DownTime, Vec3(-15.0f, -jump, 5.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			if (JumpTrue[0])
			{
				m_ptrAction->AddMoveBy(0.2f, Vec3(0.0f, 0, 2.0f));//2
				m_ptrAction->AddMoveBy(UpTime, Vec3(0.0f, jump, 5.0f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);
				m_ptrAction->AddMoveBy(DownTime, Vec3(0.0f, -jump, 8.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			}
			else
			{
				m_ptrAction->AddMoveBy(JumpTime + 0.2f, Vec3(0.0f, 0, 15.0f));//2
			}
			if (JumpTrue[1])
			{
				m_ptrAction->AddMoveBy(0.7f, Vec3(0.0f, 0, 2.0f));// 3(輪)
				m_ptrAction->AddMoveBy(UpTime, Vec3(0.0f, jump, 8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);
				m_ptrAction->AddMoveBy(DownTime, Vec3(0.0f, -jump, 12.5f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			}
			else
			{
				m_ptrAction->AddMoveBy(JumpTime + 0.7f, Vec3(0.0f, 0, 23.0f));//3(輪)
			}
			if (JumpTrue[2])
			{
				m_ptrAction->AddMoveBy(0.5f, Vec3(0.0f, 0, 2.5f));// 4
				m_ptrAction->AddMoveBy(UpTime, Vec3(0.0f, jump, 8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);
				m_ptrAction->AddMoveBy(DownTime, Vec3(15.0f, -jump, 7.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			}
			else
			{
				m_ptrAction->AddMoveBy(0.5f, Vec3(0.0f, 0, 2.5f));// 4
				m_ptrAction->AddMoveBy(UpTime, Vec3(0.0f, 0, 8.5f));
				m_ptrAction->AddMoveBy(DownTime, Vec3(15.0f, 0, 7.0f));
			}
			
			m_ptrAction->AddMoveBy(UpTime, Vec3(0.0f, jump, 8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);// 5
			m_ptrAction->AddMoveBy(DownTime, Vec3(5.0f, -jump, 1.5f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			m_ptrAction->AddMoveBy(2.8f, Vec3(10.0f, 0, -35.5f));
			m_ptrAction->AddMoveBy(UpTime, Vec3(0.0f, jump, -10.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);// 6(中央)
			m_ptrAction->AddMoveBy(DownTime, Vec3(1.5f, -jump, -17.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			m_ptrAction->AddMoveBy(1.5f, Vec3(8.5f, 0, -18.5f));
			m_ptrAction->AddMoveBy(1.0f, Vec3(5.0f, 0, 1.5f));
			m_ptrAction->AddMoveBy(UpTime, Vec3(0.0f, jump, 8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);// 7
			m_ptrAction->AddMoveBy(DownTime, Vec3(15.0f, -jump, 4.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);

			if (JumpTrue[3])
			{
				m_ptrAction->AddMoveBy(0.2f, Vec3(0.0f, 0, 3.0f));// 8
				m_ptrAction->AddMoveBy(UpTime, Vec3(0.0f, jump, 7.0f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);
				m_ptrAction->AddMoveBy(DownTime, Vec3(0.0f, -jump, 8.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			}
			else
			{
				m_ptrAction->AddMoveBy(JumpTime + 0.2, Vec3(0.0f, 0, 15.0f));// 8
			}

			if (JumpTrue[4])
			{
				m_ptrAction->AddMoveBy(UpTime + 0.35f, Vec3(0.0f, jump, 8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);// 9(輪)
				m_ptrAction->AddMoveBy(DownTime + 0.35f, Vec3(0.0f, -jump, 12.5f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			}
			else
			{
				m_ptrAction->AddMoveBy(JumpTime + 0.7f, Vec3(0.0f, 0, 23.0f));//9(輪)
			}

			if (JumpTrue[5])
			{
				m_ptrAction->AddMoveBy(0.2f, Vec3(0.0f, 0, 3.0f));
				m_ptrAction->AddMoveBy(UpTime, Vec3(0.0f, jump, 8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);// 10
				m_ptrAction->AddMoveBy(DownTime, Vec3(-9.5f, -jump, 12.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			}
			else
			{
				m_ptrAction->AddMoveBy(UpTime + 0.1f, Vec3(0.0f, 0, 8.5f));// 10
				m_ptrAction->AddMoveBy(DownTime + 0.1f, Vec3(-9.0f, 0, 15.0f));
			}

			m_ptrAction->AddMoveBy(1.0f, Vec3(-2.0f, 0, 7.5f));
			m_ptrAction->AddMoveBy(1.0f, Vec3(-3.0f, 0, -4.5f));
			m_ptrAction->AddMoveBy(UpTime, Vec3(-1.0f, jump, -10.0f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);  // 11
			m_ptrAction->AddMoveBy(DownTime, Vec3(0.0f, -jump, -7.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			m_ptrAction->AddMoveBy(2.5f, Vec3(-14.0f, 0, -20.0f));
			m_ptrAction->AddMoveBy(UpTime, Vec3(0.0f, jump, -8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear); // 12(中央)
			m_ptrAction->AddMoveBy(DownTime, Vec3(0.0f, -jump, -20.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			m_ptrAction->AddMoveBy(1.5f, Vec3(0.0f, 0, -18.5f));

			// 回転
			m_ptrAction->AddRotateInterval(4.0f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, -deg45, 0));
			m_ptrAction->AddRotateInterval(0.8f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, deg45, 0));
			m_ptrAction->AddRotateInterval(1.0f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, -deg45, 0));
			m_ptrAction->AddRotateInterval(1.7f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, deg45, 0));
			m_ptrAction->AddRotateInterval(7.4f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, deg45, 0));
			m_ptrAction->AddRotateInterval(2.0f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, -deg45, 0));
			m_ptrAction->AddRotateInterval(1.5f);
			m_ptrAction->AddRotateBy(lotsec * 4, Vec3(0, -deg180, 0));
			m_ptrAction->AddRotateInterval(6.5f);
			m_ptrAction->AddRotateBy(lotsec * 4, Vec3(0, deg180, 0));
			m_ptrAction->AddRotateInterval(0.8f);
			m_ptrAction->AddRotateBy(lotsec * 2, Vec3(0, deg45, 0));
			m_ptrAction->AddRotateInterval(0.8f);
			m_ptrAction->AddRotateBy(lotsec * 2, Vec3(0, -deg45, 0));
			m_ptrAction->AddRotateInterval(7.6f);
			//m_ptrAction->AddRotateInterval(5.5f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, -deg45, 0));
			m_ptrAction->AddRotateInterval(1.5f);
			m_ptrAction->AddRotateBy(2.0f, Vec3(0, deg180 + deg45, 0));
			m_ptrAction->AddRotateInterval(11.2f);
			m_ptrAction->AddRotateBy(0.0f, Vec3(0, deg180, 0));

		}
		else
		{
			// 移動
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 0.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(-15.0f, 0, 5.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(-15.0f, 0, 5.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 33.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(15.0f, 0, 5.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(5.0f, 0, 1.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(10.0f, 0, -35.5f)); //10
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, -8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(10.0f, 0, -35.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(5.0f, 0, 1.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(15.0f, 0, 4.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 33.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(-9.0f, 0, 15.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(-2.0f, 0, 5.0f)); //20
			m_ptrAction->AddMoveBy(debug, Vec3(-5.0f, 0, -10.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(-12.0f, 0, -30.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, -8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, -40.0f));
		}

		//ループする
		m_ptrAction->SetLooped(true);
		//アクション開始
		m_ptrAction->Run();

		//衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetFixed(false);
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		//描画処理
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"TOBIUO_MESH");
		ptrDraw->SetTextureResource(L"TOBIUO_TX");
		ptrDraw->SetOwnShadowActive(true);

	}

	void NPC::OnUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_Time += elapsedTime;
		auto ptrMana = App::GetApp()->GetXAudio2Manager();

		if (m_Time >= 20.0f)
		{
			ptrMana->Start(L"PointSE", 0, 1.0f);

			App::GetApp()->GetScene<Scene>()->AddScore2(100);
			App::GetApp()->GetScene<Scene>()->AddPoint2(100);
			m_Time = 0.0f;
		}
	}

	void NPC::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto stage = GetStage();
		auto ptrMana = App::GetApp()->GetXAudio2Manager();

		auto ptrCircle = stage->GetSharedGameObject<FloatCircle>(L"FloatCircle");

		// デルタタイムを取得する
		float delta = App::GetApp()->GetElapsedTime(); // 前フレームからの「経過時間」
		auto  Time = 0;
		auto  flag = false;

		auto ScoreFlag = false;
		auto playercicle = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto cicle = playercicle->m_CircleCount;

		if (other->FindTag(L"FloatCircle") && ScoreFlag == false)
		{
			ptrMana->Start(L"PointSE", 0, 1.0f);

			ScoreFlag = true;
			auto ciclenext = ptrCircle->m_next++;
			auto comboCount = ptrCircle->m_ComboCount;
			comboCount++;
			if (ScoreFlag && comboCount == 1)
			{
				if (m_CircleCount < 5)
				{
					m_CircleCount++;
					playercicle->m_CircleCount = 0;
				}
				App::GetApp()->GetScene<Scene>()->AddScore2(100 * m_CircleCount);
				App::GetApp()->GetScene<Scene>()->AddPoint2(100 * m_CircleCount);
				ScoreFlag = false;
				comboCount--;
			}
		}

	}

}
//end basecross
