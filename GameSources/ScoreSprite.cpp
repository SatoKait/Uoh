/*!
@file ScoreSprite.cpp
@brief Scoreスプライトの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void ScoreSprite::OnCreate()
	{
		// ポリゴンの自作
		Col4 color(1, 1, 1, 1); // ポリゴンの色
		const float w = 50.0f; // ポリゴンの幅
		const float h = 100.0f; // ポリゴンの高さ//ここでポリゴンの大きさが変わるため画像をデカくできる
		const float numberW = 50.0f / 512.0f;//nember×１
		const float numberH = 100.0f / 128.0f;
		int number = 8;
		m_vertices = { // 頂点データ//sprite.hに持って行った
			//             座標           ,頂点色,        UV座標 
			{Vec3(-w * 0.0f, +h * 0.0f, 0.0), color, Vec2(numberW * number,          0.0f)}, // 0//512=1.0fになっている256で0.5ｆ
			{Vec3(+w * 1.0f, +h * 0.0f, 0.0), color, Vec2(numberW * (number + 1),    0.0f)}, // 1
			{Vec3(-w * 0.0f, -h * 1.0f, 0.0), color, Vec2(numberW * number,       numberH)}, // 2
			{Vec3(+w * 1.0f, -h * 1.0f, 0.0), color, Vec2(numberW * (number + 1), numberH)}, // 3
		};

		vector<uint16_t> indices = { // 頂点インデックス（頂点のつなげ順）
			0, 1, 2,
			2, 1, 3
		};

		SetAlphaActive(true);

		m_ptrDraw = AddComponent<PCTSpriteDraw>(m_vertices, indices); // スプライト用のドローコンポーネント//メンバ変数にするためautoを消した
		m_ptrDraw->SetTextureResource(L"NUMBER_TX");
		m_ptrDraw->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		m_ptrDraw->SetDiffuse(Col4(1, 1, 1, 1)); // ポリゴンを色を設定する

		// アルファブレンド(透過処理)を有効にする
		SetAlphaActive(true); // true:透過を有効、false:透過を無効
	}

	void ScoreSprite::OnUpdate()
	{}

	void ScoreSprite::UpdateValue(int value)//切り出せるようにint valueしている
	{
		//ポリゴンの頂点データを更新する(valueの数値に合わせた「画像」を切り抜く)
		const float numberW = 50.0f / 512.0f;
		int number = value;

		m_vertices[0].textureCoordinate.x = numberW * number;//0番目の頂点の物になる//.のあとに入れるもので色々変えることができる
		m_vertices[1].textureCoordinate.x = numberW * (number + 1);//1番目の頂点の物になる//.のあとに入れるもので色々変えることができる
		m_vertices[2].textureCoordinate.x = numberW * number;//2番目の頂点の物になる//.のあとに入れるもので色々変えることができる
		m_vertices[3].textureCoordinate.x = numberW * (number + 1);//3番目の頂点の物になる//.のあとに入れるもので色々変えることができる

		//更新されたデータでポリゴンを作り直す
		m_ptrDraw->UpdateVertices(m_vertices);
	}
}
//end basecross
