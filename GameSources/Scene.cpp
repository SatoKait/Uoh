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

			auto texHane = texPath + L"Hane.png";
			App::GetApp()->RegisterTexture(L"HANE_TX", texHane);

			auto texNumber = texPath + L"numbers.png";
			App::GetApp()->RegisterTexture(L"NUMBER_TX",texNumber);

		}
		// モデルのリソース
		{
			auto modelPath = path + L"Models/";

			// スタティックモデルのリソース
			auto StaticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"NewTobiuo.bmf");
			App::GetApp()->RegisterResource(L"TOBIUO_MESH", StaticMultiModelMesh);
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
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
	}

}
//end basecross
