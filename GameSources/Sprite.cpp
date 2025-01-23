/*!
@file Sprite.cpp
@brief スプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	TimeSprite::TimeSprite(
		shared_ptr<Stage>& StagePtr,	// ステージ
		UINT NumberOfDigits,			// 桁数
		const wstring& TextureKey,
		const Vec2& StartScale,			// 大きさ
		const Vec3& StartPos) :

		GameObject(StagePtr),
		m_NumberOfDigits(NumberOfDigits),
		m_TextureKey(TextureKey),
		m_StartScale(StartScale),
		m_StartPos(StartPos),

		m_Time(0.0f)

	{}
	TimeSprite::~TimeSprite() {};

	void TimeSprite::OnCreate()
	{
		int NumberImageX = 512;
	}

	void TimeSprite::OnUpdate()
	{

	}


	GoalSprite::GoalSprite(
		shared_ptr<Stage>& StagePtr,
		const wstring& TextureKey,
		const Vec2& StartScale,
		const Vec3& StartPos
	) :
		GameObject(StagePtr),
		m_textureKey(TextureKey),
		m_startScale(StartScale),
		m_startPos(StartPos),
		m_Trace(true)
	{}
	GoalSprite::~GoalSprite() {};

	void GoalSprite::OnCreate()
	{
		float helfSize = 0.5f;
		Col4 color = Col4(1.0f);

		const float GoalImageX = 256;
		const float GoalImageY = 128;
		float fontH = 1.0f;
		float fontW = 1.0f;
		float fontCount = 1;

		vector<VertexPositionColorTexture> vertices = {
			{ Vec3(-helfSize, helfSize, 0),  color, Vec2(0.0f  ,0.0f)},
			{ Vec3(helfSize, helfSize, 0),   color, Vec2(fontW  ,0.0f)},
			{ Vec3(-helfSize, -helfSize, 0), color, Vec2(0.0f  ,fontH)},
			{ Vec3(helfSize, -helfSize, 0),  color, Vec2(fontW  ,fontH)},
		};

		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);//透過処理
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_startPos);
		//頂点とインデックスを指定してスプライト作成
		m_ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		m_ptrDraw->SetTextureResource(m_textureKey);



	}

	//void GoalSprite::OnUpdate()
	//{
	//	auto stage = GetStage();
	//	auto ptrplayer=  stage->GetSharedGameObject<Player>(L"Player");
	//  auto ptrplayerflag = ptrplayer->m_Goal;
	//	ptrplayerflag = true;

	//	if (ptrplayerflag)
	//	{
	//	}
	//}
}

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	                               Stageスプライト
	//--------------------------------------------------------------------------------------
	StageSprite::StageSprite(const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_ClearKey(ClearKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_color(1.0f)
	{}

	StageSprite::~StageSprite() {}

	void StageSprite::OnCreate() {
		float HelfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f),      Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f),   Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f),  Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		m_Trace = true;
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_ClearKey);

	};


	void StageSprite::SetColor(Col4 color) {
		m_color = color;
		PtrDraw->SetDiffuse(color);
	}
	Col4 StageSprite::GetColor() {
		return m_color;
	}
}

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	                               GameScoreSpriteスプライト
	//--------------------------------------------------------------------------------------
	GameScoreSprite::GameScoreSprite(const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_ClearKey(ClearKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_NewPos(0.0f),
		m_maxPos(1.0f),
		m_minPos(-0.1),
		m_yPosSpeed(0.8f),
		m_highly(0.15f),
		m_time(0.0f),
		m_isPosMax(false),
		m_isPosMin(true),
		m_isDraw(true),
		m_istimeFlag(false),
		m_nowpos(0.0f),
		m_speed(1.0f),
		m_elapsedTime(App::GetApp()->GetElapsedTime())

	{}

	GameScoreSprite::~GameScoreSprite() {}

	void GameScoreSprite::OnCreate() {
		float HelfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f),      Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f),   Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f),  Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		m_Trace = true;
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
			SetAlphaActive(m_Trace);
			m_ptrTrans = GetComponent<Transform>();
			m_ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
			m_ptrTrans->SetRotation(0, 0, 0);
			m_ptrTrans->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
			//頂点とインデックスを指定してスプライト作成
			m_ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
			m_ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			m_ptrDraw->SetTextureResource(m_ClearKey);
	}
	void GameScoreSprite::OnUpdate()
	{

		m_nowpos = m_ptrTrans->GetPosition();

		if (!m_isPosMax) {
			m_NewPos += m_yPosSpeed * m_elapsedTime;
			m_nowpos.y += m_highly + m_NewPos;
		}

		if (m_maxPos < m_NewPos && !m_isPosMax) {
			m_isPosMax = true;
			m_isPosMin = false;
			m_istimeFlag = true;
		}
		m_ptrTrans->SetPosition(m_nowpos);

		if (m_istimeFlag)
		{
			m_time += m_elapsedTime * m_speed;
		}

		if (m_time >= 0.5f)
		{		
			m_istimeFlag = false;
			m_time = 0.0f;
			GetStage()->RemoveGameObject<GameScoreSprite>(GetThis<GameScoreSprite>());
		}
	};
}

namespace basecross {

	//--------------------------------------------------------------------------------------
	///明減文字
	//--------------------------------------------------------------------------------------
	Flickering::Flickering(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0.0f)
	{}
	Flickering::~Flickering() {}

	void Flickering::OnCreate() {
		float HelfSize = 0.5f;
		//頂点配列
		vector<VertexPositionColorTexture> vertex = {
		{ VertexPositionColorTexture(Vec3(-HelfSize,  HelfSize, 0),  Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 0.0f)) },
		{ VertexPositionColorTexture(Vec3(HelfSize,  HelfSize, 0),  Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
		{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0),  Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
		{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0),  Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		//インデックス配列
		m_Trace = true;
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//スプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertex, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
	}


	void Flickering::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime * 3.0f;
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0.0f;
		}

		auto PtrDraw = GetComponent<PCTSpriteDraw>();
		Col4 col(1.0, 1.0, 1.0, 1.0);
		col.w = sin(m_TotalTime);
		PtrDraw->SetDiffuse(col);
	};
}

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	                               Comboスプライト
	//--------------------------------------------------------------------------------------
	ComboSprite::ComboSprite(const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_ClearKey(ClearKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}

	ComboSprite::~ComboSprite() {}

	void ComboSprite::OnCreate() {
		float HelfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f),      Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f),   Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f),  Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		m_Trace = true;
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_ClearKey);

	};
}

namespace basecross {
	//初期化
	void ComboSpriteNumber::OnCreate()
	{
		auto stage = GetStage();
		auto ptrPlayer = stage->GetSharedGameObject<Player>(L"Player");
		auto count = ptrPlayer->m_CircleCount;
		// ポリゴンの自作
		Col4 color(1, 1, 1, 1); // ポリゴンの色
		const float w = 50.0f; // ポリゴンの幅
		const float h = 100.0f; // ポリゴンの高さ//ここでポリゴンの大きさが変わるため画像をデカくできる
		const float numberW = 50.0f / 512.0f;//nember×１
		const float numberH = 100.0f / 128.0f;
		int number = count;
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
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 0.0f);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		m_ptrDraw = AddComponent<PCTSpriteDraw>(m_vertices, indices); // スプライト用のドローコンポーネント//メンバ変数にするためautoを消した
		m_ptrDraw->SetTextureResource(L"NUMBER_TX");
		m_ptrDraw->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		m_ptrDraw->SetDiffuse(Col4(1, 1, 1, 1)); // ポリゴンを色を設定する

		// アルファブレンド(透過処理)を有効にする
		//SetAlphaActive(m_Trace);
		////頂点とインデックスを指定してスプライト作成
		//auto PtrDraw = AddComponent<PCTSpriteDraw>(m_vertices, indices);
		//PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		//PtrDraw->SetTextureResource(m_ClearKey);

	}

	void ComboSpriteNumber::OnUpdate()
	{
		auto stage = GetStage();
		auto ptrPlayer = stage->GetSharedGameObject<Player>(L"Player");
		auto count = ptrPlayer->m_CircleCount;

		UpdateValue(count);
	}

	void ComboSpriteNumber::UpdateValue(int value)//切り出せるようにint valueしている
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

namespace basecross {
	//初期化
	void RankSpriteNumber::OnCreate()
	{
		auto stage = GetStage();
		auto ptrPlayer = stage->GetSharedGameObject<Player>(L"Player");
		auto count = ptrPlayer->m_CircleCount;
		// ポリゴンの自作
		Col4 color(1, 1, 1, 1); // ポリゴンの色
		const float w = 50.0f; // ポリゴンの幅
		const float h = 100.0f; // ポリゴンの高さ//ここでポリゴンの大きさが変わるため画像をデカくできる
		const float numberW = 50.0f / 512.0f;//nember×１
		const float numberH = 100.0f / 128.0f;
		int number = count;
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
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 0.0f);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		m_ptrDraw = AddComponent<PCTSpriteDraw>(m_vertices, indices); // スプライト用のドローコンポーネント//メンバ変数にするためautoを消した
		m_ptrDraw->SetTextureResource(L"NUMBER_TX");
		m_ptrDraw->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		m_ptrDraw->SetDiffuse(Col4(m_color)); // ポリゴンを色を設定する

		// アルファブレンド(透過処理)を有効にする
		//SetAlphaActive(m_Trace);
		////頂点とインデックスを指定してスプライト作成
		//auto PtrDraw = AddComponent<PCTSpriteDraw>(m_vertices, indices);
		//PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		//PtrDraw->SetTextureResource(m_ClearKey);

	}

	void RankSpriteNumber::OnUpdate()
	{
		auto stage = GetStage();
		auto ptrPlayer = stage->GetSharedGameObject<Player>(L"Player");
		auto count = ptrPlayer->m_CircleCount;

		UpdateValue(count);
	}

	void RankSpriteNumber::UpdateValue(int value)//切り出せるようにint valueしている
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

	void RankSpriteNumber::SetColor(Col4 color) {
		m_color = color;
		m_ptrDraw->SetDiffuse(color);
	}
	Col4 RankSpriteNumber::GetColor() {
		return m_color;
	}
}

namespace basecross {
	//初期化
	void GaugeSpriteNumber::OnCreate()
	{
		auto stage = GetStage();
		auto ptrGauge = stage->GetSharedGameObject<GaugeScore>(L"Gauge");
		auto count = ptrGauge->Count;
		// ポリゴンの自作
		Col4 color(1, 1, 1, 1); // ポリゴンの色
		const float w = 50.0f; // ポリゴンの幅
		const float h = 100.0f; // ポリゴンの高さ//ここでポリゴンの大きさが変わるため画像をデカくできる
		const float numberW = 50.0f / 512.0f;//nember×１
		const float numberH = 100.0f / 128.0f;
		int number = count;
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
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 0.0f);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		m_ptrDraw = AddComponent<PCTSpriteDraw>(m_vertices, indices); // スプライト用のドローコンポーネント//メンバ変数にするためautoを消した
		m_ptrDraw->SetTextureResource(L"COUNT_TX");
		m_ptrDraw->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		m_ptrDraw->SetDiffuse(Col4(1, 1, 1, 1)); // ポリゴンを色を設定する

		// アルファブレンド(透過処理)を有効にする
		//SetAlphaActive(m_Trace);
		////頂点とインデックスを指定してスプライト作成
		//auto PtrDraw = AddComponent<PCTSpriteDraw>(m_vertices, indices);
		//PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		//PtrDraw->SetTextureResource(m_ClearKey);

	}

	void GaugeSpriteNumber::OnUpdate()
	{
		auto stage = GetStage();
		auto ptrGauge = stage->GetSharedGameObject<GaugeScore>(L"Gauge");
		auto count = ptrGauge->Count;

		UpdateValue(count);
	}

	void GaugeSpriteNumber::UpdateValue(int value)//切り出せるようにint valueしている
	{
		//ポリゴンの頂点データを更新する(valueの数値に合わせた「画像」を切り抜く)
		const float numberW = 51.0f / 512.0f;
		int number = value;

		m_vertices[0].textureCoordinate.x = numberW * number;//0番目の頂点の物になる//.のあとに入れるもので色々変えることができる
		m_vertices[1].textureCoordinate.x = numberW * (number + 1);//1番目の頂点の物になる//.のあとに入れるもので色々変えることができる
		m_vertices[2].textureCoordinate.x = numberW * number;//2番目の頂点の物になる//.のあとに入れるもので色々変えることができる
		m_vertices[3].textureCoordinate.x = numberW * (number + 1);//3番目の頂点の物になる//.のあとに入れるもので色々変えることができる

		//更新されたデータでポリゴンを作り直す
		m_ptrDraw->UpdateVertices(m_vertices);
	}
}

namespace basecross {
	MiniMapSprite::MiniMapSprite(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size, Vec3 pos, Vec3 rot, Col4 color, int layer) :
		GameObject(stagePtr),
		m_textureName(textureName),
		m_size(size),
		m_pos(pos),
		m_color(color),
		m_layer(layer)
	{

	}

	MiniMapSprite::~MiniMapSprite()
	{
	}

	void MiniMapSprite::OnCreate()
	{
		// ポリゴンの自作
		Col4 color(1, 1, 1, 1); // ポリゴンの色
		const float w = 200.0f; // ポリゴンの幅
		const float h = 100.0f; // ポリゴンの高さ
		vector<VertexPositionColorTexture> m_vertices = { // 頂点データ
			//             座標                          ,頂点色,     UV座標
			{Vec3(-m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(0.0f, 0.0f)}, // 0
			{Vec3(+m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(1.0f, 0.0f)}, // 1
			{Vec3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(0.0f, 1.0f)}, // 2
			{Vec3(+m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(1.0f, 1.0f)}, // 3
		};

		vector<uint16_t> m_indices = { // 頂点インデックス（頂点のつなげ順）
			0, 1, 2, // ←これで一つのポリゴン(三角形)
			2, 1, 3  // ←こっちも
		};

		m_drawComp = AddComponent<PCTSpriteDraw>(m_vertices, m_indices); // スプライト用のドローコンポーネント
		m_drawComp->SetTextureResource(m_textureName);//テクスチャの名前指定
		m_drawComp->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		m_drawComp->SetDiffuse(Col4(1, 1, 1, 1.0f)); // ポリゴンを色を設定する

		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_pos);
		trans->SetRotation(m_rot);


		// アルファブレンド(透過処理)を有効にする
		SetAlphaActive(true); // true:透過を有効、false:透過を無効

		SetDrawLayer(m_layer);

	}

	void MiniMapSprite::OnUpdate()
	{

	}

	//カラーの数値を変更する
	void MiniMapSprite::SetColor(Col4 color)
	{
		m_color = color;
		m_drawComp->SetDiffuse(m_color);
	}
	//カラーの数値を取得させる
	Col4 MiniMapSprite::GetColor()
	{
		return m_color;
	}

	//自分自身を消去する
	void MiniMapSprite::MyDestroy()
	{
		GetStage()->RemoveGameObject<MiniMapSprite>(GetThis<MiniMapSprite>());
	}
}

namespace basecross {

	GateSprite::GateSprite(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size, Vec3 pos, Vec3 rot, Col4 color, int layer) :
		MiniMapSprite(stagePtr, textureName, size, pos, rot, color, layer)
		//m_parent(parent)
	{
	}

	GateSprite::~GateSprite()
	{
	}

	void GateSprite::OnUpdate()
	{
	}
}

namespace basecross {
		MiniMapMoveGate::MiniMapMoveGate(shared_ptr<Stage>& stagePtr, weak_ptr<Gate> parentObj, wstring textureName, Vec2 size, int layer, Vec3 pos, Vec3 rot) :
			GameObject(stagePtr),
			m_textureName(textureName),
			m_parentObj(parentObj),
			m_size(size),
			m_pos(pos),
			m_layer(layer)
		{

		}

		MiniMapMoveGate::~MiniMapMoveGate()
		{
		}

		void MiniMapMoveGate::OnCreate()
		{
			// ポリゴンの自作
			m_color = Col4(1, 1, 1, 1); // ポリゴンの色
			const float w = 200.0f; // ポリゴンの幅
			const float h = 100.0f; // ポリゴンの高さ
			vector<VertexPositionColorTexture> m_vertices = { // 頂点データ
				//             座標                          ,頂点色,     UV座標
				{Vec3(-m_size.x * 0.5f, +m_size.y * 0.5f, 0), m_color, Vec2(0.0f, 0.0f)}, // 0
				{Vec3(+m_size.x * 0.5f, +m_size.y * 0.5f, 0), m_color, Vec2(1.0f, 0.0f)}, // 1
				{Vec3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0), m_color, Vec2(0.0f, 1.0f)}, // 2
				{Vec3(+m_size.x * 0.5f, -m_size.y * 0.5f, 0), m_color, Vec2(1.0f, 1.0f)}, // 3
			};

			vector<uint16_t> m_indices = { // 頂点インデックス（頂点のつなげ順）
				0, 1, 2, // ←これで一つのポリゴン(三角形)
				2, 1, 3  // ←こっちも
			};

			auto drawComp = AddComponent<PCTSpriteDraw>(m_vertices, m_indices); // スプライト用のドローコンポーネント
			drawComp->SetTextureResource(m_textureName);//テクスチャの名前指定
			drawComp->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
			drawComp->SetDiffuse(Col4(1, 1, 1, 1.0f)); // ポリゴンを色を設定する

			auto trans = GetComponent<Transform>();
			trans->SetPosition(m_pos);
			trans->SetRotation(m_rot);


			// アルファブレンド(透過処理)を有効にする
			SetAlphaActive(true); // true:透過を有効、false:透過を無効

			SetDrawLayer(m_layer);

		}

		void MiniMapMoveGate::OnUpdate()
		{
			//元となるオブジェクトが消えた場合、自分も消える
			if (!m_parentObj.lock())
			{
				GetStage()->RemoveGameObject<MiniMapMoveGate>(GetThis<MiniMapMoveGate>());
			}
		}

}//end basecross

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	                               Spriteスプライト
	//--------------------------------------------------------------------------------------
	JumpSprite::JumpSprite(const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_ClearKey(ClearKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_color(1.0f),
		m_MoveFlag(false),
		m_DownMoveFlag(false),
		m_UpFlag(true),
		m_DownFlag(false)
	{}

	JumpSprite::~JumpSprite() {}

	void JumpSprite::OnCreate() {
		float HelfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f),      Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f),   Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f),  Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		m_Trace = true;
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_ClearKey);

	};

	void JumpSprite::OnUpdate() {
		auto ptrTrans = GetComponent<Transform>();
		Vec3 ptrPosition = ptrTrans->GetPosition();
		auto deltaTime = 0.0f;
		auto delta = App::GetApp()->GetElapsedTime();
		deltaTime += delta;
		auto m_Speed = 10.0f;
		if (m_MoveFlag)
		{
			if(ptrPosition.y <= 100.0f && m_UpFlag == true)
			{
				ptrPosition.y += 10.0f * deltaTime * m_Speed;
			}	
			if (ptrPosition.y >= 100.0f)
			{	
				m_UpFlag = false;
				m_DownFlag = true;
			}
			if (m_DownFlag == true)
			{
				ptrPosition.y -= 10.0f * deltaTime * m_Speed;
			}	
			if (ptrPosition.y <= 0.0f)
			{
				m_DownFlag = false;
				m_UpFlag = true;
			}

			ptrTrans->SetPosition(ptrPosition.x, ptrPosition.y, 0.0f);
		}
		if (m_DownMoveFlag)
		{
			if (m_DownFlag == false)
			{
				ptrPosition.y -= 10.0f * deltaTime * m_Speed;
			}
			if (ptrPosition.y <= -100.0f)
			{
				m_DownFlag = true;
				m_UpFlag = false;
			}

			ptrTrans->SetPosition(ptrPosition.x, ptrPosition.y, 0.0f);
		}


	}

	void JumpSprite::SetColor(Col4 color) {
		m_color = color;
		PtrDraw->SetDiffuse(color);
	}
	Col4 JumpSprite::GetColor() {
		return m_color;
	}
}
