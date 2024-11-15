/*!
@file　GameStage2.cpp
@brief タイトルなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GameStage2::CreateViewLight() {		//ビューのカメラの設定
		auto cameraView = ObjectFactory::Create<SingleView>(GetThis<GameStage2>());
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

	void GameStage2::CreateSprite()
	{
	}

	void GameStage2::OnCreate() {
		try {
			CreateViewLight();
			CreateSprite();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage2::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GameStage2>());
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y)
		{
			int a = 0;
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage2");
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
