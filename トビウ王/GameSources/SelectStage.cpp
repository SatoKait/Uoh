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

		//m_Ptr1 = AddGameObject<ScoreSprite>(L"STAGE1", true, Vec2(500, 400), Vec3(0.0f, 300.0f, 0.1f));
		//m_Ptr2 = AddGameObject<ScoreSprite>(L"STAGE2", true, Vec2(500, 400), Vec3(0.0f, 300.0f, 0.1f));

	}

	void SelectStage::OnCreate() {
		App::GetApp()->GetScene<Scene>()->SetScore(0);
		App::GetApp()->GetScene<Scene>()->SetScore2(0);

		try {
			m_select = 0;
			CreateViewLight();
			CreateSprite();
			//m_Ptr1->SetDrawActive(true);
			//m_Ptr2->SetDrawActive(false);
		}
		catch (...) {
			throw;
		}
	}

	void SelectStage::OnUpdate() {
		// デバッグログ
		wstringstream wss(L"");

		//コントローラー判別
		m_InputHandler.PushHandle(GetThis<SelectStage>());
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		SwitchSelect();

		switch (m_select)
		{
		case 0:
			CreateSelect();
			if ((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B || KeyState.m_bPressedKeyTbl[VK_SPACE]))
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			}
			break;

		case 1:
			CreateSelect();
			if ((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B || KeyState.m_bPressedKeyTbl[VK_SPACE]))
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage2");
			}
			break;
		}

	}

	void SelectStage::SwitchSelect()
	{
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

	void SelectStage::CreateSelect()
	{
		//if (m_select == 0)
		//{
		//	m_Ptr2->SetDrawActive(false);
		//	m_Ptr1->SetDrawActive(true);
		//}
		//else if (m_select == 1)
		//{
		//	m_Ptr1->SetDrawActive(false);
		//	m_Ptr2->SetDrawActive(true);
		//}

	}
}
//end basecross
