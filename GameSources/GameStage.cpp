/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	// コンストラクタ
	GameStage::GameStage() :
		m_StageRation(10.0f), // ステージのサイズ倍率
		m_ToTalTime(90)
	{}

	void GameStage::CreateViewLight() {
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
	void GameStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>(Vec3(-2.5f,0.4f,-45.0f),Vec3(0.25f,0.25f,0.25f),Vec3(0.0f,0.0f,0.0f));
		SetSharedGameObject(L"Player", ptrPlayer);
    }
	void GameStage::CreateWall()
	{
		auto WallCol = AddGameObject<Wall>(Vec3(0.0f, 10.0f, 50.0f), Vec3(95.0f, 20.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));//上

	    WallCol = AddGameObject<Wall>(Vec3(0.0f, 10.0f, -49.0f), Vec3(95.0f, 20.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
		WallCol = AddGameObject<Wall>(Vec3(47.0f, 10.0f, -46.5f), Vec3(1.0f, 20.0f, 4.0f), Vec3(0.0f, 0.0f, 0.0f));//左上の部分
		WallCol = AddGameObject<Wall>(Vec3(48.0f, 10.0f, -42.0f), Vec3(1.0f, 20.0f, 5.2f), Vec3(0.0f, 0.0f, 0.0f));//左上の部分
		WallCol = AddGameObject<Wall>(Vec3(48.0f, 10.0f, -42.0f), Vec3(1.0f, 20.0f, 5.2f), Vec3(0.0f, 0.0f, 0.0f));//左上の部分
		WallCol = AddGameObject<Wall>(Vec3(49.0f, 10.0f, 0.0f), Vec3(1.0f, 20.0f, 81.0f), Vec3(0.0f, 0.0f, 0.0f));//左の部分
		WallCol = AddGameObject<Wall>(Vec3(47.0f, 10.0f, 47.5f), Vec3(1.0f, 20.0f, 4.0f), Vec3(0.0f, 0.0f, 0.0f));//左下の部分
		WallCol = AddGameObject<Wall>(Vec3(48.0f, 10.0f, 43.0f), Vec3(1.0f, 20.0f, 5.2f), Vec3(0.0f, 0.0f, 0.0f));//左下の部分

		WallCol = AddGameObject<Wall>(Vec3(-48.0f, 10.0f,  47.5f),  Vec3(1.0f, 20.0f, 4.0f), Vec3(0.0f, 0.0f, 0.0f));//左上の部分
		WallCol = AddGameObject<Wall>(Vec3(-49.0f, 10.0f,  43.0f),  Vec3(1.0f, 20.0f, 5.2f), Vec3(0.0f, 0.0f, 0.0f));//左上の部分
		WallCol = AddGameObject<Wall>(Vec3(-50.0f, 10.0f,  0.5f),  Vec3(1.0f, 20.0f, 80.0f), Vec3(0.0f, 0.0f, 0.0f));//左の部分
		WallCol = AddGameObject<Wall>(Vec3(-48.0f, 10.0f, -46.5f), Vec3(1.0f, 20.0f, 4.0f), Vec3(0.0f, 0.0f, 0.0f));//左下の部分
		WallCol = AddGameObject<Wall>(Vec3(-49.0f, 10.0f, -42.0f), Vec3(1.0f, 20.0f, 5.2f), Vec3(0.0f, 0.0f, 0.0f));//左下の部分
	}

	void GameStage::CreatePollCollision()
	{
		//pollCollision
		auto pollCol = AddGameObject<PollCollision>(Vec3(3.0f,3.75,0.0f), Vec3(1.5f, 7.25f, 2.0f),Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-3.0f, 3.75, 0.0f), Vec3(1.5f, 7.25f, 2.0f),Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(0.0f, 4.8f, 0.0f), Vec3(5.0f, 0.4f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(0.0f, 7.2f, 0.0f), Vec3(5.0f, 0.4f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
		//CirecleCollision
		auto CirclepollColrig = AddGameObject<PollCollision>(Vec3(30.0f, 12.75f, 0.0f), Vec3(4.0f,2.0f,0.3f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(30.0f, 7.35f, 0.0f), Vec3(4.0f, 2.0f, 0.3f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(27.15f, 10.0f, 0.0f), Vec3(1.7f, 6.0f, 0.3f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(32.9f, 10.0f, 0.0f), Vec3(1.7f, 6.0f, 0.3f), Vec3(0.0f, 0.0f, 0.0f));
		//CirecleCollision左側
		auto CirclepollCollef = AddGameObject<PollCollision>(Vec3(-30.0f, 12.75f, 0.0f), Vec3(4.0f, 2.0f, 0.3f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-30.0f, 7.35f, 0.0f), Vec3(4.0f, 2.0f, 0.3f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-27.15f, 10.0f, 0.0f), Vec3(1.7f, 6.0f, 0.3f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-32.9f, 10.0f, 0.0f), Vec3(1.7f, 6.0f, 0.3f), Vec3(0.0f, 0.0f, 0.0f));

		auto pollCollef = AddGameObject<PollCollision>(Vec3(18.0f, 4.0f, -25.0f), Vec3(3.0f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(12.0f, 4.0f, -25.0f), Vec3(3.0f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-18.0f, 4.0f, -25.0f), Vec3(3.0f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-12.0f, 4.0f, -25.0f), Vec3(3.0f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(18.0f, 4.0f, 25.0f), Vec3(3.0f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(12.0f, 4.0f, 25.0f), Vec3(3.0f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-18.0f, 4.0f, 25.0f), Vec3(3.0f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-12.0f, 4.0f, 25.0f), Vec3(3.0f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));

	}

	void GameStage::CreateGround() {		
		AddGameObject<Ground>(Vec3(0.0f, -1.0f, 0.0f), Vec3(300.0f, 0.5f, 300.0f), L"SEA_TX");

	}
	void GameStage::CreateObstacle() {
		auto objPoll = AddGameObject<Poll>(Vec3(0.0f, 6.0f, 0.0f), Vec3(5.0f, 2.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll", objPoll);
		auto objCirclePoll = AddGameObject<CirclePoll>(Vec3(30.0f, 10.0f, 0.0f), Vec3(4.0f,3.5f,0.3f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		objCirclePoll = AddGameObject<CirclePoll>(Vec3(-30.0f, 10.0f, 0.0f), Vec3(4.0f, 3.5f, 0.3f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		//SetSharedGameObject(L"CirclePoll", objCirclePoll);
		auto objPollnol = AddGameObject<Poll1>(Vec3(15.0f, 4.0f, -25.0f), Vec3(3.0f, 8.0f,2.0f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		objPollnol = AddGameObject<Poll1>(Vec3(-15.0f, 4.0f, -25.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		objPollnol = AddGameObject<Poll1>(Vec3(15.0f, 4.0f, 25.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		objPollnol = AddGameObject<Poll1>(Vec3(-15.0f, 4.0f, 25.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		//SetSharedGameObject(L"Poll1", objPollnol);


		auto ptrobstacle = AddGameObject<Deployment>();
	}
	void GameStage::CreateTraceSprite() {
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
	void GameStage::CreateGoal(){
		//AddGameObject<Goal>(
		//	Vec3(0.0f, 25.0f, -240.0f),//pos z=-240
		//	Vec3(100.0f, 50.0f, 1.0f),//scl
		//	Vec3(0.0f,0.0f,0.0f));//rot
	}
	void GameStage::CreateTime()
	{
		AddGameObject<UITime>(2,
			L"NUMBER2_TX",
			true,
			Vec2(240.0f, 60.0f),
			Vec3(-440.0f, 350.0f, 0.0f));
	}

	void GameStage::OnCreate() {
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
			CreatePollCollision();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate()
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
