/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void GoalScene::CreateBGM()
	{
		auto ptrMana = App::GetApp()->GetXAudio2Manager();
		m_stageBGM = ptrMana->Start(L"GAMECREAL2SE", 0.0f, 1.0f);

	}
	void GoalScene::OnDestroy() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_stageBGM);
	}


	void GoalScene::CreateViewLight() {		//ビューのカメラの設定
		auto cameraView = ObjectFactory::Create<SingleView>(GetThis<GoalScene>());
		auto ptrMyCamera = ObjectFactory::Create<Camera>();
		cameraView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
		SetView(cameraView);
	}
	void GoalScene::CreateSprite()
	{
		AddGameObject<StageSprite>(L"TITLEBACK_TX", true,
			Vec2(1280.0f, 1080.0f), Vec2(0.0f, 0.0f));
		AddGameObject<StageSprite>(L"GOALSCENE_TX", true,
			Vec2(750.0f, 400.0f), Vec2(0.0f, 200.0f));
		AddGameObject<Flickering>(L"TITLETEXT_TX", true,
			Vec2(450.0f, 100.0f), Vec2(0.0f, -300.0f));


	}
	void GoalScene::CreateScore()
	{
		AddGameObject<StageScore>();
	}


	void GoalScene::OnCreate() {
		try {
			
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
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{

		}
		else if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{

		}

	}
}
//end basecross
