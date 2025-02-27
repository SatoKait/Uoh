/*!
@file Map.cpp
@brief Mapクラスの実装
@authors YoshidaTomoki
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Map::OnCreate() {
		auto& app = App::GetApp();//アプリケーションの参照
		auto path = app->GetDataDirWString();//メディアの取得

		auto LevelsPath = path + L"Levels/";//Levelと繋ぐ
		auto mediaPath = app->GetDataDirWString(); // 「media」パスを文字列として取得する

		auto drawComp = AddComponent<PNTStaticInstanceDraw>(); // ←「Instance」と付いたドローコンポーネントを生成します
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetTextureResource(L"block");

		const int MAP_ROWS = 30;
		const int MAP_COLS = 20;
		int stageMap[MAP_ROWS][MAP_COLS];//縦横

		ifstream ifs(LevelsPath + L"map001.csv");//マップを読み取る
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
					float x = -5.0f + c;
					float z = +25.0f + (-r) - 0.5f;
					//// インスタンス用の行列を作成する
					Vec3 startPos(x, 0.0f, z); // 基準となるオフセット座標//移動座標
					Vec3 startScl(1.0f);

					auto block = GetStage()->AddGameObject<Block>();
					auto blockTransComp = block->GetComponent<Transform>();
					blockTransComp->SetPosition(startPos);
					blockTransComp->SetScale(startScl);
					auto blockInstance = block->GetComponent<PNTStaticInstanceDraw>();
					Mat4x4 matrix;
					matrix.translation(Vec3(x, 0.0f, z));
					blockInstance->AddMatrix(matrix);
					
					break;
				}
			}
		}
	}
}
