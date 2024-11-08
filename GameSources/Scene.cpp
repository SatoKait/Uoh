/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::CreateResourses() {
		// mediaファイルのパス取得
		auto path = App::GetApp()->GetDataDirWString();
		// テクスチャのリソース
		{
			auto texPath = path + L"Textures/";

			auto tex = texPath + L"Hane.png";
			App::GetApp()->RegisterTexture(L"HANE_TX", tex);

			tex = texPath + L"numbers.png";
			App::GetApp()->RegisterTexture(L"NUMBER_TX",tex);
			tex = texPath + L"Goal.png";
			App::GetApp()->RegisterTexture(L"GOAL_TX",tex);

			tex = texPath + L"sea2.png";
			App::GetApp()->RegisterTexture(L"SEA_TX", tex);
			tex = texPath + L"Red.png";
			App::GetApp()->RegisterTexture(L"RED_TX", tex);
		}
		// モデルのリソース
		{
			auto modelPath = path + L"Models/";

			// スタティックマルチモデルのリソース
			auto StaticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Pole.bmf");
			App::GetApp()->RegisterResource(L"POLE_MESH", StaticMultiModelMesh);
			StaticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Pole2.bmf");
			App::GetApp()->RegisterResource(L"POLE2_MESH", StaticMultiModelMesh);
			StaticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Poll2.bmf");
			App::GetApp()->RegisterResource(L"POLL2_MESH", StaticMultiModelMesh);

            // テクスチャ
			auto Modeltex = modelPath + L"FlyingFish.png";
			App::GetApp()->RegisterTexture(L"TOBIUO_TX",Modeltex);
		
			// スタティックモデルのリソース
			auto StaticModelMesh = MeshResource::CreateStaticModelMesh(modelPath, L"Buoy.bmf");
			App::GetApp()->RegisterResource(L"BUOY_MESH", StaticModelMesh);
			StaticModelMesh = MeshResource::CreateStaticModelMesh(modelPath, L"Poll.bmf");
			App::GetApp()->RegisterResource(L"POLL_MESH", StaticModelMesh);
			StaticModelMesh = MeshResource::CreateStaticModelMesh(modelPath, L"FlyingFish.bmf");
			App::GetApp()->RegisterResource(L"TOBIUO_MESH", StaticModelMesh);

		}
	}


	void Scene::OnCreate(){
		try {
			CreateResourses();
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToSelectStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToSelectStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<SelectStage>();
		}
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToGoalScene") {
			//ゴールシーンに移動
		    ResetActiveStage<GoalScene>();
		}

	}

}
//end basecross
