/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void SelectStage::CreateViewLight() {		//ビューのカメラの設定
		auto cameraView = ObjectFactory::Create<SingleView>(GetThis<SelectStage>());
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

	void SelectStage::CreateSprite()
	{
		AddGameObject<StageSprite>(L"STAGESELECT_TX", true,
			Vec2(750.0f, 400.0f), Vec2(0.0f, 200.0f));
	}

	void SelectStage::OnCreate() {
		App::GetApp()->GetScene<Scene>()->SetScore(0);

		try {
			m_select = 0;
			CreateViewLight();
			CreateSprite();
		}
		catch (...) {
			throw;
		}
	}

	void SelectStage::OnUpdate() {
		// デバッグ用ストリーム
		wstringstream wss(L"");

		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<SelectStage>());
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		SwitchSelect();

		if ((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeyState.m_bPressedKeyTbl[VK_SPACE]) && m_select == 0)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}
		if ((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeyState.m_bPressedKeyTbl[VK_SPACE]) && m_select == 1)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage2");
		}

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{

		}
		else if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{

		}
		wss << L"m_select : " <<
			m_select <<

			endl;

		// デバッグ用文字列
		auto scene = App::GetApp()->GetScene<Scene>();
		auto dstr = scene->GetDebugString();
		scene->SetDebugString(wss.str());

	}

	void SelectStage::SwitchSelect()
	{
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<SelectStage>());
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		if ((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT || KeyState.m_bPressedKeyTbl['D']) && m_select <= 0)
		{
			m_select += 1;
		}
		if ((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT || KeyState.m_bPressedKeyTbl['A']) && m_select >= 1)
		{
			m_select -= 1;
		}
	}
}
//end basecross
