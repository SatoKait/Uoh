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
			App::GetApp()->RegisterTexture(L"NUMBER_TX", tex);
			tex = texPath + L"number.png";
			App::GetApp()->RegisterTexture(L"NUMBER2_TX", tex);
			tex = texPath + L"Score100.png";
			//Scoreテクスチャ
			tex = texPath + L"Score50.png";
			App::GetApp()->RegisterTexture(L"SCORE_TX", tex);
			tex = texPath + L"Score100.png";
			App::GetApp()->RegisterTexture(L"SCORE2_TX", tex);
			tex = texPath + L"Score1000.png";
			App::GetApp()->RegisterTexture(L"SCORE3_TX", tex);
			//Stageに使うテクスチャ
			tex = texPath + L"StageSlect.png";
			App::GetApp()->RegisterTexture(L"STAGESELECT_TX", tex);
			tex = texPath + L"GoalScene.png";
			App::GetApp()->RegisterTexture(L"GOALSCENE_TX", tex);
			tex = texPath + L"TitleLogo.png";
			App::GetApp()->RegisterTexture(L"LOGO_TX", tex);
			tex = texPath + L"TItleBack.png";
			App::GetApp()->RegisterTexture(L"TITLEBACK_TX", tex);
			tex = texPath + L"TitleText.png";
			App::GetApp()->RegisterTexture(L"TITLETEXT_TX", tex);
			tex = texPath + L"GameOver.png";
			App::GetApp()->RegisterTexture(L"GAMEOVER_TX", tex);
			tex = texPath + L"Time.png";
			App::GetApp()->RegisterTexture(L"TIME_TX", tex);
			tex = texPath + L"Goal.png";
			App::GetApp()->RegisterTexture(L"GOAL_TX", tex);
			tex = texPath + L"sea2.png";
			App::GetApp()->RegisterTexture(L"SEA_TX", tex);
			tex = texPath + L"Red.png";
			App::GetApp()->RegisterTexture(L"RED_TX", tex);
			tex = texPath + L"Blue.png";
			App::GetApp()->RegisterTexture(L"BLUE_TX", tex);
			tex = texPath + L"Green.png";
			App::GetApp()->RegisterTexture(L"GREEN_TX", tex);
			tex = texPath + L"Yellow.png";
			App::GetApp()->RegisterTexture(L"YELLOW_TX", tex);
			tex = texPath + L"Line.png";
			App::GetApp()->RegisterTexture(L"LINE_TX", tex);
			tex = texPath + L"Partition.png";
			App::GetApp()->RegisterTexture(L"PARTITION_TX", tex);
			tex = texPath + L"Combo.png";
			App::GetApp()->RegisterTexture(L"COMBO_TX", tex);
			tex = texPath + L"Bar.png";
			App::GetApp()->RegisterTexture(L"BAR_TX", tex);
			tex = texPath + L"counts.png";
			App::GetApp()->RegisterTexture(L"COUNT_TX", tex);
			tex = texPath + L"kakeru.png";
			App::GetApp()->RegisterTexture(L"KAKERU_TX", tex);
			tex = texPath + L"Gray.png";
			App::GetApp()->RegisterTexture(L"Haikei_TX", tex);
			tex = texPath + L"MiniMapPlayer.png";
			App::GetApp()->RegisterTexture(L"MiniMap_TX", tex);
			tex = texPath + L"White.png";
			App::GetApp()->RegisterTexture(L"MiniMapPlayer_TX", tex);
			tex = texPath + L"icon.png";
			App::GetApp()->RegisterTexture(L"ICON_TX", tex);
			tex = texPath + L"LastTime.png";
			App::GetApp()->RegisterTexture(L"LASTTIME_TX", tex);
			tex = texPath + L"wave.png";
			App::GetApp()->RegisterTexture(L"WAVE_TX", tex);

			//tex = texPath + L"Tri.png";
			//App::GetApp()->RegisterTexture(L"MiniMapPlayer_TX", tex);
		}
		// モデルのリソース
		{
			auto modelPath = path + L"Models/";

			// スタティックマルチモデルのリソース
			auto StaticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Pole.bmf");
			App::GetApp()->RegisterResource(L"POLE_MESH", StaticMultiModelMesh);
			StaticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Pole2.bmf");
			App::GetApp()->RegisterResource(L"POLL_MESH", StaticMultiModelMesh);
			StaticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Trophy.bmf");
			App::GetApp()->RegisterResource(L"TROPHY_MESH", StaticMultiModelMesh);

			// テクスチャ
			auto Modeltex = modelPath + L"FlyingFish.png";
			App::GetApp()->RegisterTexture(L"TOBIUO_TX", Modeltex);

			// スタティックモデルのリソース
			auto StaticModelMesh = MeshResource::CreateStaticModelMesh(modelPath, L"Buoy.bmf");
			App::GetApp()->RegisterResource(L"BUOY_MESH", StaticModelMesh);
			//StaticModelMesh = MeshResource::CreateStaticModelMesh(modelPath, L"Poll.bmf");
			//App::GetApp()->RegisterResource(L"POLL_MESH", StaticModelMesh);
			StaticModelMesh = MeshResource::CreateBoneModelMesh(modelPath, L"FlyingFish.bmf");
			App::GetApp()->RegisterResource(L"TOBIUO_MESH", StaticModelMesh);
			StaticModelMesh = MeshResource::CreateBoneModelMesh(modelPath, L"DeadFlyingFish.bmf");
			App::GetApp()->RegisterResource(L"DEADTOBIUO_MESH", StaticModelMesh);
			StaticModelMesh = MeshResource::CreateStaticModelMesh(modelPath, L"Poll3.bmf");
			App::GetApp()->RegisterResource(L"POLL3_MESH", StaticModelMesh);
			StaticModelMesh = MeshResource::CreateStaticModelMesh(modelPath, L"Poll.bmf");
			App::GetApp()->RegisterResource(L"POLL_1_MESH", StaticModelMesh);
			StaticModelMesh = MeshResource::CreateStaticModelMesh(modelPath, L"Poll2.bmf");
			App::GetApp()->RegisterResource(L"POLL_2_MESH", StaticModelMesh);
			StaticModelMesh = MeshResource::CreateStaticModelMesh(modelPath, L"Crown.bmf");
			App::GetApp()->RegisterResource(L"CROWN_MESH", StaticModelMesh);

			//StaticModelMesh = MeshResource::CreateStaticModelMesh(modelPath, L"Trophy.bmf");
			//App::GetApp()->RegisterResource(L"TROPHY_MESH", StaticModelMesh);

		}

		// モデルのリソース
		{
			auto SoundPath = path + L"Sounds/";

			wstring strSE = SoundPath + L"Wave.wav";
			App::GetApp()->RegisterWav(L"STAGEBGM", strSE);
			strSE = SoundPath + L"Kamome.wav";
			App::GetApp()->RegisterWav(L"KAMOMESE", strSE);
			strSE = SoundPath + L"GameCreal2.wav";
			App::GetApp()->RegisterWav(L"GAMECREAL2SE", strSE);
			strSE = SoundPath + L"BGM1.wav";
			App::GetApp()->RegisterWav(L"StageBGM1", strSE);
			strSE = SoundPath + L"BGM2.wav";
			App::GetApp()->RegisterWav(L"StageBGM2", strSE);
			strSE = SoundPath + L"EnterWater.wav";
			App::GetApp()->RegisterWav(L"EnterWaterSE", strSE);
			strSE = SoundPath + L"Damage.wav";
			App::GetApp()->RegisterWav(L"DamageSE", strSE);
			strSE = SoundPath + L"Float.wav";
			App::GetApp()->RegisterWav(L"FloatSE", strSE);
			strSE = SoundPath + L"Points.wav";
			App::GetApp()->RegisterWav(L"PointSE", strSE);
			strSE = SoundPath + L"GameOver.wav";
			App::GetApp()->RegisterWav(L"GAMEOVERSE", strSE);
			strSE = SoundPath + L"TimeUp.wav";
			App::GetApp()->RegisterWav(L"TIMEUPSE", strSE);
			strSE = SoundPath + L"Alarm.wav";
			App::GetApp()->RegisterWav(L"ALARMSE", strSE);
			strSE = SoundPath + L"Enter.wav";
			App::GetApp()->RegisterWav(L"ENTERSE", strSE);
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
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTiTleStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToTiTleStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<TitleStage>();
		}
		if (event->m_MsgStr == L"ToSelectStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<SelectStage>();
		}
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}		
		if (event->m_MsgStr == L"ToGameStage2") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage2>();
		}
		if (event->m_MsgStr == L"ToGameOverStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameOverStage>();
		}
		if (event->m_MsgStr == L"ToGoalScene") {
			//ゴールシーンに移動
		    ResetActiveStage<GoalScene>();
		}

	}

}
//end basecross
