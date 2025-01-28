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
		m_ToTalTime(30.0f),
		m_ToStartTime(3.0f),
		m_ToTalTime2(1.0f),
		m_EndTime(10.0f),
		m_isStartFlag(false),
		m_TimeFlag(false),
		m_Flag(false),
		m_DrawFlag(true),
		m_GoalFlag(false),
		m_EndFlag(false),
		m_30secFlag(true),
		m_TimeUpFlag(false),
		m_CreateResultFlag(false),
		m_CreateResultGauge(false),
		m_CreateResult(false),
		m_ResultFlag(false),
		count(0),
		m_SetCount(0),
		m_TimeUpAfter(0.0f),
		m_Set2Count(0),
		m_deltatime1(0.0f),
		m_deltatime2(0.0f),
		m_StrartFlag1(false),
		m_StrartFlag2(false),
		m_MoveFlag(false),
		StartTime(0.0f),
		m_StartDraw(false)
	{}

	void GameStage::CreateViewLight() {		
		// カメラの位置と注視点位置
		const Vec3 eye(0.0f, 2.5f, -3.5f);
		const Vec3 at(0.0f);

		//OpeningCameraView用のビュー
		m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_OpeningCameraView->SetCamera(ptrOpeningCamera);
		//MyCamera用のビュー
		m_MyCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MainCamera>();
		ptrMyCamera->SetEye(eye);
		ptrMyCamera->SetAt(at);
		m_MyCameraView->SetCamera(ptrMyCamera);
		////ObjCamera用のビュー
		//m_ObjCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		//auto ptrObjCamera = ObjectFactory::Create<ObjCamera>();
		//m_ObjCameraView->SetCamera(ptrObjCamera);
		// カメラの設定MainCamera
		m_View = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto camera = ObjectFactory::Create<MainCamera>(-90.0f);
		camera->SetEye(eye);
		camera->SetAt(at);
		//camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		// ビューにカメラを設定
		m_View = CreateView<SingleView>();
		m_View->SetCamera(camera);

		//初期状態ではm_OpeningCameraViewを使う
		SetView(m_OpeningCameraView);
		m_CameraSelect = CameraSelect::openingCamera;
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();

	}
	void GameStage::CameraSetting()
	{
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraman>();
		//シェア配列にOpeningCameramanを追加
		SetSharedGameObject(L"OpeningCameraman", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_OpeningCameraView->GetCamera());
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_OpeningCameraView);
			m_CameraSelect = CameraSelect::openingCamera;

		}
	}

	void GameStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>(Vec3(-2.5f, -15.0f, -45.0f), Vec3(2.0f, 0.25f, 0.25f), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"Player", ptrPlayer);
	}
	void GameStage::CreateWall()
	{
		auto WallCol = AddGameObject<Wall>(Vec3(0.0f, 10.0f, 55.0f), Vec3(95.0f, 20.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));//上
		WallCol = AddGameObject<Wall>(Vec3(0.0f, 10.0f, -54.0f), Vec3(95.0f, 20.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));

		WallCol = AddGameObject<Wall>(Vec3(48.0f, 10.0f, -48.5f), Vec3(1.0f, 20.0f, 10.0f), Vec3(0.0f, 0.261, 0.0f));//左上の部分
		//WallCol = AddGameObject<Wall>(Vec3(48.0f, 10.0f, -42.0f), Vec3(1.0f, 20.0f, 5.2f), Vec3(0.0f, 0.0f, 0.0f));//左上の部分

		WallCol = AddGameObject<Wall>(Vec3(49.0f, 10.0f, 0.0f), Vec3(1.0f, 20.0f, 87.0f), Vec3(0.0f, 0.0f, 0.0f));//左の部分
		WallCol = AddGameObject<Wall>(Vec3(47.0f, 10.0f, 49.0f), Vec3(1.0f, 20.0f, 11.3f), Vec3(0.0f, -0.261, 0.0f));//左下の部分
		
		//WallCol = AddGameObject<Wall>(Vec3(48.0f, 10.0f, 43.0f), Vec3(1.0f, 20.0f, 5.2f), Vec3(0.0f, 0.0f, 0.0f));//左下の部分
		WallCol = AddGameObject<Wall>(Vec3(-48.5f, 10.0f, 49.0f), Vec3(1.0f, 20.0f, 11.3f), Vec3(0.0f, 0.261, 0.0f));//左上の部分
		//WallCol = AddGameObject<Wall>(Vec3(-49.0f, 10.0f, 43.0f), Vec3(1.0f, 20.0f, 5.2f), Vec3(0.0f, 0.0f, 0.0f));//左上の部分
		WallCol = AddGameObject<Wall>(Vec3(-50.0f, 10.0f, 0.5f), Vec3(1.0f, 20.0f, 87.0f), Vec3(0.0f, 0.0f, 0.0f));//左の部分
		WallCol = AddGameObject<Wall>(Vec3(-48.0f, 10.0f, -48.3f), Vec3(1.0f, 20.0f, 11.3f), Vec3(0.0f, -0.261, 0.0f));//左下の部分
		//WallCol = AddGameObject<Wall>(Vec3(-49.0f, 10.0f, -42.0f), Vec3(1.0f, 20.0f, 5.2f), Vec3(0.0f, 0.0f, 0.0f));//左下の部分
	}
	void GameStage::CreatePollCollision()
	{
		//pollCollision
		auto pollCol = AddGameObject<PollCollision>(Vec3(3.0f, 4.2f, 0.0f), Vec3(1.5f, 7.25f, 2.0f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-3.0f, 4.2f, 0.0f), Vec3(1.5f, 7.25f, 2.0f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(0.0f, 4.35f, 0.0f), Vec3(5.0f, 0.4f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(0.0f, 7.75f, 0.0f), Vec3(5.0f, 0.4f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(0.0f, 2.0f, 0.0f), Vec3(5.0f, 4.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));

		//CirecleCollision
		auto CirclepollColrig = AddGameObject<PollCollision>(Vec3(30.0f, 12.75f, 0.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(30.0f, 7.35f, 0.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(26.7f, 10.0f, 0.0f), Vec3(2.6f, 6.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(33.3f, 10.0f, 0.0f), Vec3(2.6f, 6.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		//左右のポール
		pollCol = AddGameObject<PollCollision>(Vec3(33.9f, 3.5f, 0.0f), Vec3(1.7f, 7.0f, 1.7f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(26.2f, 3.5f, 0.0f), Vec3(1.7f, 7.0f, 1.7f), Vec3(0.0f, 0.0f, 0.0f));

		//CirecleCollision左側
		auto CirclepollCollef = AddGameObject<PollCollision>(Vec3(-30.0f, 12.75f, 0.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-30.0f, 7.35f, 0.0f), Vec3(4.0f, 2.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-26.7f, 10.0f, 0.0f), Vec3(2.6f, 6.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-33.3f, 10.0f, 0.0f), Vec3(2.6f, 6.0f, 1.2f), Vec3(0.0f, 0.0f, 0.0f));
		//左右のポール
		pollCol = AddGameObject<PollCollision>(Vec3(-33.8f, 3.5f, 0.0f), Vec3(1.7f, 7.0f, 1.7f), Vec3(0.0f, 0.0f, 0.0f));
		pollCol = AddGameObject<PollCollision>(Vec3(-26.1f, 3.5f, 0.0f), Vec3(1.7f, 7.0f, 1.7f), Vec3(0.0f, 0.0f, 0.0f));

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

		auto ConmboSprite = AddGameObject<ComboSprite>(
			L"COMBO_TX", 
			true,
			Vec2(120.0f, 80.0f),
			Vec3(x, y - 30.0f, 0.0f)
		);
		ConmboSprite->SetDrawLayer(-100);
		SetSharedGameObject(L"ConmboSprite", ConmboSprite);

		auto ConmboSpriteNumber =  AddGameObject<ComboSpriteNumber>(
			L"NUMBER_TX",
			true,
			Vec2(1.0f, 1.0f),
			Vec3(x - 130.0f, y + 44.0f , 0.0f)
		);
		ConmboSpriteNumber->SetDrawLayer(-100);
			SetSharedGameObject(L"ConmboSpriteNumber", ConmboSpriteNumber);

	}
	void GameStage::CreateGoal() {
		//AddGameObject<Goal>(
		//	Vec3(0.0f, 25.0f, -240.0f),//pos z=-240
		//	Vec3(100.0f, 50.0f, 1.0f),//scl
		//	Vec3(0.0f,0.0f,0.0f));//rot
	}
	void GameStage::CreateTime()
	{
		//右側のカウントダウン
		auto Time = AddGameObject<UITime>(2,
			L"NUMBER_TX",
			true,
			Vec2(220.0f, 80.0f),
			Vec3(670.0f, 365.0f, 0.0f));
		Time->SetDrawLayer(-100);
		SetSharedGameObject(L"Time", Time);
		//左側のカウントダウン
		auto Time2 = AddGameObject<UITime2>(2,
			L"NUMBER_TX",
			true,
			Vec2(220.0f, 80.0f),
			Vec3(530.0f, 365.0f, 0.0f));
		Time2->SetDrawLayer(-100);
		SetSharedGameObject(L"Time2", Time2);
		//:の部分を表示している
		auto ptrSprite = AddGameObject<StageSprite>(L"TIME_TX", true,
			Vec2(350.0f, 80.0f), Vec2(495.0f, 355.0f));
		ptrSprite->SetDrawLayer(-100);
		SetSharedGameObject(L"TimeSprite", ptrSprite);	
		//AddGameObject<StageSprite>(L"PARTITION_TX", true,
		//Vec2(500.0f, 100.0f), Vec2(-15.0f, 350.0f));
		//auto score = AddGameObject<Score>();
		//AddGameObject<StageScore>();
		//SetSharedGameObject(L"Score", ptrscore);
		
		// HPゲージの生成
		auto ptrHpGauge = AddGameObject<GaugeScore>(false,
			Vec2(360.0f, 2.0f), Vec3(-540.0f, -360.0f, 0.0f), L"ORANGE_TX");
		SetSharedGameObject(L"Gauge", ptrHpGauge);
		auto ptrGaugeSpriteNumber = AddGameObject<GaugeSpriteNumber>(L"NUMBER_TX",
			true,
			Vec2(1.3f, 0.85f), Vec3(-448.0f, -300.0f, 0.0f));
		SetSharedGameObject(L"GaugeSpriteNumber", ptrGaugeSpriteNumber);
		// HPゲージの生成
		auto ptrHpGauge2 = AddGameObject<GaugeScoreEnemy>(false,
			Vec2(360.0f, 2.0f), Vec3(-615.0f, -360.0f, 0.0f), L"PURPLE_TX");
		SetSharedGameObject(L"GaugeEnemy", ptrHpGauge2);
		// 説明のアイコンを生成
		auto YouIcon = AddGameObject<StageSprite>(L"YOU_TX", true,
			Vec2(90.0f, 50.0f), Vec2(-515.0f, -378.0f));
		YouIcon->SetDrawLayer(-100);
		SetSharedGameObject(L"YouIcon", YouIcon);
		auto UIIcon = AddGameObject<StageSprite>(L"ICON_TX", true,
			Vec2(200.0f, 100.0f), Vec2(520.0f, -340.0f));
		UIIcon->SetDrawLayer(-100);
		SetSharedGameObject(L"UIIcon", UIIcon);
		auto Kakeru = AddGameObject<StageSprite>(L"KAKERU_TX", true,
			Vec2(64.0f, 64.0f), Vec2(-460.0f, -360.0f));
		Kakeru->SetDrawLayer(-100);
		SetSharedGameObject(L"Kakeru", Kakeru);
	}
	void GameStage::CreateStageTime()
	{
		//始まりのカウントダウン
		auto CountTime =  AddGameObject<UITimeStage>(1,
			L"NUMBER2_TX",
			true,
			Vec2(480.0f, 200.0f),
			Vec3(250.0f, 0.0f, 0.0f));
		CountTime->SetDrawLayer(-900);
		SetSharedGameObject(L"CountTime", CountTime);
		//終わりのカウントダウン
		AddGameObject<LastTime>(1,
			L"LASTTIME_TX",
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
		SetSharedGameObject(L"NPC", ptr);
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
			CameraSetting();
			auto& app = App::GetApp();
			auto path = app->GetDataDirWString();

			auto miniMapManager = AddGameObject<MiniMapManager>(100);//ミニマップ生成デバック用
			SetSharedGameObject(L"MiniMapManager", miniMapManager);
			miniMapManager->CreateMoveGate();
			miniMapManager->CreatePlayer();

			App::GetApp()->GetScene<Scene>()->SetScore(0);
			App::GetApp()->GetScene<Scene>()->SetScore2(0);

			App::GetApp()->GetScene<Scene>()->SetPoint(0);
			App::GetApp()->GetScene<Scene>()->SetPoint2(0);

			auto skyboxPath = path + L"skybox/";
			for (const auto& keyName : Skybox2::pairs) {
				app->RegisterTexture(keyName.first, skyboxPath + keyName.first + L".bmp");
			}


			auto PlayerBAR = AddGameObject<StageSprite>(L"BAR_TX", true,
				Vec2(256.0f, 256.0f), Vec2(-515.0f, -260.0f));
			PlayerBAR->SetDrawLayer(-100);
				SetSharedGameObject(L"PlayerBAR", PlayerBAR);
			auto EnemyBAR = AddGameObject<StageSprite>(L"BAR_TX", true,
				Vec2(256.0f, 256.0f), Vec2(-590.0f, -260.0f));
			EnemyBAR->SetDrawLayer(-100);
			SetSharedGameObject(L"EnemyBAR", EnemyBAR);
			// Skyboxクラス用
			app->RegisterTexture(L"skybox", skyboxPath + L"skybox1.png"); // テクスチャを１枚にまとめたバージョン
			// スカイボックス
			AddGameObject<Skybox>(); // テクスチャを１枚にまとめたバージョン
			//AddGameObject<Skybox2>();

			auto Rank = AddGameObject<RankSpriteNumber>(L"NUMBER_TX", true,
				Vec2(1.0f, 1.0f), Vec3(-540.0f, -50.0f, 0.0f));
			Rank->SetDrawLayer(-100);
			auto Rank2 = AddGameObject<RankSpriteNumber>(L"NUMBER_TX", true,
				Vec2(1.0f, 1.0f), Vec3(-620.0f, -50.0f, 0.0f));
			Rank2->SetDrawLayer(-100);
			SetSharedGameObject(L"Rank", Rank);
			SetSharedGameObject(L"Rank2", Rank2);
			//AddGameObject<ScoreSprite>();
			
			// HPゲージの生成
			auto ptrPlayerGauge = AddGameObject<PlayerRusultScore>(false,
				Vec2(8.2f, 5.0f), Vec3(-410.0f, 40.0f, 0.0f), L"RED_TX");
			ptrPlayerGauge->SetDrawLayer(-1000);
			SetSharedGameObject(L"PlayerResultGauge", ptrPlayerGauge);

			auto ptrNPCGauge = AddGameObject<NPCRusultScore>(false,
				Vec2(8.2f, 5.0f), Vec3(410.0f, 40.0f, 0.0f), L"BLUE_TX");
			ptrNPCGauge->SetDrawLayer(-1000);
			SetSharedGameObject(L"NPCResultGauge", ptrNPCGauge);

			auto IconPlayer = AddGameObject<JumpSprite>
				(L"MiniMapPlayer_TX", true,
					Vec2(150.0f, 150.0f), Vec2(-495.0f, 0.0f));
			SetSharedGameObject(L"ResultIconPlayer", IconPlayer);
			IconPlayer->SetDrawLayer(-999);
			auto IconNPC = AddGameObject<JumpSprite>
				(L"MiniMapNPC_TX", true,
					Vec2(150.0f, 150.0f), Vec2(495.0f, 0.0f));
			SetSharedGameObject(L"ResultIconNPC", IconNPC);
			IconNPC->SetDrawLayer(-999);

            auto StageText = AddGameObject<StageSprite>(L"STAGETEXT_TX", true,
				Vec2(1200.0f, 200.0f), Vec2(0.0f, 20.0f));
			SetSharedGameObject(L"StageText", StageText);
			auto GaugeHide = AddGameObject<StageSprite>(L"GaugeHide_TX", true,
				Vec2(270.0f, 285.0f), Vec2(-513.0f, -255.0f));
			GaugeHide->SetDrawLayer(-90);
			SetSharedGameObject(L"GaugeHide", GaugeHide);
			auto GaugeHide2 = AddGameObject<StageSprite>(L"GaugeHide2_TX", true,
				Vec2(270.0f, 285.0f), Vec2(-590.0f, -255.0f));
			GaugeHide2->SetDrawLayer(-90);
			SetSharedGameObject(L"GaugeHide2", GaugeHide2);
			auto GaugeHide3 = AddGameObject<StageSprite>(L"GaugeHide3_TX", true,
				Vec2(75.0f, 75.0f), Vec2(-415.0f, -352.0f));
			GaugeHide3->SetDrawLayer(-90);
			SetSharedGameObject(L"GaugeHide3", GaugeHide3);


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

		auto score1 = App::GetApp()->GetScene<Scene>()->GetPoint();
		auto score2 = App::GetApp()->GetScene<Scene>()->GetPoint2();
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrNPC = GetSharedGameObject<NPC>(L"NPC");
		auto GoalFlag = ptrPlayer->m_GoalFlag;
		auto m_count = ptrPlayer->m_CircleCount;
		auto gauge = GetSharedGameObject<GaugeScore>(L"Gauge");
		auto gaugecount = gauge->Count;

		auto Rank = GetSharedGameObject<RankSpriteNumber>(L"Rank");
		auto Rank2 = GetSharedGameObject<RankSpriteNumber>(L"Rank2");
		
		auto ptrPlayerResultScore = GetSharedGameObject<PlayerRusultScore>(L"PlayerResultGauge");
		auto ptrNPCResultScore = GetSharedGameObject<NPCRusultScore>(L"NPCResultGauge");

		auto ptrPlayerResultIcon = GetSharedGameObject<JumpSprite>(L"ResultIconPlayer");
		auto ptrNPCResultIcon= GetSharedGameObject<JumpSprite>(L"ResultIconNPC");
		
		auto CountTime = GetSharedGameObject<UITimeStage>(L"CountTime");
		auto StageText = GetSharedGameObject<StageSprite>(L"StageText");

		auto GaugeHide = GetSharedGameObject<StageSprite>(L"GaugeHide");
		auto GaugeHide2 = GetSharedGameObject<StageSprite>(L"GaugeHide2");
		auto GaugeHide3 = GetSharedGameObject<StageSprite>(L"GaugeHide3");

		Rank->UpdateValue(m_rank);
		Rank2->UpdateValue(m_rank2);
		
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START && cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_BACK)
		{
			ptrMana->Stop(m_BGM);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTiTleStage");
		}

		if (score1 >= score2)
		{ 
			m_rank = 1;
			Rank->SetColor(Col4(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			m_rank = 2;
			Rank->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (score2 >= score1)
		{
			m_rank2 = 1;
			Rank2->SetColor(Col4(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			m_rank2 = 2;
			Rank2->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y)
		{
			//ptrMana->Stop(m_BGM);

			//if (score1 > score2)
			//{
			//	PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGoalScene");
			//}
			//else
			//{
			//	PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
			//}
		}
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto CameraFlag = ptrPlayer->m_CameraFlag;
		auto PlayerMoveFlag = ptrPlayer->m_MoveFlag;
		auto NPCStopFlag = ptrNPC->m_stopFlag;
		StartTime += delta;
		if (StartTime >= 8.0f && !m_StartDraw)
		{		
			StageText->SetDrawLayer(-90);
			CountTime->SetDrawLayer(100);
			auto ptrUITime = GetSharedGameObject<UITime>(L"UITime");
			ptrUITime->SetDrawLayer(100);
			auto ptrUITime2 = GetSharedGameObject<UITime2>(L"UITime2");
			ptrUITime2->SetDrawLayer(100);
			auto ptrSprite = GetSharedGameObject<StageSprite>(L"TimeSprite");
			ptrSprite->SetDrawLayer(100);
			auto ptrUIIcon = GetSharedGameObject<StageSprite>(L"UIIcon");
			ptrUIIcon->SetDrawLayer(100);
			auto ptrConmboSprite = GetSharedGameObject<ComboSprite>(L"ConmboSprite");
			ptrConmboSprite->SetDrawLayer(100);
			auto ptrConmboSpriteNumber = GetSharedGameObject<ComboSpriteNumber>(L"ConmboSpriteNumber");
			ptrConmboSpriteNumber->SetDrawLayer(100);
			auto MiniMapSprite = GetSharedGameObject<MiniMapManager>(L"MiniMapManager");
			MiniMapSprite->SetDrawLayer(-100);
			auto PlayerBAR = GetSharedGameObject<StageSprite>(L"PlayerBAR");
			PlayerBAR->SetDrawLayer(100);
			auto EnemyBAR = GetSharedGameObject<StageSprite>(L"EnemyBAR");
			EnemyBAR->SetDrawLayer(100);
			auto YouIcon = GetSharedGameObject<StageSprite>(L"YouIcon");
			YouIcon->SetDrawLayer(100);
			Rank->SetDrawLayer(100);
			Rank2->SetDrawLayer(100);
			m_ToStartTime -= elapsedTime;
		}
		if (m_ToStartTime <= 0)
		{
			if (!m_StartDraw)
			{
				auto Start = AddGameObject<StageSprite>(L"START_TX", true,
					Vec2(512.0f, 256.0f), Vec2(0.0f, 0.0f));
				Start->SetDrawLayer(100);
				SetSharedGameObject(L"Start", Start);
			}
			m_StartDraw = true;
			CountTime->SetDrawLayer(-90);
			m_isStartFlag = true;
			if (m_StartDraw && StartTime >= 12.0f)
			{
				auto Start = GetSharedGameObject<StageSprite>(L"Start");
				Start->SetDrawLayer(-100);
			}

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
				m_DrawFlag = false;
			}

			if (m_ToTalTime <= 0.0f && m_TimeFlag == true && m_Flag == true) {
				if (m_TimeUpFlag == false)
				{	
					ptrMana->Stop(m_BGM);
					auto EndText = AddGameObject<StageSprite>(L"END_TX", true,
						Vec2(1024.0f, 512.0f), Vec2(0.0f, 0.0f));
					SetSharedGameObject(L"EndText", EndText);
					ptrMana->Start(L"TIMEUPSE", 0, 0.5f);
					m_TimeUpFlag = true;
				}
				m_TimeUpAfter += delta;
				ptrPlayer->m_MoveFlag = false;		
				ptrNPC->m_stopFlag = true;
				if (m_TimeUpAfter >= 3.0f)
				{
					auto EndText = GetSharedGameObject<StageSprite>(L"EndText");
					EndText->SetDrawLayer(-100);
					if (m_CreateResultFlag == false)
					{
						ptrMana->Start(L"RESULT", 0, 1.0f);

						auto ptrPlayerFlag = ptrPlayerResultScore->m_UpdateStartFlag = true;
						auto ptrNPCFlag = ptrNPCResultScore->m_UpdateStartFlag = true;

						auto Result = AddGameObject<StageSprite>
							(L"Haikei_TX", true,
								Vec2(1920.0f, 1080.0f), Vec2(0.0f, 0.0f));
						Result->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.7f));
						Result->SetDrawLayer(997);
						m_CreateResultFlag = true;

						if (m_CreateResultFlag = true && m_CreateResultGauge == false)
						{
							ptrPlayerResultIcon->SetDrawLayer(998);
							ptrNPCResultIcon->SetDrawLayer(998);
							ptrPlayerResultScore->SetDrawLayer(999);
							ptrNPCResultScore->SetDrawLayer(999);
						}
					}
				}
			}
		}

		auto ptrPlayerFlag = ptrPlayerResultScore->m_CreateFlag;
		
			


		if (ptrPlayerFlag && m_ResultFlag ==  false)
		{
			m_ResultFlag = true;
			ptrPlayerResultScore->SetDrawLayer(-1000);
			ptrNPCResultScore->SetDrawLayer(-1000);

			auto ptrPlayerResutlt = AddGameObject<PlayerResultGauge>(false,
				Vec2(8.2f, 5.0f), Vec3(-410.0f, 40.0f, 0.0f), L"RED_TX");
			ptrPlayerResutlt->SetDrawLayer(999);
			SetSharedGameObject(L"PlayerResult", ptrPlayerResutlt);
			auto ptrNPCResutlt = AddGameObject<NPCResultGauge>(false,
				Vec2(8.2f, 5.0f), Vec3(410.0f, 40.0f, 0.0f), L"BLUE_TX");
			ptrNPCResutlt->SetDrawLayer(999);
			SetSharedGameObject(L"NPCResult", ptrNPCResutlt);
			m_CreateResultGauge = true;
			m_CreateResultFlag = true;

			if (score1 > score2)
			{
				auto delta = App::GetApp()->GetElapsedTime();
				ptrPlayerResultIcon->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"MiniMapPlayer_TX");
				ptrPlayerResultIcon->m_MoveFlag = true;
				ptrNPCResultIcon->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"MiniMapNPC_TX");
				ptrNPCResultIcon->m_DownMoveFlag = true;

				auto IconPlayer = AddGameObject<JumpSprite>
					(L"HAPPY_TX", true,
						Vec2(150.0f, 150.0f), Vec2(-495.0f, 0.0f));
				IconPlayer->SetDrawLayer(999);
				IconPlayer->m_MoveFlag = true;
				auto IconNPC = AddGameObject<JumpSprite>
					(L"UNHAPPY_TX", true,
						Vec2(150.0f, 150.0f), Vec2(495.0f, 0.0f));
				IconNPC->SetDrawLayer(999);
				IconNPC->m_DownMoveFlag = true;
				m_StrartFlag1 = true;
			}
			else
			{
				auto delta = App::GetApp()->GetElapsedTime();

				ptrPlayerResultIcon->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"MiniMapPlayer_TX");
				ptrPlayerResultIcon->m_DownMoveFlag = true;
				ptrNPCResultIcon->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"MiniMapNPC_TX");
				ptrNPCResultIcon->m_MoveFlag = true;


				auto IconPlayer2 = AddGameObject<JumpSprite>
					(L"HAPPY_TX", true,
						Vec2(150.0f, 150.0f), Vec2(495.0f, 0.0f));
				IconPlayer2->SetDrawLayer(999);
				IconPlayer2->m_MoveFlag = true;
				auto IconNPC2 = AddGameObject<JumpSprite>
					(L"UNHAPPY_TX", true,
						Vec2(150.0f, 150.0f), Vec2(-495.0f, 0.0f));
				IconNPC2->SetDrawLayer(999);
				IconNPC2->m_DownMoveFlag = true;
				m_StrartFlag2 = true;
			}
		}			

		if (m_StrartFlag1 == true)
		{
			m_deltatime1 += delta;
		}
		if (m_StrartFlag2 == true)
		{
			m_deltatime2 += delta;
		}

		if (m_deltatime1 >= 3.0f)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGoalScene");
		}

		if (m_deltatime2 >= 3.0f)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
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

			GaugeHide->SetDrawLayer(90);
			GaugeHide2->SetDrawLayer(90);
			GaugeHide3->SetDrawLayer(90);


			auto ptrUITime = GetSharedGameObject<UITime>(L"UITime");
			ptrUITime->SetColor(Col4(1.0f, 1.0f, 0.0f, 1.0f));
			auto ptrUITime2 = GetSharedGameObject<UITime2>(L"UITime2");
			ptrUITime2->SetColor(Col4(1.0f, 1.0f, 0.0f, 1.0f));
			auto Rank = GetSharedGameObject<RankSpriteNumber>(L"Rank");
			Rank->SetDrawLayer(-100);
			auto Rank2 = GetSharedGameObject<RankSpriteNumber>(L"Rank2");
			Rank2->SetDrawLayer(-100);

		}
		//スコアを更新する
		auto ptrScor = GetSharedGameObject<UITime>(L"UITime");
		ptrScor->SetScore(m_ToTalTime);
		auto ptrScor2 = GetSharedGameObject<UITime2>(L"UITime2");
		ptrScor2->SetScore(m_ToTalTime2);

		//これで最後の演出をすることが出来る
		if (m_TimeFlag == true && m_ToTalTime <= 11.0f && m_EndFlag == false)
		{
			m_EndFlag = true;
			auto ptrScor3 = GetSharedGameObject<LastTime>(L"LastTime");
			ptrScor3->m_isDrawFlag = true;
		}
		if (m_TimeFlag == true && m_ToTalTime <= 11.0f && m_EndFlag == true)
		{
			m_EndTime += elapsedTime;
			auto ptrScor3 = GetSharedGameObject<LastTime>(L"LastTime");
			ptrScor3->SetScore3(m_EndTime);

			auto ptrUITime = GetSharedGameObject<UITime>(L"UITime");
			ptrUITime->SetColor(Col4(1.0f, 0.0f, 0.0f, 1.0f));
			auto ptrUITime2 = GetSharedGameObject<UITime2>(L"UITime2");
			ptrUITime2->SetColor(Col4(1.0f, 0.0f, 0.0f, 1.0f));

		}
		if (m_TimeFlag == true && m_ToTalTime <= 1.0f && m_EndFlag == true)
		{
			auto ptrScor3 = GetSharedGameObject<LastTime>(L"LastTime");
			ptrScor3->m_isDrawFlag = false;
			auto ptrUITime = GetSharedGameObject<UITime>(L"UITime");
			ptrUITime->m_isBackGrundDrawFlag = true;
			auto ptrUITime2 = GetSharedGameObject<UITime2>(L"UITime2");
			ptrUITime2->m_isBackGrundDrawFlag = true;
			auto ptrSprite = GetSharedGameObject<StageSprite>(L"TimeSprite");
			ptrSprite->SetDrawLayer(-100);
			auto ptrUIIcon = GetSharedGameObject<StageSprite>(L"UIIcon");
			ptrUIIcon->SetDrawLayer(-100);
			auto ptrConmboSprite = GetSharedGameObject<ComboSprite>(L"ConmboSprite");
			ptrConmboSprite->SetDrawLayer(-100);
			auto ptrConmboSpriteNumber = GetSharedGameObject<ComboSpriteNumber>(L"ConmboSpriteNumber");
			ptrConmboSpriteNumber->SetDrawLayer(-100);
			//auto MiniMapSpritehaikei = GetSharedGameObject<MiniMapSprite>(L"haikei");
			//MiniMapSpritehaikei->SetDrawLayer(-100);
			//auto MiniMapSpriteGate = GetSharedGameObject<MiniMapSprite>(L"MiniMapGate");
			//MiniMapSpriteGate->SetDrawLayer(-100);
			auto PlayerBAR = GetSharedGameObject<StageSprite>(L"PlayerBAR");
			PlayerBAR->SetDrawLayer(-100);
			auto EnemyBAR = GetSharedGameObject<StageSprite>(L"EnemyBAR");
			EnemyBAR->SetDrawLayer(-100);
			auto ptrHpGauge = GetSharedGameObject<GaugeScore>(L"Gauge");
			ptrHpGauge->SetDrawLayer(-100);
			auto ptrGaugeSpriteNumber = GetSharedGameObject<GaugeSpriteNumber>(L"GaugeSpriteNumber");
			ptrGaugeSpriteNumber->SetDrawLayer(-100);
			auto ptrHpGauge2 = GetSharedGameObject<GaugeScoreEnemy>(L"GaugeEnemy");
			ptrHpGauge2->SetDrawLayer(-100);
			auto Kakeru = GetSharedGameObject<StageSprite>(L"Kakeru");
			Kakeru->SetDrawLayer(-100);
			auto YouIcon = GetSharedGameObject<StageSprite>(L"YouIcon");
			YouIcon->SetDrawLayer(-100);
			Rank->SetDrawLayer(-100);
			Rank2->SetDrawLayer(-100);

			//auto MinimapDraw = GetSharedGameObject<MiniMapManager>(L"MiniMapManager");
			//MinimapDraw->m_MiniMapDrawFlag = true;
			GaugeHide->SetDrawLayer(-100);
			GaugeHide2->SetDrawLayer(-100);
			GaugeHide3->SetDrawLayer(-100);

		}
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
				else if (m_SetCount == 2)
				{
					SetSharedGameObject(L"Gate5", ptrgate);
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
				else if (m_SetCount == 3)
				{
					auto ptrgate10 = GetSharedGameObject<Gate>(L"Gate5");
					auto ptrFlag = ptrgate10->flag = 0;
					auto ptrRandFlag = ptrgate10->m_RandFlag = false;
					auto ptrDownFlag = ptrgate10->m_DownFlag = true;
					auto ptrChangeFlag = ptrgate10->m_ChangeFlag = false;
					auto ptrChangeFlag1 = ptrgate10->m_ChangeFlag1 = false;
					auto ptrChangeFlag2 = ptrgate10->m_ChangeFlag2 = false;
					auto ptrChangeFlag3 = ptrgate10->m_ChangeFlag3 = false;
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
				else if (m_SetCount == 3)
				{
					auto ptrgate3 = GetSharedGameObject<Gate>(L"Gate5");
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
				else if (m_Set2Count == 2)
				{
					SetSharedGameObject(L"Gate4", ptrgate4);
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
				else if (m_Set2Count == 1)
				{
					auto ptrgate11 = GetSharedGameObject<Gate>(L"Gate4");
					auto ptrFlag = ptrgate11->flag = 0;
					auto ptrRandFlag = ptrgate11->m_RandFlag = false;
					auto ptrDownFlag = ptrgate11->m_DownFlag = true;
					auto ptrChangeFlag = ptrgate11->m_ChangeFlag = false;
					auto ptrChangeFlag1 = ptrgate11->m_ChangeFlag1 = false;
					auto ptrChangeFlag2 = ptrgate11->m_ChangeFlag2 = false;
					auto ptrChangeFlag3 = ptrgate11->m_ChangeFlag3 = false;
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
				else if (m_Set2Count == 3)
				{
					auto ptrgate8 = GetSharedGameObject<Gate>(L"Gate4");
					RemoveGameObject<Gate>(ptrgate8);
					count--;
				}

			}

			circle->m_next = 2;
			break;
		}
	}
	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//MyCameraに変更
		auto ptrMyCamera = dynamic_pointer_cast<MainCamera>(m_View->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTarget(ptrPlayer);
			//m_MyCameraViewを使う
			SetView(m_View);
			m_CameraSelect = CameraSelect::myCamera;
		}
	}
	void GameStage::OnDraw() {
	}
}
//end basecross
