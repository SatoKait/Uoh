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
		m_ToTalTime(90)
	{}

	void GameStage2::CreateViewLight() {
		// カメラの設定MainCamera
		auto camera = ObjectFactory::Create<MainCamera>(0.0f);
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
		auto ptrPlayer = AddGameObject<Player>(Vec3(-2.0f, 0.4f, 0.0f), Vec3(0.25f, 0.25f, 0.25f), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"Player", ptrPlayer);
	}
	void GameStage2::CreateWall()
	{
		auto ptrWall = AddGameObject<Wall>(Vec3(0.0f, 10.0f, 50.0f), Vec3(95.0f, 20.0f, 1.0f));//上

		ptrWall = AddGameObject<Wall>(Vec3(0.0f, 10.0f, -49.0f), Vec3(95.0f, 20.0f, 1.0f));
		ptrWall = AddGameObject<Wall>(Vec3(47.0f, 10.0f, -46.5f), Vec3(1.0f, 20.0f, 4.0f));//左上の部分
		ptrWall = AddGameObject<Wall>(Vec3(48.0f, 10.0f, -42.0f), Vec3(1.0f, 20.0f, 5.2f));//左上の部分
		ptrWall = AddGameObject<Wall>(Vec3(48.0f, 10.0f, -42.0f), Vec3(1.0f, 20.0f, 5.2f));//左上の部分
		ptrWall = AddGameObject<Wall>(Vec3(49.0f, 10.0f, 0.0f), Vec3(1.0f, 20.0f, 81.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3(47.0f, 10.0f, 47.5f), Vec3(1.0f, 20.0f, 4.0f));//左下の部分
		ptrWall = AddGameObject<Wall>(Vec3(48.0f, 10.0f, 43.0f), Vec3(1.0f, 20.0f, 5.2f));//左下の部分

		ptrWall = AddGameObject<Wall>(Vec3(-47.0f, 10.0f, 46.5f), Vec3(1.0f, 20.0f, 4.0f));//左上の部分
		ptrWall = AddGameObject<Wall>(Vec3(-48.0f, 10.0f, 42.0f), Vec3(1.0f, 20.0f, 5.2f));//左上の部分
		ptrWall = AddGameObject<Wall>(Vec3(-48.0f, 10.0f, 42.0f), Vec3(1.0f, 20.0f, 5.2f));//左上の部分
		ptrWall = AddGameObject<Wall>(Vec3(-49.0f, 10.0f, 0.0f), Vec3(1.0f, 20.0f, 81.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3(-47.0f, 10.0f, -47.5f), Vec3(1.0f, 20.0f, 4.0f));//左下の部分
		ptrWall = AddGameObject<Wall>(Vec3(-48.0f, 10.0f, -43.0f), Vec3(1.0f, 20.0f, 5.2f));//左下の部分



	}
	void GameStage2::CreateGround() {
		AddGameObject<Ground>(Vec3(0.0f, -1.0f, 0.0f), Vec3(300.0f, 0.5f, 300.0f), L"SEA_TX");
	}
		
	void GameStage2::CreateObstacle() {
		auto objPoll = AddGameObject<Poll>(Vec3(0.0f, 6.0f, 0.0f), Vec3(5.0f, 2.5f, 1.0f), L"RED_TX");
		SetSharedGameObject(L"Poll", objPoll);
		auto ptrobstacle = AddGameObject<Deployment2>();
	}

	void GameStage2::CreateTraceSprite() {
		float a = -510.0f;
		float b = 70.0f;
		//AddGameObject<Time>(1,Vec3(1.0f,1.0f,1.0f),L"NUMBER_TX");
		//AddGameObject<Energy>(L"HANE_TX", true,
		//    Vec2(100.0f, 60.0f), Vec3(a,350.0f, 0.0f));
		//AddGameObject<Energy>(L"HANE_TX", true,
		//	Vec2(100.0f, 60.0f), Vec3(a - b, 350.0f, 0.0f));
		//AddGameObject<Energy>(L"HANE_TX", true,
		//	Vec2(100.0f, 60.0f), Vec3(a + b, 350.0f, 0.0f));

	}
	void GameStage2::CreateGoal() {
		//AddGameObject<Goal>(
		//	Vec3(0.0f, 25.0f, -240.0f),//pos z=-240
		//	Vec3(100.0f, 50.0f, 1.0f),//scl
		//	Vec3(0.0f,0.0f,0.0f));//rot
	}
	void GameStage2::CreateTime()
	{
		AddGameObject<UITime>(2,
			L"NUMBER2_TX",
			true,
			Vec2(240.0f, 60.0f),
			Vec3(-440.0f, 350.0f, 0.0f));
	}

	void GameStage2::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreatePlayer();
			CreateWall();
			CreateGround();
			CreateObstacle();
			CreateGoal();
			CreateTraceSprite();
			CreateTime();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage2::OnUpdate()
	{
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y)
		{
			int a = 0;
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGoalScene");
		}

		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_ToTalTime;
		m_ToTalTime -= elapsedTime;
		if (m_ToTalTime <= 0) {
			//m_ToTalTime = 0.0f;
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGoalScene");

		}
		//スコアを更新する
		auto ptrScor = GetSharedGameObject<UITime>(L"UITime");
		ptrScor->SetScore(m_ToTalTime);
	}

}
//end basecross
