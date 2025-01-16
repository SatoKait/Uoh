/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include <Windows.h>
#include <d3d11.h>

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	// コンストラクタ
	GameStage::GameStage() :
		m_StageRation(10.0f), // ステージのサイズ倍率
		m_ToTalTime(30),
		m_ToStartTime(4),
		m_ToTalTime2(1),
		m_isStartFlag(false),
		m_TimeFlag(false),
		m_Flag(false),
		DrawFlag(true),
		m_GoalFlag(false),
<<<<<<< HEAD
=======
		m_EndFlag(false),
>>>>>>> Tomoki
		m_30secFlag(true),
		m_TimeUpFlag(false),
		count(0),
		m_SetCount(0),
		m_TimeUpAfter(0.0f),
		m_Set2Count(0)
	{}

	void GameStage::CreateViewLight() {
		////OpeningCameraView用のビュー
		//m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		//auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		//m_OpeningCameraView->SetCamera(ptrOpeningCamera);
		////MyCamera用のビュー
		//m_MyCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		//auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		//ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		//ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//m_MyCameraView->SetCamera(ptrMyCamera);
		//////ObjCamera用のビュー
		////m_ObjCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		////auto ptrObjCamera = ObjectFactory::Create<ObjCamera>();
		////m_ObjCameraView->SetCamera(ptrObjCamera);
		////初期状態ではm_OpeningCameraViewを使う
		//SetView(m_OpeningCameraView);
		//m_CameraSelect = CameraSelect::openingCamera;
		////マルチライトの作成
		//auto PtrMultiLight = CreateLight<MultiLight>();
		////デフォルトのライティングを指定
		//PtrMultiLight->SetDefaultLighting();

		// カメラの位置と注視点位置
		const Vec3 eye(0.0f, 2.5f, -3.5f);
		const Vec3 at(0.0f);

		// カメラの設定MainCamera
		m_View = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto camera = ObjectFactory::Create<MainCamera>(-90.0f);
		camera->SetEye(eye);
		camera->SetAt(at);
		camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// ビューにカメラを設定
		m_View = CreateView<SingleView>();
		m_View->SetCamera(camera);

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();

	}
	void GameStage::CameraSetting(const shared_ptr<GameObject>& ptrObj)
	{
		//// カメラの設定
		//auto ptrCamera = GetView()->GetTargetCamera();
		//auto ptrMainCamera = dynamic_pointer_cast<MainCamera>(ptrCamera);
		//ptrMainCamera->SetTarget(ptrObj);

		////カメラのオブジェクトの設定
		//auto ptrCameraObject = AddGameObject<MoveCamera>();
		//ptrCameraObject->SetOwner(ptrMainCamera);
		//ptrCameraObject->GetComponent<Transform>()->SetPosition(ptrMainCamera->GetEye());
		//ptrCameraObject->GetComponent<CollisionSphere>()->AddExcludeCollisionGameObject(ptrObj);
	}

	void GameStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>(Vec3(-2.5f, -15.0f, -45.0f), Vec3(2.0f, 0.25f, 0.25f), Vec3(0.0f, 0.0f, 0.0f));
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

		WallCol = AddGameObject<Wall>(Vec3(-48.0f, 10.0f, 47.5f), Vec3(1.0f, 20.0f, 4.0f), Vec3(0.0f, 0.0f, 0.0f));//左上の部分
		WallCol = AddGameObject<Wall>(Vec3(-49.0f, 10.0f, 43.0f), Vec3(1.0f, 20.0f, 5.2f), Vec3(0.0f, 0.0f, 0.0f));//左上の部分
		WallCol = AddGameObject<Wall>(Vec3(-50.0f, 10.0f, 0.5f), Vec3(1.0f, 20.0f, 80.0f), Vec3(0.0f, 0.0f, 0.0f));//左の部分
		WallCol = AddGameObject<Wall>(Vec3(-48.0f, 10.0f, -46.5f), Vec3(1.0f, 20.0f, 4.0f), Vec3(0.0f, 0.0f, 0.0f));//左下の部分
		WallCol = AddGameObject<Wall>(Vec3(-49.0f, 10.0f, -42.0f), Vec3(1.0f, 20.0f, 5.2f), Vec3(0.0f, 0.0f, 0.0f));//左下の部分
	}
	void GameStage::CreatePollCollision()
	{
		//pollCollision
		auto pollCol = AddGameObject<PollCollision>(Vec3(3.0f, 4.2f, 0.0f), Vec3(1.5f, 7.25f, 2.0f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-3.0f, 4.2f, 0.0f), Vec3(1.5f, 7.25f, 2.0f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(0.0f, 4.35f, 0.0f), Vec3(5.0f, 0.4f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(0.0f, 7.75f, 0.0f), Vec3(5.0f, 0.4f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
		//CirecleCollision
		auto CirclepollColrig = AddGameObject<PollCollision>(Vec3(30.0f, 12.75f, 0.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(30.0f, 7.35f, 0.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(27.15f, 10.0f, 0.0f), Vec3(1.7f, 6.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(32.9f, 10.0f, 0.0f), Vec3(1.7f, 6.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		//CirecleCollision左側
		auto CirclepollCollef = AddGameObject<PollCollision>(Vec3(-30.0f, 12.75f, 0.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-30.0f, 7.35f, 0.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-27.15f, 10.0f, 0.0f), Vec3(1.7f, 6.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-32.9f, 10.0f, 0.0f), Vec3(1.7f, 6.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));

		auto pollCollef = AddGameObject<PollCollision>(Vec3(18.0f, 4.0f, -35.0f), Vec3(2.25f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(12.0f, 4.0f, -35.0f), Vec3(2.25f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-18.0f, 4.0f, -35.0f), Vec3(2.25f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-12.0f, 4.0f, -35.0f), Vec3(2.25f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-27.3f, 4.0f, -20.0f), Vec3(2.25, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(27.3f, 4.0f, -20.0f), Vec3(2.25, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(32.8f, 4.0f, -20.0f), Vec3(2.25, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-32.8f, 4.0f, -20.0f), Vec3(2.25, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));

		pollCollef = AddGameObject<PollCollision>(Vec3(18.0f, 4.0f, 35.0f), Vec3(2.25f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(12.0f, 4.0f, 35.0f), Vec3(2.25f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-18.0f, 4.0f, 35.0f), Vec3(2.25f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-12.0f, 4.0f, 35.0f), Vec3(2.25f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-27.3f, 4.0f, 20.0f), Vec3(2.25f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(27.3f, 4.0f, 20.0f), Vec3(2.25f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(32.8f, 4.0f, 20.0f), Vec3(2.25f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCollef = AddGameObject<PollCollision>(Vec3(-32.8f, 4.0f, 20.0f), Vec3(2.25f, 8.0f, 2.2f), Vec3(0.0f, 0.0f, 0.0f));
	}
	void GameStage::CreateGround() {
		AddGameObject<Ground>(Vec3(0.0f, -1.0f, 0.0f), Vec3(500.0f, 0.5f, 500.0f), L"SEA_TX");

	}
	void GameStage::CreateObstacle() {
		auto objPoll = AddGameObject<Poll>(Vec3(0.0f, 5.55f, 0.0f), Vec3(5.0f, 1.75f, 0.5f), Vec3(0.0f, 0.0f, 0.0f), L"GREEN_TX");
		SetSharedGameObject(L"Poll", objPoll);
		auto objCirclePoll = AddGameObject<CirclePoll>(Vec3(30.0f, 10.0f, 0.0f), Vec3(4.0f, 3.5f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"CirclePoll1", objCirclePoll);
		objCirclePoll = AddGameObject<CirclePoll>(Vec3(-30.0f, 10.0f, 0.0f), Vec3(4.0f, 3.5f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), L"BLUE_TX");
		SetSharedGameObject(L"CirclePoll2", objCirclePoll);
		auto objPollnol = AddGameObject<Poll1>(Vec3(15.0f, 4.0f, -35.0f), Vec3(3.0f, 8.0f,2.0f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll1_1", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(-15.0f, 4.0f, -35.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), L"BLUE_TX");
		SetSharedGameObject(L"Poll1_2", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(15.0f, 4.0f, 35.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll1_3", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(-15.0f, 4.0f, 35.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), L"BLUE_TX");
		SetSharedGameObject(L"Poll1_4", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(30.0f, 4.0f, 20.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll1_5", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(30.0f, 4.0f, -20.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Poll1_6", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(-30.0f, 4.0f, 20.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), L"BLUE_TX");
		SetSharedGameObject(L"Poll1_7", objPollnol);
		objPollnol = AddGameObject<Poll1>(Vec3(-30.0f, 4.0f, -20.0f), Vec3(3.0f, 8.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), L"BLUE_TX");
		SetSharedGameObject(L"Poll1_8", objPollnol);
		//AddGameObject<UpdownPoll>(Vec3(0.0f, 5.55f, -10.0f), Vec3(5.0f, 1.75f, 0.5f), Vec3(0.0f, 0.0f, 0.0f));
		//AddGameObject<OnewaytrafficPoll>(Vec3(0.0f, 5.55f, -10.0f), Vec3(5.0f, 1.75f, 0.5f), Vec3(0.0f, 0.0f, 0.0f));
		//AddGameObject<OneWayPollCollision>(Vec3(0.0f, 5.55f, -11.0f), Vec3(5.0f, 2.0f, 0.5f), Vec3(0.0f, 0.0f, 0.0f));

		auto ptrobstacle = AddGameObject<Deployment>();
	}
	void GameStage::CreateComboSprite() {
		float x = 550.0f, y = 320.0f;

		AddGameObject<ComboSprite>(
			L"COMBO_TX", 
			true,
			Vec2(120.0f, 80.0f),
			Vec3(x, y - 30.0f, 0.0f)
		);

		AddGameObject<ComboSpriteNumber>(
			L"NUMBER_TX",
			true,
			Vec2(1.0f, 1.0f),
			Vec3(x - 130.0f, y + 44.0f , 0.0f)
);

	}
	void GameStage::CreateGoal() {
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
			Vec2(220.0f, 60.0f),
			Vec3(670.0f, 350.0f, 0.0f));
		AddGameObject<UITime2>(2,
			L"NUMBER2_TX",
			true,
			Vec2(220.0f, 60.0f),
			Vec3(530.0f, 350.0f, 0.0f));
		AddGameObject<StageSprite>(L"TIME_TX", true,
			Vec2(350.0f, 80.0f), Vec2(495.0f, 355.0f));
		//AddGameObject<StageSprite>(L"PARTITION_TX", true,
		//Vec2(500.0f, 100.0f), Vec2(-15.0f, 350.0f));
		//auto score = AddGameObject<Score>();
		//AddGameObject<StageScore>();
		//SetSharedGameObject(L"Score", ptrscore);
		
		// HPゲージの生成
		auto ptrHpGauge = AddGameObject<GaugeScore>(false,
			Vec2(360.0f, 2.0f), Vec3(-540.0f, -360.0f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"Gauge", ptrHpGauge);
		AddGameObject<GaugeSpriteNumber>(L"NUMBER_TX",
			true,
			Vec2(1.0f, 1.0f), Vec3(-445.0f, -290.0f, 0.0f));
		// HPゲージの生成
		auto ptrHpGauge2 = AddGameObject<GaugeScoreEnemy>(false,
			Vec2(360.0f, 2.0f), Vec3(-615.0f, -360.0f, 0.0f), L"RED_TX");
		SetSharedGameObject(L"GaugeEnemy", ptrHpGauge2);
		// 説明のアイコンを生成
		AddGameObject<StageSprite>(L"ICON_TX", true,
			Vec2(200.0f, 100.0f), Vec2(520.0f, -340.0f));
		AddGameObject<StageSprite>(L"YOU_TX", true,
			Vec2(90.0f, 50.0f), Vec2(-515.0f, -378.0f));
	}
	void GameStage::CreateStageTime()
	{
		AddGameObject<UITimeStage>(1,
			L"NUMBER2_TX",
			true,
			Vec2(480.0f, 200.0f),
			Vec3(250.0f, 0.0f, 0.0f));
	}

	void GameStage::CreateBGM() {
		auto ptrMana = App::GetApp()->GetXAudio2Manager();
		m_BGM = ptrMana->Start(L"StageBGM1", XAUDIO2_LOOP_INFINITE, 0.3f);
		//m_ptrXA->Start(L"StageBGM2", XAUDIO2_LOOP_INFINITE, 0.5f);
	}

	void GameStage::CreateFloatCircle()
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
	void GameStage::CreateWave()
	{
		//auto ptrgate = AddGameObject<Gate>(1, rand() % 4, Vec3(5.0f, 1.75f, 0.5f), L"GREEN_TX");

	}

	//カメラマンの作成
	void GameStage::CreateCameraman() {

	}

	void GameStage::CreateMoveCamera()
	{
		//auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		////MyCameraに変更
		//auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_MyCameraView->GetCamera());
		//if (ptrMyCamera) {
		//	ptrMyCamera->SetTargetObject(ptrPlayer);
		//	//m_MyCameraViewを使う
		//	SetView(m_MyCameraView);
		//	m_CameraSelect = CameraSelect::myCamera;
		//}

	}

	void GameStage::CreateNPC()
	{
		auto ptr = AddGameObject<NPC>(Vec3(0.3f), Vec3(0.0f, XM_PIDIV2,0.0f), Vec3(0.0f, 0.0f, -45.0f));

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
			CreateComboSprite();
			CreateTime();
			CreateStageTime();
			CreatePollCollision();
			CreateBGM();
			CreateFloatCircle();
			CreateWave();
			CreateMoveCamera();
			CreateNPC();
			//CreateMoveCamera();
			//CameraSetting(ptrPlayer);
			auto& app = App::GetApp();
			auto path = app->GetDataDirWString();

			auto miniMapManager = AddGameObject<MiniMapManager>(100);//ミニマップ生成デバック用
			SetSharedGameObject(L"MiniMapManager", miniMapManager);
			miniMapManager->CreateMoveGate();
			miniMapManager->CreatePlayer();

			auto skyboxPath = path + L"skybox/";
			for (const auto& keyName : Skybox2::pairs) {
				app->RegisterTexture(keyName.first, skyboxPath + keyName.first + L".bmp");
			}

			AddGameObject<StageSprite>(L"BAR_TX", true,
				Vec2(256.0f, 256.0f), Vec2(-515.0f, -260.0f));
			AddGameObject<StageSprite>(L"BAR_TX", true,
				Vec2(256.0f, 256.0f), Vec2(-590.0f, -260.0f));

			// Skyboxクラス用
			app->RegisterTexture(L"skybox", skyboxPath + L"skybox1.png"); // テクスチャを１枚にまとめたバージョン
			// スカイボックス
			AddGameObject<Skybox>(); // テクスチャを１枚にまとめたバージョン
			//AddGameObject<Skybox2>();

			CreateMoveCamera();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate()
	{
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto ptrMana = App::GetApp()->GetXAudio2Manager();
		auto delta = App::GetApp()->GetElapsedTime();

		auto score1 = App::GetApp()->GetScene<Scene>()->GetScore();
		auto score2 = App::GetApp()->GetScene<Scene>()->GetScore2();
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto GoalFlag = ptrPlayer->m_GoalFlag;
		auto m_count = ptrPlayer->m_CircleCount;
		auto gauge = GetSharedGameObject<GaugeScore>(L"Gauge");
		auto gaugecount = gauge->Count;

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y)
		{
			int a = 0;
			ptrMana->Stop(m_BGM);
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

			if (gaugecount == 2 && !gaugeFlag)
			{
				//ptrMana->Stop(m_BGM);
				//AddGameObject<GoalTrophy>(Vec3(0.0f, 10.0f, 0.0f), Vec3(2.0f, 2.0f, 1.0f), Vec3(0.0f));
				gaugeFlag = true;
				DrawFlag = false;
			}

			if (m_ToTalTime <= 0 && m_TimeFlag == true && m_Flag == true) {
				ptrMana->Stop(m_BGM);
				if (m_TimeUpFlag == false)
				{
					ptrMana->Start(L"TIMEUPSE", 0, 0.5f);
					m_TimeUpFlag = true;
				}
				m_TimeUpAfter += delta;
				ptrPlayer->m_MoveFlag = false;
				if (m_TimeUpAfter >= 3.0f)
				{
					if (score1 > score2)
					{
						PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGoalScene");
					}
					if (score1 < score2)
					{
						PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
					}
				}
			}

		}
		if (GoalFlag == true)
		{
			ptrMana->Stop(m_BGM);
			ptrPlayer->m_StopFlag = true;
		}
		if (m_TimeFlag == true && m_ToTalTime <= 31 && m_30secFlag)
		{
			ptrMana->Stop(m_BGM);
			ptrMana->Start(L"ALARMSE", 0, 0.6f);
			m_BGM = ptrMana->Start(L"StageBGM2", 1, 0.3f);
			m_30secFlag = false;
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
			cicleTrans->SetPosition(-15.0f, 6.0f, -35.0f);
			break;
		case 2:

			cicleTrans->SetPosition(-30.0f, 6.0f, -20.0f);
			break;
		case 3:
			cicleTrans->SetPosition(-29.95f, 10.2f, -0.5f);
			break;
		case 4:
			cicleTrans->SetPosition(-30.0f, 6.0f, 20.0f);
			break;
		case 5:
			cicleTrans->SetPosition(-15.0f, 6.0f, 35.0f);
			break;
		case 6:
			if (count == 0)
			{
				auto ptrgate = AddGameObject<Gate>(1, rand() % 4, Vec3(5.0f, 1.75f, 0.5f), L"GREEN_TX");
				if (m_SetCount == 0)
				{
					SetSharedGameObject(L"Gate", ptrgate);
					m_SetCount++;
				}
				else if (m_SetCount == 1)
				{
					SetSharedGameObject(L"Gate1", ptrgate);
					m_SetCount++;
				}

			
				auto ptrRandFlag = ptrgate->m_RandFlag = false;
			    //auto ptrEndFlag =  ptrgate->= false;
				auto ptrFlag = ptrgate->flag;
				count++;
				if (ptrFlag == 0)
				{
					cicleTrans->SetPosition(0.0f, 6.0f, 20.0f);
				}
				if (ptrFlag == 1)
				{
					cicleTrans->SetPosition(20.0f, 6.0f, 0.0f);
				}
				if (ptrFlag == 2)
				{
					cicleTrans->SetPosition(0.0f, 6.0f, -20.0f);
				}
				if (ptrFlag == 3)
				{
					cicleTrans->SetPosition(-20.0f, 6.0f, 0.0f);
				}
			}


			break;
		case 7: 
			if (count == 1)
			{
				if (m_SetCount == 1)
				{
					auto ptrgate2 = GetSharedGameObject<Gate>(L"Gate");
					auto ptrFlag = ptrgate2->flag = 0;
					auto ptrRandFlag = ptrgate2->m_RandFlag = false;
					auto ptrDownFlag = ptrgate2->m_DownFlag = true;
					auto ptrChangeFlag = ptrgate2->m_ChangeFlag = false;
					auto ptrChangeFlag1 = ptrgate2->m_ChangeFlag1 = false;
					auto ptrChangeFlag2 = ptrgate2->m_ChangeFlag2 = false;
					auto ptrChangeFlag3 = ptrgate2->m_ChangeFlag3 = false;
				}
				else if (m_SetCount == 2)
				{
					auto ptrgate3 = GetSharedGameObject<Gate>(L"Gate1");
					auto ptrFlag = ptrgate3->flag = 0;
					auto ptrRandFlag = ptrgate3->m_RandFlag = false;
					auto ptrDownFlag = ptrgate3->m_DownFlag = true;
					auto ptrChangeFlag = ptrgate3->m_ChangeFlag = false;
					auto ptrChangeFlag1 = ptrgate3->m_ChangeFlag1 = false;
					auto ptrChangeFlag2 = ptrgate3->m_ChangeFlag2 = false;
					auto ptrChangeFlag3 = ptrgate3->m_ChangeFlag3 = false;

				}
			}

			cicleTrans->SetPosition(15.0f, 6.0f, -35.0f);
			break;
		case 8:
			if (count == 1)
			{	
				if (m_SetCount == 1)
				{
					auto ptrgate3 = GetSharedGameObject<Gate>(L"Gate");
					RemoveGameObject<Gate>(ptrgate3);
					count--;
				}
				else if (m_SetCount == 2)
				{
					auto ptrgate3 = GetSharedGameObject<Gate>(L"Gate1");
					RemoveGameObject<Gate>(ptrgate3);
					count--;
				}

			}

			cicleTrans->SetPosition(30.0f, 6.0f, -20.0f);
			break;
		case 9:
			cicleTrans->SetPosition(29.95f, 10.2f, 0.5f);
			break;
		case 10:
			cicleTrans->SetPosition(30.0f, 6.0f, 20.0f);
			break;
		case 11:
			cicleTrans->SetPosition(15.0f, 6.0f, 35.0f);
			break;
		case 12:
			if (count == 0)
			{
				auto ptrgate4 = AddGameObject<Gate>(1, rand() % 4, Vec3(5.0f, 1.75f, 0.5f),L"GREEN_TX");
				if (m_Set2Count == 0)
				{
				   SetSharedGameObject(L"Gate2", ptrgate4);
				   m_Set2Count++;
				}
				else if (m_Set2Count == 1)
				{
					SetSharedGameObject(L"Gate3", ptrgate4);
					m_Set2Count++;
				}

				auto ptrRandFlag2 = ptrgate4->m_RandFlag = false;
				auto ptrFlag2 = ptrgate4->flag;
				count++;
				if (ptrFlag2 == 0)
				{
					cicleTrans->SetPosition(0.0f, 6.0f, 20.0f);
				}
				if (ptrFlag2 == 1)
				{
					cicleTrans->SetPosition(20.0f, 6.0f, 0.0f);
				}
				if (ptrFlag2 == 2)
				{
					cicleTrans->SetPosition(0.0f, 6.0f, -20.0f);
				}
				if (ptrFlag2 == 3)
				{
					cicleTrans->SetPosition(-20.0f, 6.0f, 0.0f);
					//ptrFlag--;
				}
			}
			break;
		case 13:
			cicleTrans->SetPosition(-15.0f, 6.0f, -35.0f);
			if (count == 1)
			{

				if (m_Set2Count == 1)
				{
					auto ptrgate5 = GetSharedGameObject<Gate>(L"Gate2");
					auto ptrFlag = ptrgate5->flag = 0;
					auto ptrRandFlag = ptrgate5->m_RandFlag = false;
					auto ptrDownFlag = ptrgate5->m_DownFlag = true;
					auto ptrChangeFlag = ptrgate5->m_ChangeFlag = false;
					auto ptrChangeFlag1 = ptrgate5->m_ChangeFlag1 = false;
					auto ptrChangeFlag2 = ptrgate5->m_ChangeFlag2 = false;
					auto ptrChangeFlag3 = ptrgate5->m_ChangeFlag3 = false;
				}
				else if (m_Set2Count == 1)
				{
					auto ptrgate6 = GetSharedGameObject<Gate>(L"Gate3");
					auto ptrFlag = ptrgate6->flag = 0;
					auto ptrRandFlag = ptrgate6->m_RandFlag = false;
					auto ptrDownFlag = ptrgate6->m_DownFlag = true;
					auto ptrChangeFlag = ptrgate6->m_ChangeFlag = false;
					auto ptrChangeFlag1 = ptrgate6->m_ChangeFlag1 = false;
					auto ptrChangeFlag2 = ptrgate6->m_ChangeFlag2 = false;
					auto ptrChangeFlag3 = ptrgate6->m_ChangeFlag3 = false;
				}
			}

			break;
		case 14:
			if (count == 1)
			{
				if (m_Set2Count == 1)
				{
					auto ptrgate7 = GetSharedGameObject<Gate>(L"Gate2");
					RemoveGameObject<Gate>(ptrgate7);
					count--;
				}
				else if (m_Set2Count == 2)
				{
					auto ptrgate8 = GetSharedGameObject<Gate>(L"Gate3");
					RemoveGameObject<Gate>(ptrgate8);
					count--;
				}
			}

			circle->m_next = 2;
			break;
		}
	}
}
//end basecross
