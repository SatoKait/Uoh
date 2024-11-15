/*!
@file　TitleStage.cpp
@brief タイトルなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleStage::CreateViewLight() {		//ビューのカメラの設定
		auto cameraView = ObjectFactory::Create<SingleView>(GetThis<TitleStage>());
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

	void TitleStage::CreateSprite()
	{		
		AddGameObject<StageSprite>(L"TITLEBACK_TX", true,
			Vec2(1280.0f, 1080.0f), Vec2(0.0f, 0.0f));
		AddGameObject<StageSprite>(L"LOGO_TX", true,
			Vec2(750.0f, 300.0f), Vec2(0.0f, 200.0f));
	}

	void TitleStage::OnCreate() {
		App::GetApp()->GetScene<Scene>()->SetScore(0);

		try {
			CreateViewLight();
			CreateSprite();
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
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
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
