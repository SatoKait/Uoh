/*!
@file Block.cpp
@brief Blockクラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Block::OnCreate() {
		auto& app = App::GetApp();//アプリケーションの参照

		auto path = app->GetDataDirWString();//メディアの取得
		auto LevelsPath = path + L"Levels/";//Levelと繋ぐ
		auto mediaPath = app->GetDataDirWString(); // 「media」パスを文字列として取得する
		auto texturePath = mediaPath + L"Textures/"; // 「Textures/」フォルダのパスを連結する
		app->RegisterTexture(L"block", texturePath + L"block.jpg");


		auto drawComp = AddComponent<PNTStaticInstanceDraw>(); //Instanceと付いたドローコンポーネントを生成します
		drawComp->SetMeshResource(m_meshResName);
		drawComp->SetTextureResource(L"block");
		drawComp->SetOwnShadowActive(true);
		
		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(m_meshResName);


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
					float x = -25.0f + c + 0.5f;
					float z = +25.0f + (-r) - 0.5f;

					// インスタンス用の行列を作成する
					Mat4x4 matrix;
					matrix.translation(Vec3(x, 1.0f, z));
					drawComp->AddMatrix(matrix); // ブロックを表示したい数だけ行列を追加します。この行列が示す位置・向き・大きさで指定したメッシュが描画されます

					break;
				}
			}
		}
	}
}
