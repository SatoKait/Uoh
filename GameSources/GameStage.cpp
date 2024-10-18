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
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateGround() {
		Vec3 startPos =   Vec3(0.0f, 0.0f,  30.0f);
		Vec3 startScale = Vec3(5.0f, 1.0f, 100.0f);
		auto ptrGround = AddGameObject<Ground>(startPos,startScale);
	}

	void GameStage::CreateObstacle() {
		Vec3 startPos   =  Vec3(-2.0f,1.5f,0.0f);
		Vec3 startScale =  Vec3( 0.5f,3.0f,0.5f);
		auto ptrGround = AddGameObject<Pole>(startPos, startScale);
	}

	void GameStage::OnCreate() {
		try {
			CreateGround();
			CreateObstacle();
			//ビューとライトの作成
			CreateViewLight();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
