/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GameOverStage::CreateBGM()
	{
		auto ptrMana = App::GetApp()->GetXAudio2Manager();
		m_stageBGM = ptrMana->Start(L"GAMEOVERSE", 0.0f, 1.0f);

	}
	void GameOverStage::OnDestroy() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_stageBGM);
	}


	void GameOverStage::CreateViewLight() {		//ビューのカメラの設定
		auto cameraView = ObjectFactory::Create<SingleView>(GetThis<GameOverStage>());
		auto ptrMyCamera = ObjectFactory::Create<Camera>();
		cameraView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 0.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
		SetView(cameraView);

		m_flag = false;
		deg = 0.0f;
	}
	void GameOverStage::CreateSprite()
	{
		auto title = AddGameObject<StageSprite>(L"TITLEBACK_TX", true,
			Vec2(1280.0f, 1080.0f), Vec2(0.0f, 0.0f));
		SetSharedGameObject(L"TitleLogo", title);
		auto Layer = GetSharedGameObject<StageSprite>(L"TitleLogo");
		Layer->SetDrawLayer(-100);

		AddGameObject<StageSprite>(L"GAMEOVER_TX", true,
			Vec2(1200.0f, 350.0f), Vec2(0.0f, 200.0f));
		AddGameObject<Flickering>(L"TITLETEXT_TX", true,
			Vec2(450.0f, 100.0f), Vec2(0.0f, -300.0f));


	}
	void GameOverStage::CreateScore()
	{
		//AddGameObject<StageScore>();
	}


	void GameOverStage::OnCreate() {
		try {
			flyingfish = AddGameObject<Model4>(Vec3(0.0f, -0.5f, -2.0f), Vec3(rad, 0.0f, 0.0f));

			CreateViewLight();
			CreateSprite();
			CreateScore();
			CreateBGM();
		}
		catch (...) {
			throw;
		}
	}

	void GameOverStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GameOverStage>());
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
		{
			int a = 0;
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTiTleStage");
		}

		auto flyngfishtrans = flyingfish->GetComponent<Transform>();
		Vec3 spriterot = flyngfishtrans->GetRotation();

		if (!m_flag)
		{
			deg += 1.0f;
			rad = XMConvertToRadians(deg);
			flyngfishtrans->SetRotation(rad, 0.0f, 0.0f);
		}
		if (deg >= 40.0f)
		{
			m_flag = true;
		}
		if (m_flag == true)
		{
			deg += 0.0f;
			rad = XMConvertToRadians(deg);
			flyngfishtrans->SetRotation(rad, 0.0f, 0.0f);
		}
	}

	Model4::Model4(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& StartRot) :
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_StartRot(StartRot)
	{
	}
	Model4::~Model4() {}

	//初期化
	void Model4::OnCreate() {
		//初期位置などの設定
		auto trans = GetComponent<Transform>();

		//auto deg = 0;;
		//auto deg2 = 0;
		//auto rad = XMConvertToRadians(deg);
		//auto rad2 = XMConvertToRadians(deg2);

		trans->SetScale(0.5f, 0.5f, 0.5f);
		trans->SetRotation(m_StartRot);
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
		ptrShadow->SetMeshResource(L"DEADTOBIUO_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEADTOBIUO_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		ptrDraw->AddAnimation(L"Default", 15, 45, false, 60.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//透明処理
		SetAlphaActive(true);
	}

	void Model4::OnUpdate()
	{
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(elapsedTime);
	}
}
//end basecross
