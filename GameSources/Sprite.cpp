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
		m_StartPos(StartPos)
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
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_ClearKey);

	};
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

//end basecross
