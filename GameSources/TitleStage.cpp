/*!
@file　TitleStage.cpp5
@brief タイトルなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleStage::CreateViewLight() {		//ビューのカメラの設定
		auto cameraView = ObjectFactory::Create<SingleView>(GetThis<TitleStage>());
		auto ptrMyCamera = ObjectFactory::Create<Camera>();
		cameraView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, -0.8f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
		SetView(cameraView);

		m_comX = 3.0f;
		m_flag = false;
		deg = 0.0f;
		deg2 = 0.0f;
	}



	void TitleStage::CreateSprite()
	{		
		auto title = AddGameObject<StageSprite>(L"TITLEBACK_TX", true,
			Vec2(1280.0f, 1080.0f), Vec2(0.0f, 0.0f));
		SetSharedGameObject(L"TitleLogo", title);
		auto Layer = GetSharedGameObject<StageSprite>(L"TitleLogo");
		Layer->SetDrawLayer(-100);

		AddGameObject<StageSprite>(L"LOGO_TX", true,
			Vec2(1300.0f, 800.0f), Vec2(0.0f, 200.0f));
		AddGameObject<Flickering>(L"TITLETEXT_TX", true,
			Vec2(640.0f, 200.0f), Vec2(0.0f, -150.0f));

		AddGameObject<StageSprite>(L"WAVE_TX", true,
			Vec2(1280.0f, 1080.0f), Vec2(0.0f, 100.0f));
	}

	void TitleStage::OnCreate() {
		App::GetApp()->GetScene<Scene>()->SetScore(0);
		App::GetApp()->GetScene<Scene>()->SetScore2(0);

		flyingfish = AddGameObject<Model1>(Vec3(0.0f, -1.0f, -2.0f), Vec3(0.0f, rad, 0.0f));

		try {
			CreateViewLight();
			CreateSprite();
			CreateBGM();
		}
		catch (...) {
			throw;
		}

	}

	void TitleStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<TitleStage>());
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B || KeyState.m_bPressedKeyTbl[VK_SPACE])
		{
			int a = 0;
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT || KeyState.m_bPressedKeyTbl[VK_RETURN])
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
		}
		else if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{

		}

		auto flyngfishtrans = flyingfish->GetComponent<Transform>();
		Vec3 spritepos = flyngfishtrans->GetPosition();
		Vec3 spriterot = flyngfishtrans->GetRotation();

		if (!m_flag)
		{
			deg = 0.0f;
			rad = XMConvertToRadians(deg);
			flyngfishtrans->SetRotation(0.0f, rad, 0.0f);

			m_comX -= 0.01f;
			flyngfishtrans->SetPosition(m_comX, -1.3f, -2.0f);
		}
		if (m_comX <= -4.0f)
		{
			m_flag = true;
		}

		if (m_flag == true)
		{
			deg = 180.0f;
			rad = XMConvertToRadians(deg);
			flyngfishtrans->SetRotation(0.0f, rad, 0.0f);

			m_comX += 0.01f;
			flyngfishtrans->SetPosition(m_comX, -1.3f, -2.0f);
		}
		if (m_comX >= 4.0f)
		{
			m_flag = false;
		}
	}

	// BGMの再生
	void TitleStage::CreateBGM() {

		auto ptrMana = App::GetApp()->GetXAudio2Manager();
		m_stageBGM  = ptrMana->Start(L"STAGEBGM", XAUDIO2_LOOP_INFINITE, 0.5f);
		m_stageBGM2 = ptrMana->Start(L"KAMOMESE", XAUDIO2_LOOP_INFINITE, 0.2f);
	}
	void TitleStage::OnDestroy() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_stageBGM);
		XAPtr->Stop(m_stageBGM2);
	}

	Model1::Model1(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& StartRot) :
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_StartRot(StartRot)
	{
	}
	Model1::~Model1() {}

	//初期化
	void Model1::OnCreate() {
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
		ptrShadow->SetMeshResource(L"TOBIUO_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"TOBIUO_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		ptrDraw->AddAnimation(L"Swim", 15, 40, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Swim");

		//透明処理
		SetAlphaActive(true);
	}

	void Model1::OnUpdate()
	{
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(elapsedTime);
	}


}
//end basecross
