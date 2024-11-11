/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	// コンストラクタ
	GameStage::GameStage() :
		m_StageRation(10.0f) // ステージのサイズ倍率
	{}

	
	void GameStage::CreateViewLight() {
		// カメラの設定MainCamera
		auto camera = ObjectFactory::Create<MainCamera>(0.0f);
		camera->SetEye(Vec3(0.0f, 2.5f, -3.5f));
		//camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// ビューにカメラを設定
		m_View = CreateView<SingleView>();
		m_View->SetCamera(camera);

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>(Vec3(-2.0f,0.4f,0.0f),Vec3(0.3f,0.3f,0.3f),Vec3(0.0f,0.0f,0.0f));
		SetSharedGameObject(L"Player", ptrPlayer);
    }
	void GameStage::CreateWall()
	{
		auto ptrWall = AddGameObject<Wall>(Vec3(0.0f, 10.0f, 50.0f), Vec3(95.0f, 20.0f, 1.0f));//上

	    ptrWall = AddGameObject<Wall>(Vec3(0.0f, 10.0f, -49.0f), Vec3(95.0f, 20.0f, 1.0f));	
		ptrWall = AddGameObject<Wall>(Vec3(47.0f, 10.0f, -46.5f), Vec3(1.0f, 20.0f, 4.0f));//左上の部分
		ptrWall = AddGameObject<Wall>(Vec3(48.0f, 10.0f, -42.0f), Vec3(1.0f, 20.0f, 5.2f));//左上の部分
		ptrWall = AddGameObject<Wall>(Vec3(48.0f, 10.0f, -42.0f), Vec3(1.0f, 20.0f, 5.2f));//左上の部分
		ptrWall = AddGameObject<Wall>(Vec3(49.0f, 10.0f, 0.0f), Vec3(1.0f, 20.0f, 81.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3(47.0f, 10.0f, 47.5f), Vec3(1.0f, 20.0f, 4.0f));//左下の部分
		ptrWall = AddGameObject<Wall>(Vec3(48.0f, 10.0f, 43.0f), Vec3(1.0f, 20.0f, 5.2f));//左下の部分

		ptrWall = AddGameObject<Wall>(Vec3(-47.0f, 10.0f, 46.5f), Vec3(1.0f, 20.0f, 4.0f));//左上の部分
		ptrWall = AddGameObject<Wall>(Vec3(-48.0f, 10.0f, 42.0f), Vec3(1.0f, 20.0f, 5.2f));//左上の部分
		ptrWall = AddGameObject<Wall>(Vec3(-48.0f, 10.0f, 42.0f), Vec3(1.0f, 20.0f, 5.2f));//左上の部分
		ptrWall = AddGameObject<Wall>(Vec3(-49.0f, 10.0f, 0.0f), Vec3(1.0f, 20.0f, 81.0f));//左の部分
		ptrWall = AddGameObject<Wall>(Vec3(-47.0f, 10.0f, -47.5f), Vec3(1.0f, 20.0f, 4.0f));//左下の部分
		ptrWall = AddGameObject<Wall>(Vec3(-48.0f, 10.0f, -43.0f), Vec3(1.0f, 20.0f, 5.2f));//左下の部分



	}

	void GameStage::CreateGround() {		
		//for (int i = 0; i < 7;i++) {
		//	/*auto ptrGround = */
		//	AddGameObject<Ground>(Vec3(0.0f, 0.0f, -50.0f * i), Vec3(100.0f, 0.5f, 50.0f), L"SEA_TX");
		//	//SetSharedGameObject(L"Ground" + i, ptrGround);
		//}
		AddGameObject<Ground>(Vec3(0.0f, -1.0f, 0.0f), Vec3(300.0f, 0.5f, 300.0f), L"SEA_TX");

	}

	void GameStage::CreateObstacle() {
		//for (int i = 0; i < 7; i++) {
		//	AddGameObject<MoveObject>(Vec3(0.0f, 1.0f, -50.0f * i), Vec3(0.05f, 0.05f, 0.05f),L"RED_TX");
		//}
		//for (int i = 0; i < 1; i++) {
		//	AddGameObject<MoveBuoy>(Vec3(-20.0f, 0.0f, -100.0f * i), Vec3(1.0f, 1.0f, 1.0f), L"RED_TX");
		//}

		auto ptrobstacle = AddGameObject<Deployment>();
	}

	void GameStage::CreateTraceSprite() {
		float a = -510.0f;
		float b = 70.0f;

		//AddGameObject<Energy>(L"HANE_TX", true,
		//    Vec2(100.0f, 60.0f), Vec3(a,350.0f, 0.0f));
		//AddGameObject<Energy>(L"HANE_TX", true,
		//	Vec2(100.0f, 60.0f), Vec3(a - b, 350.0f, 0.0f));
		//AddGameObject<Energy>(L"HANE_TX", true,
		//	Vec2(100.0f, 60.0f), Vec3(a + b, 350.0f, 0.0f));

	}

	void GameStage::CreateGoal(){
		//AddGameObject<Goal>(
		//	Vec3(0.0f, 25.0f, -240.0f),//pos z=-240
		//	Vec3(100.0f, 50.0f, 1.0f),//scl
		//	Vec3(0.0f,0.0f,0.0f));//rot
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
			CreateTraceSprite();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
