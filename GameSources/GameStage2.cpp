/*!
@file　GameStage2.cpp
@brief タイトルなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	// コンストラクタ
	GameStage2::GameStage2() :
		m_StageRation(10.0f), // ステージのサイズ倍率
		m_ToTalTime(30),
		m_ToStartTime(3),
		m_ToTalTime2(1),
		m_isStartFlag(false),
		m_TimeFlag(false),
		m_Flag(false),
		DrawFlag(true)

	{}

	void GameStage2::CreateViewLight() {
		// カメラの設定MainCamera
		auto camera = ObjectFactory::Create<MainCamera>(-90.0f);
		camera->SetEye(Vec3(0.0f, 2.5f, -3.5f));
		//camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// ビューにカメラを設定
		m_View = CreateView<SingleView>();
		m_View->SetCamera(camera);

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}
	void GameStage2::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>(Vec3(0.0f, 0.4f,-20.0f), Vec3(0.25f, 0.25f, 0.25f), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"Player", ptrPlayer);
	}
	void GameStage2::CreateWall()
	{
		auto ptrWall = AddGameObject<Wall>(Vec3(49.0f, 10.0f, 0.0f),    Vec3(1.0f, 20.0f, 100.0f), Vec3(0.0f, 0.0f, 0.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3(-50.0f, 10.0f,   0.0f), Vec3(1.0f, 20.0f, 100.0f),Vec3(0.0f, 0.0f, 0.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3( 34.0f, 10.0f, -49.0f), Vec3(29.0f, 20.0f,  1.0f),Vec3(0.0f, 0.0f, 0.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3(-35.0f, 10.0f, -49.0f), Vec3(29.0f, 20.0f,  1.0f),Vec3(0.0f, 0.0f, 0.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3( 34.0f, 10.0f,  49.0f), Vec3(29.0f, 20.0f,  1.0f),Vec3(0.0f, 0.0f, 0.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3(-35.0f, 10.0f,  49.0f), Vec3(29.0f, 20.0f,  1.0f),Vec3(0.0f, 0.0f, 0.0f));//左の部分

		ptrWall = AddGameObject<Wall>(Vec3(-10.0f, 10.0f, 39.0f),  Vec3(27.5f, 20.0f, 1.0f), Vec3(0.0f, 0.8f, 0.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3( 10.0f, 10.0f, 39.0f),  Vec3(29.0f, 20.0f, 1.0f), Vec3(0.0f, -0.8f, 0.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3(-11.0f, 10.0f, -38.5f), Vec3(28.0f, 20.0f, 1.0f), Vec3(0.0f, -0.8f, 0.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3(10.0f, 10.0f, -39.0f),  Vec3(29.0f, 20.0f, 1.0f), Vec3(0.0f, 0.8f, 0.0f));//左の部分
		
		ptrWall = AddGameObject<Wall>(Vec3( 29.5f, 10.0f,  1.0f), Vec3(20.0f, 20.0f, 21.0f), Vec3(0.0f, 0.0f, 0.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3(-30.5f, 10.0f,  1.0f), Vec3(20.0f, 20.0f, 21.0f), Vec3(0.0f, 0.0f, 0.0f));//左の部分

	}
	void GameStage2::CreateGround() {
		AddGameObject<Ground>(Vec3(0.0f, -1.0f, 0.0f), Vec3(500.0f, 0.5f, 500.0f), L"SEA_TX");
	}
	void GameStage2::CreatePollCollision()
	{
		auto pollCollef = AddGameObject<PollCollision>(Vec3(16.4f, 4.0f, -27.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, 16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(13.8f, 4.0f, -22.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, 16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(38.7f, 4.0f, -27.3f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, -16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(41.4f, 4.0f, -22.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, -16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-41.4f, 4.0f, -27.3f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, -16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-38.7f, 4.0f, -22.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, -16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-13.8f, 4.0f, -27.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, 16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-16.4f, 4.0f, -22.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, 16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(41.4f, 4.0f, 27.3f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, -16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(38.7f, 4.0f, 22.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, -16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(41.4f, 4.0f, 27.3f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, -16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(38.7f, 4.0f, 22.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, -16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(16.4f, 4.0f, 27.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, -16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(13.8f, 4.0f, 22.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, -16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-16.4f, 4.0f, 27.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, 16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-13.8f, 4.0f, 22.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, 16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-38.7f, 4.0f, 27.3f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, -16.8f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-41.4f, 4.0f, 22.5f), Vec3(2.5f, 8.0f, 2.2f), Vec3(0.0f, -16.8f, 0.0f));

		//pollCollision
		auto pollCol = AddGameObject<PollCollision>(Vec3(3.0f, 4.2f, 0.0f), Vec3(1.5f, 7.25f, 2.0f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-3.0f, 4.2f, 0.0f), Vec3(1.5f, 7.25f, 2.0f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(0.0f, 4.5f, 0.0f), Vec3(5.0f, 0.4f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(0.0f, 7.7f, 0.0f), Vec3(5.0f, 0.4f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));

		//CirecleCollision
		auto CirclepollColrig = AddGameObject<PollCollision>(Vec3(-30.0f, 12.75f, 25.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-30.0f, 7.35f, 25.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-29.7f, 10.0f, 28.0f), Vec3(1.7f, 6.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-30.0f, 10.0f, 22.0f), Vec3(1.7f, 6.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		
		CirclepollColrig = AddGameObject<PollCollision>(Vec3(-30.0f, 12.75f, -25.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-30.0f, 7.35f, -25.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-29.7f, 10.0f, -22.2f), Vec3(1.7f, 6.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-30.0f, 10.0f, -27.8f), Vec3(1.7f, 6.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));

		CirclepollColrig = AddGameObject<PollCollision>(Vec3(30.0f, 12.75f, 25.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(30.0f, 7.35f, 25.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(29.7f, 10.0f, 22.2f), Vec3(1.7f, 6.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(30.0f, 10.0f, 27.8f), Vec3(1.7f, 6.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));

		CirclepollColrig = AddGameObject<PollCollision>(Vec3(30.0f, 12.75f, -25.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(30.0f, 7.35f,-25.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(29.7f, 10.0f, -27.8f), Vec3(1.7f, 6.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(30.0f, 10.0f, -22.2f), Vec3(1.7f, 6.0f, 1.2f), Vec3(0.0f, 70.8f, 0.0f));

	}
	void GameStage2::CreateObstacle() {
		auto objPoll = AddGameObject<Poll>(Vec3(0.0f, 6.0f, 0.0f), Vec3(5.0f, 2.5f, 0.5f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll", objPoll);
		auto objPollnol = AddGameObject<Poll1>(Vec3(15.0f, 4.0f, -25.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, 16.8f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll1_1", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(40.0f, 4.0f, -25.0f), Vec3(3.0f, 8.0f, 2.0f),  Vec3(0.0f, -16.8f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll1_2", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(-15.0f, 4.0f, -25.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, 16.8f, 0.0f),  L"RED_TX");
		SetSharedGameObject(L"Poll1_3", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(-40.0f, 4.0f, -25.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, -16.8f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll1_4", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(15.0f, 4.0f, 25.0f),  Vec3(3.0f, 8.0f, 2.0f),  Vec3(0.0f, -16.8f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll1_5", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(40.0f, 4.0f, 25.0f),  Vec3(3.0f, 8.0f, 2.0f),  Vec3(0.0f, -16.8f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll1_6", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(-15.0f, 4.0f, 25.0f), Vec3(3.0f, 8.0f, 2.0f),  Vec3(0.0f, 16.8f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll1_7", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(-40.0f, 4.0f, 25.0f), Vec3(3.0f, 8.0f, 2.0f),  Vec3(0.0f, -16.8f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll1_8", objPollnol);

		auto objCirclePollnol = AddGameObject<CirclePoll>(Vec3(-30.0f, 10.0f, 25.0), Vec3(4.0f, 3.5f, 1.0f), Vec3(0.0f, 70.8f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"CirclePoll1", objCirclePollnol);
		objCirclePollnol = AddGameObject<CirclePoll>(Vec3(-30.0f, 10.0f, -25.0), Vec3(4.0f, 3.5f, 1.0f),     Vec3(0.0f, 70.8f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"CirclePoll2", objCirclePollnol);
		objCirclePollnol = AddGameObject<CirclePoll>(Vec3(30.0f, 10.0f, 25.0), Vec3(4.0f, 3.5f, 1.0f),       Vec3(0.0f, 70.8f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"CirclePoll3", objCirclePollnol);
		objCirclePollnol = AddGameObject<CirclePoll>(Vec3(30.0f, 10.0f, -25.0), Vec3(4.0f, 3.5f, 1.0f),      Vec3(0.0f, 70.8f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"CirclePoll4", objCirclePollnol);

		auto ptrobstacle = AddGameObject<Deployment2>();
	}

	void GameStage2::CreateGoal() {
		//AddGameObject<Goal>(
		//	Vec3(0.0f, 25.0f, -240.0f),//pos z=-240
		//	Vec3(100.0f, 50.0f, 1.0f),//scl
		//	Vec3(0.0f,0.0f,0.0f));//rot
	}
	void GameStage2::CreateFloatCircle()
	{
		// 筒状ポリゴン
		auto Circle = AddGameObject<FloatCircle>(L"LINE_TX"); // 使用するテクスチャキーを設定できる
		Circle->SetHeight(1.0f); // 筒の高さ
		Circle->SetTopRadius(1.0f); // 上の輪の半径
		Circle->SetBottomRadius(1.0f); // 下の輪の半径
		Circle->SetTopColor(1.0f, 1.0f, 1.0f, 1.0f); // 上の方の色
		Circle->SetBottomColor(1.0f, 1.0f, 1.0f, 1.0f); // 下の方の色
		Circle->SetLoops({ 1.0f, 1.0f }); // テクスチャの繰り返し数(U方向とV方向)
		Circle->SetScrollPerSecond({ 0.0f, 0.0f }); // テクスチャアニメーションの速さ（UV方向、秒単位）
		auto cicleTrans = Circle->GetComponent<Transform>();
		cicleTrans->SetPosition(-15.0f, 6.0f, -35.0f);
		cicleTrans->SetRotation(Vec3(XM_PIDIV2, 0.0f, 0.0f));
		cicleTrans->SetScale(Vec3(2.5f, 0.25f, 2.5f));
		SetSharedGameObject(L"FloatCircle", Circle);
	}

	void GameStage2::CreateTime()
	{
		AddGameObject<UITime>(2,
			L"NUMBER2_TX",
			true,
			Vec2(220.0f, 60.0f),
			Vec3(-340.0f, 350.0f, 0.0f));
		AddGameObject<UITime2>(2,
			L"NUMBER2_TX",
			true,
			Vec2(220.0f, 60.0f),
			Vec3(-470.0f, 350.0f, 0.0f));
		AddGameObject<StageSprite>(L"TIME_TX", true,
			Vec2(350.0f, 80.0f), Vec2(-515.0f, 350.0f));
		AddGameObject<StageSprite>(L"PARTITION_TX", true,
			Vec2(500.0f, 100.0f), Vec2(-15.0f, 350.0f));
		auto score = AddGameObject<Score>();
		AddGameObject<TargetsScore>();
		//SetSharedGameObject(L"Score", ptrscore);
		AddGameObject<UITimeStage>(1,
			L"NUMBER2_TX",
			true,
			Vec2(480.0f, 120.0f),
			Vec3(250.0f, 0.0f, 0.0f));
	}

	void GameStage2::CreateBGM() {
		auto ptrMana = App::GetApp()->GetXAudio2Manager();
		m_BGM = ptrMana->Start(L"StageBGM1", XAUDIO2_LOOP_INFINITE, 0.1f);
	}


	void GameStage2::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreatePlayer();
			CreateWall();
			CreateGround();
			CreatePollCollision();
			CreateObstacle();
			CreateGoal();
			CreateFloatCircle();
			CreateTime();
			CreateBGM();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage2::OnUpdate()
	{
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto ptrMana = App::GetApp()->GetXAudio2Manager();

		auto score = App::GetApp()->GetScene<Scene>()->GetScore();
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto GoalFlag = ptrPlayer->m_GoalFlag;

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y)
		{
			int a = 0;
			//ptrMana->Stop(m_BGM);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGoalScene");
		}
		float elapsedTime = App::GetApp()->GetElapsedTime();
		if (m_isStartFlag == false)
		{
			m_ToStartTime -= elapsedTime;
		}
		if (m_ToStartTime <= 0)
		{
			m_isStartFlag = true;
		}

		if (m_isStartFlag)
		{
			m_ToTalTime -= elapsedTime;

			if (m_ToTalTime <= 0 && m_TimeFlag == false)
			{
				m_Flag = true;
				m_TimeFlag = true;
				m_ToTalTime = 60;
			}
			if (m_ToTalTime == 0 && m_TimeFlag == true)
			{
				m_ToTalTime = 0;
			}

			if (m_Flag == true)
			{
				m_ToTalTime2 -= elapsedTime;

			}
			if (m_ToTalTime2 <= 0)
			{
				m_ToTalTime2 = 0;
			}

			if (score >= 10000 && DrawFlag == true)
			{
				AddGameObject<GoalTrophy>(Vec3(0.0f, 10.0f, 0.0f), Vec3(2.0f, 2.0f, 1.0f), Vec3(0.0f));
				DrawFlag = false;
			}

			if (m_ToTalTime <= 0 && m_TimeFlag == true && m_Flag == true) {
				if (score <= 9999 || score >= 9999)
				{
					ptrMana->Stop(m_BGM);
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
				}

			}
		}

		if (GoalFlag == true)
		{
			ptrMana->Stop(m_BGM);
			ptrPlayer->m_StopFlag = true;
		}



		//スコアを更新する
		auto ptrScor = GetSharedGameObject<UITime>(L"UITime");
		ptrScor->SetScore(m_ToTalTime);
		auto ptrScor2 = GetSharedGameObject<UITime2>(L"UITime2");
		ptrScor2->SetScore(m_ToTalTime2);
		if (m_isStartFlag == false)
		{
			auto ptrScor2 = GetSharedGameObject<UITimeStage>(L"UITimeStage");
			ptrScor2->SetScore2(m_ToStartTime);
		}
		if (m_isStartFlag == true)
		{
			auto ptrScoreDraw = GetSharedGameObject<UITimeStage>(L"UITimeStage");
			ptrScoreDraw->m_isDrawFlag = true;
		}

		//CirCleや他の場所に移動
		auto circle = GetSharedGameObject<FloatCircle>(L"FloatCircle");
		auto ciclenext = circle->m_next;
		auto circleCount = circle->m_ComboCount;
		auto cicleTrans = circle->GetComponent<Transform>();

		switch (ciclenext)
		{
		case 1:
			cicleTrans->SetPosition(0.0f, 6.0f, 0.0f);
			break;
		case 2:
			cicleTrans->SetPosition(15.0f, 6.0f, 25.0f);
			cicleTrans->SetRotation(80.1f, 80.5f, 0.0f);
			break;
		case 3:
			cicleTrans->SetPosition(30.0f, 10.0f, 25.0);
			cicleTrans->SetRotation(80.1f, 80.1f, 0.0f);
			break;
		case 4:
			cicleTrans->SetPosition(40.0f, 6.0f, 25.0f);
			cicleTrans->SetRotation(80.1f, 80.6f, 0.0f);
			break;
		case 5:
			cicleTrans->SetPosition(40.0f, 6.0f, -25.0f);
			break;
		case 6:
			cicleTrans->SetPosition(30.0f, 10.0f, -25.0f);
			cicleTrans->SetRotation(80.1f, 80.1f, 0.0f);
			break;
		case 7:
			cicleTrans->SetPosition(15.0f, 6.0f, -25.0f);
			cicleTrans->SetRotation(80.1f, 80.0f, 0.0f);
			break;
		case 8:
			cicleTrans->SetPosition(0.0f, 6.0f, 0.0f);
			cicleTrans->SetRotation(80.1f, 0.0f, 0.0f);
			break;
		case 9:
			cicleTrans->SetPosition(-15.0f, 4.0f, 25.0f);
			cicleTrans->SetRotation(80.1f, 80.1f, 0.0f);
			break;
		case 10:
			cicleTrans->SetPosition(-15.0f, 6.0f, 25.0f);
			cicleTrans->SetRotation(80.1f, 79.9f, 0.0f);
			break;
		case 11:
			cicleTrans->SetPosition(-30.0f, 10.0f, 25.0);
			cicleTrans->SetRotation(80.1f, 80.1f, 0.0f);
			break;
		case 12:
			cicleTrans->SetPosition(-40.0f, 6.0f, 25.0f);
			cicleTrans->SetRotation(80.1f, -80.0f, 0.0f);
			break;
		case 13:
			cicleTrans->SetPosition(-40.0f, 6.0f, -25.0f);
			cicleTrans->SetRotation(80.1f, -79.5f, 0.0f);
			break;
		case 14:
			cicleTrans->SetPosition(-30.0f, 10.0f, -25.0);
			cicleTrans->SetRotation(80.1f, 80.1f, 0.0f);
			break;
		case 15:
			cicleTrans->SetPosition(-15.0f, 6.0f, -25.0f);
			cicleTrans->SetRotation(80.1f, 85.9f, 0.0f);
			circle->m_next = 1;
			break;
		}
	}
}
//end basecross
