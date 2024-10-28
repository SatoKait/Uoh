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
		// カメラの設定
		auto camera = ObjectFactory::Create<MainCamera>(90.0f);
		//camera->SetEye(Vec3(0.0f, 15.0f, -5.0f));
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
		auto ptrPlayer = AddGameObject<Player>(Vec3(0.0f,1.0f,30.0f),Vec3(0.5f,0.5f,0.5f));
		SetSharedGameObject(L"Player", ptrPlayer);

    }

	void GameStage::CreateGround() {

		//auto ptrBlock = AddGameObject<Block>();
		//auto ptrmap = AddGameObject<Map>();

		//Vec3 startPos =   Vec3(0.0f, 0.0f,  30.0f);
	 //   Vec3 startScale = Vec3(5.0f, 1.0f, 100.0f);
		auto ptrGround = AddGameObject<Ground>(Vec3(0.0f, 0.0f, -235.0f),Vec3(500.0f, 1.0f, 500.0f));
	}

	void GameStage::CreateObstacle() {
		Vec3 startPos   =  Vec3(-2.0f,1.5f,0.0f);
		Vec3 startScale =  Vec3( 0.5f,3.0f,0.5f);
		auto ptrGround = AddGameObject<Pole>(startPos, startScale);
	}

	void GameStage::CreateTraceSprite() {
		float a = -510.0f;
		float b = 70.0f;

		AddGameObject<ScrollSprite>(L"HANE_TX", true,
		    Vec2(100.0f, 60.0f), Vec3(a,350.0f, 0.0f));
		AddGameObject<ScrollSprite>(L"HANE_TX", true,
			Vec2(100.0f, 60.0f), Vec3(a - b, 350.0f, 0.0f));
		AddGameObject<ScrollSprite>(L"HANE_TX", true,
			Vec2(100.0f, 60.0f), Vec3(a + b, 350.0f, 0.0f));

	}

	void GameStage::OnCreate() {
		try {

			CreateGround();
			CreateObstacle();
			//ビューとライトの作成
			CreateViewLight();	
			CreatePlayer();
			CreateTraceSprite();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
