/*!
@file Deployment.cpp
@brief オブジェクト配置実体
@authors YoshidaTomoki
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Deployment::OnCreate() {
		auto& app = App::GetApp();//アプリケーションの参照
		auto path = app->GetDataDirWString();//メディアの取得

		auto LevelsPath = path + L"Levels/";//Levelと繋ぐ
		auto mediaPath = app->GetDataDirWString(); // 「media」パスを文字列として取得する

		auto drawComp = AddComponent<PNTStaticInstanceDraw>(); // ←「Instance」と付いたドローコンポーネントを生成します
		const int MAP_ROWS = 110;
		const int MAP_COLS = 100;
		int stageMap[MAP_ROWS][MAP_COLS];//縦横

		ifstream ifs(LevelsPath + L"Object.csv");//マップを読み取る
		if (ifs)
		{
			int c = 0; // マップデータ参照用

			string line;
			while (getline(ifs, line)) // ファイルから1行読み取る
			{
				string data;
				istringstream ss(line); // 読み取った内容をストリームに変換する
				while (getline(ss, data, ',')) // そのストリームからカンマ区切りでデータを読み込む
				{
					int cellData = atoi(data.c_str()); // 読み取ったデータをint型に変換する
					stageMap[0][c++] = cellData; // マップデータにCSVのデータをコピーする
				}
			}
		}

		// ブロック（二次元配列の「1」の位置にブロックを置く）
		for (int r = 0; r < MAP_ROWS; r++)
		{
			for (int c = 0; c < MAP_COLS; c++)
			{

				switch (stageMap[r][c])
				{

				case 1:
					m_Side = -50.0 + c;//x
					m_Warp =  55.0f + (-r);//z
					float scl = 1.0f;
					//// インスタンス用の行列を作成する
					Vec3 m_stratPos(m_Side, 0.0f, m_Warp); // 基準となるオフセット座標//移動座標
					auto pole = GetStage()->AddGameObject<Buoy>();
					auto poleTransComp = pole->GetComponent<Transform>();
					poleTransComp->SetPosition(m_stratPos);
					auto blockInstance = pole->GetComponent<PNTStaticInstanceDraw>();
					Mat4x4 matrix, mtxScale;
					//mtxScale.scale(Vec3(2.0f, 2.0f, 2.0f));
					matrix.translation(Vec3(m_Side, 0.5f, m_Warp));

					blockInstance->AddMatrix(matrix);

					break;
				}
			}
		}
	}

}

namespace basecross {

	void Deployment2::OnCreate() {
		auto& app = App::GetApp();//アプリケーションの参照
		auto path = app->GetDataDirWString();//メディアの取得

		auto LevelsPath = path + L"Levels/";//Levelと繋ぐ
		auto mediaPath = app->GetDataDirWString(); // 「media」パスを文字列として取得する

		auto drawComp = AddComponent<PNTStaticInstanceDraw>(); // ←「Instance」と付いたドローコンポーネントを生成します
		const int MAP_ROWS = 100;
		const int MAP_COLS = 100;
		int stageMap[MAP_ROWS][MAP_COLS];//縦横

		ifstream ifs(LevelsPath + L"Stage2.csv");//マップを読み取る
		if (ifs)
		{
			int c = 0; // マップデータ参照用

			string line;
			while (getline(ifs, line)) // ファイルから1行読み取る
			{
				string data;
				istringstream ss(line); // 読み取った内容をストリームに変換する
				while (getline(ss, data, ',')) // そのストリームからカンマ区切りでデータを読み込む
				{
					int cellData = atoi(data.c_str()); // 読み取ったデータをint型に変換する
					stageMap[0][c++] = cellData; // マップデータにCSVのデータをコピーする
				}
			}
		}

		// ブロック（二次元配列の「1」の位置にブロックを置く）
		for (int r = 0; r < MAP_ROWS; r++)
		{
			for (int c = 0; c < MAP_COLS; c++)
			{

				switch (stageMap[r][c])
				{

				case 1:
					m_Side = -50.0 + c;//x
					m_Warp = 50.0f + (-r);//z
					float scl = 1.0f;
					//// インスタンス用の行列を作成する
					Vec3 m_stratPos(m_Side, 0.0f, m_Warp); // 基準となるオフセット座標//移動座標
					auto pole = GetStage()->AddGameObject<Buoy>();
					auto poleTransComp = pole->GetComponent<Transform>();
					poleTransComp->SetPosition(m_stratPos);
					auto blockInstance = pole->GetComponent<PNTStaticInstanceDraw>();
					Mat4x4 matrix, mtxScale;
					//mtxScale.scale(Vec3(2.0f, 2.0f, 2.0f));
					matrix.translation(Vec3(m_Side, 0.5f, m_Warp));

					blockInstance->AddMatrix(matrix);

					break;
				}
			}
		}
	}
}


