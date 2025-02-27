/*!
@file GoalScene.cpp
@brief ゴールシーンの実体
@authors SatouKaito AndouTinami YoshidaTomoki
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void GoalScene::CreateBGM()
	{
		auto ptrMana = App::GetApp()->GetXAudio2Manager();
		m_stageBGM = ptrMana->Start(L"GAMECREAL2SE", 0.0f, 0.5f);

	}
	void GoalScene::OnDestroy() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_stageBGM);
	}


	void GoalScene::CreateViewLight() {		//ビューのカメラの設定
		auto cameraView = ObjectFactory::Create<SingleView>(GetThis<GoalScene>());
		auto ptrMyCamera = ObjectFactory::Create<Camera>();
		cameraView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, -3.5f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, -2.5f, 1.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
		SetView(cameraView);

		m_comY = -0.6f;
		m_flag = false;
	}
	void GoalScene::CreateSprite()
	{
		auto title = AddGameObject<StageSprite>(L"TITLEBACK_TX", true,
			Vec2(1280.0f, 1080.0f), Vec2(0.0f, 0.0f));
		SetSharedGameObject(L"TitleLogo", title);
		auto Layer = GetSharedGameObject<StageSprite>(L"TitleLogo");
		Layer->SetDrawLayer(-100);

		auto Goal = AddGameObject<StageSprite>(L"GOALSCENE_TX", true,
			Vec2(1000.0f, 400.0f), Vec2(0.0f, 250.0f));
		Goal->SetDrawLayer(-50);
		AddGameObject<Flickering>(L"TITLETEXT_TX", true,
			Vec2(640.0f, 200.0f), Vec2(0.0f, -330.0f));


	}
	void GoalScene::CreateScore()
	{
		//AddGameObject<StageScore>();
	}


	void GoalScene::OnCreate() {
		try {
			AddGameObject<Model2>(Vec3(0.0f, -3.8f, -0.0f));
			AddGameObject<Model5>(Vec3(0.0f, -4.3f, -0.0f));

			CreateViewLight();
			CreateSprite();
			CreateScore();
			CreateBGM();
		}
		catch (...) {
			throw;
		}
	}

	void GoalScene::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GoalScene>());
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
		{
			int a = 0;
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTiTleStage");
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{

		}
		else if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{

		}
	}

	Model2::Model2(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos)
	{
	}
	Model2::~Model2() {}

	//初期化
	void Model2::OnCreate() {
		//初期位置などの設定
		auto trans = GetComponent<Transform>();

		auto deg = -90;
		auto deg2 = 0;
		auto rad = XMConvertToRadians(deg);
		auto rad2 = XMConvertToRadians(deg2);

		trans->SetScale(0.7f, 0.7f, 0.7f);
		trans->SetRotation(Vec3(0.0f, rad, rad2));
		trans->SetPosition(m_StartPos);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.3f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"HAPPYTOBIUO_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"HAPPYTOBIUO_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		ptrDraw->AddAnimation(L"Default", 123, 140, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//透明処理
		SetAlphaActive(true);
	}

	void Model2::OnUpdate()
	{
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(elapsedTime);
	}

	Model5::Model5(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos)
	{
	}
	Model5::~Model5() {}

	//初期化
	void Model5::OnCreate() {
		//初期位置などの設定
		auto trans = GetComponent<Transform>();

		trans->SetScale(0.1f, 0.1f, 0.1f);
		trans->SetRotation(0.0f, 0.0f, 0.0f);
		trans->SetPosition(m_StartPos);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.3f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"PODIUM_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"PODIUM_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//透明処理
		SetAlphaActive(true);
	}
}
//end basecross
