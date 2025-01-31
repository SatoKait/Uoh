/*!
@file Score.cpp
@brief スコアの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Score::OnCreate()
	{
		const int numPlaces = 5;
		m_numberSprites.reserve(numPlaces);
		int place = 10000;

		for (int i = 0; i < numPlaces; i++)
		{
			auto stage = GetStage();
			number = stage->AddGameObject<ScoreSprite>();
			m_numberTrans = number->GetComponent<Transform>();
			m_numberTrans->SetPosition(300 * 0.5f - 50.0f * (numPlaces - i), 800 * 0.5f, 0.0f);		
			//m_numberTrans->SetPosition(50.0f * (numPlaces - i - 3.4f), 800 * 0.5f, 0.0f);
			number->UpdateValue(m_score / place % 10);
			place /= 10;
			m_numberSprites.push_back(number);
		}
	}

	void Score::OnDraw()
	{
		//200 * 0.5f - 50.0f * (numPlaces - i), -50 * 0.5f, 0.0f
		//for (const auto& number : m_numberSprites)
		//{
		//	number->OnDraw();
		//}
	}

	void Score::OnUpdate()
	{	auto stage = GetStage();
	    m_score = App::GetApp()->GetScene<Scene>()->GetPoint();//更新で最新の数字を見る
		int place = 10000;	
		for (int i = 0; i < m_numberSprites.size(); ++i) {
			
			int digit = (m_score / place) % 10;// 現在の桁の数字を計算
			m_numberSprites[i]->UpdateValue(digit);// スプライトの数字を更新
			place /= 10;// 次の桁に移動
		}
	}
}

namespace basecross {

	//初期化
	void StageScore::OnCreate()
	{
		//m_Trans = GetComponent<Transform>();
		//m_Trans->SetPosition(m_Position);

		const int numPlaces = 5;
		m_numberSprites.reserve(numPlaces);
		int place = 10000;

		for (int i = 0; i < numPlaces; i++)
		{
			auto stage = GetStage();
			number = stage->AddGameObject<ScoreSprite>();
			m_numberTrans = number->GetComponent<Transform>();
			m_numberTrans->SetPosition(200 * 0.5f - 50.0f * (numPlaces - i), -50 * 0.5f, 0.0f);
			number->UpdateValue(m_score / place % 1);
			place /= 10;
			m_numberSprites.push_back(number);
		}
	}

	void StageScore::OnUpdate()
	{
		auto stage = GetStage();
		m_score = App::GetApp()->GetScene<Scene>()->GetPoint();//更新で最新の数字を見る
		int place = 10000;
		for (int i = 0; i < m_numberSprites.size(); ++i) {
			int digit = (m_score / place) % 10;// 現在の桁の数字を計算
			m_numberSprites[i]->UpdateValue(digit);// スプライトの数字を更新
			place /= 10;// 次の桁に移動
		}
	}
}

namespace basecross {

	void GaugeScore::OnCreate() {

		m_ptrTrans = GetComponent<Transform>();

		//色の設定
		Col4 color(1, 1, 1, 1); //ポリゴンの色
		float widthSize = m_Hp_now; //ポリゴンの幅
		float helfSize = 20.0f; //ポリゴンの高さ


		m_BackupVertices = {
			{VertexPositionColorTexture(Vec3(0, 0, 0), color, Vec2(0, 0))},
			{VertexPositionColorTexture(Vec3(widthSize, 0, 0), color, Vec2(1, 0))},
			{VertexPositionColorTexture(Vec3(0, helfSize, 0), color, Vec2(0, 1))},
			{VertexPositionColorTexture(Vec3(widthSize, helfSize, 0), color, Vec2(1, 1))},
		};

		//インデックス配列
		vector<uint16_t> indices = { 2, 1, 0, 3, 1, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_HpKey);
	}

	void GaugeScore::OnUpdate() {

		auto stage = GetStage();

		m_Hp_now = App::GetApp()->GetScene<Scene>()->GetScore() * 1.0f;
		if (m_Hp_now <= 1000)
		{
			m_ptrTrans->SetScale(1.0f, m_Hp_now / m_Max_hp * 1.0f, 1.0f);
		}
		if (m_Hp_now >= 1000)
		{
			Count++;
			m_Hp_now = App::GetApp()->GetScene<Scene>()->SetScore(m_Reset);
			//auto Kakeru = stage->AddGameObject<StageSprite>(L"KAKERU_TX", true,
			//	Vec2(64.0f, 64.0f), Vec2(-460.0f, -360.0f));
      
			//GetStage()->GetSharedGameObject<StageSprite>(L"Kakeru");
			auto Kakeru = GetStage()->GetSharedGameObject<StageSprite>(L"Kakeru");
			Kakeru->SetDrawLayer(3);
			//GetStage()->SetSharedGameObject(L"KAKERU", Kakeru);

		}
	}
}

namespace basecross {

	void GaugeScoreEnemy::OnCreate() {

		m_ptrTrans = GetComponent<Transform>();

		//色の設定
		Col4 color(1, 1, 1, 1); //ポリゴンの色
		float widthSize = m_Hp_now; //ポリゴンの幅
		float helfSize = 20.0f; //ポリゴンの高さ


		m_BackupVertices = {
			{VertexPositionColorTexture(Vec3(0, 0, 0), color, Vec2(0, 0))},
			{VertexPositionColorTexture(Vec3(widthSize, 0, 0), color, Vec2(1, 0))},
			{VertexPositionColorTexture(Vec3(0, helfSize, 0), color, Vec2(0, 1))},
			{VertexPositionColorTexture(Vec3(widthSize, helfSize, 0), color, Vec2(1, 1))},
		};

		//インデックス配列
		vector<uint16_t> indices = { 2, 1, 0, 3, 1, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_HpKey);
	}

	void GaugeScoreEnemy::OnUpdate() {

		auto stage = GetStage();

		m_Hp_now = App::GetApp()->GetScene<Scene>()->GetScore2() * 1.0f;
		if (m_Hp_now <= 1000)
		{
			m_ptrTrans->SetScale(1.0f, m_Hp_now / m_Max_hp * 1.0f, 1.0f);
		}
		if (m_Hp_now >= 1000)
		{
			Count++;
			m_Hp_now = App::GetApp()->GetScene<Scene>()->SetScore2(m_Reset);
			if (Count == 13)
			{
				Count = 13;
			}
			//auto Kakeru = stage->AddGameObject<StageSprite>(L"KAKERU_TX", true,
			//	Vec2(64.0f, 64.0f), Vec2(-460.0f, -360.0f));
			//if (m_isLayerBackGroundFlag)
			//{
			//	Kakeru->SetDrawLayer(-100);
			//}
		}
	}
}

namespace basecross {

	void OverGauge::OnCreate() {

		auto stage = GetStage();
		score = stage->AddGameObject<ScoreSprite>();
		m_scoreTrans = GetComponent<Transform>();
		m_scoreTrans->SetPosition(m_Position);
	}

	void OverGauge::OnUpdate() {


		m_Hp_now = App::GetApp()->GetScene<Scene>()->GetScore() * 1.0f;
		if (m_Hp_now >= 1000)
		{
			Count++;
			m_Hp_now = App::GetApp()->GetScene<Scene>()->SetScore(m_Reset);
		}
		score->UpdateValue(Count);
	}
}

namespace basecross {

	void PlayerRusultScore::OnCreate() {

		m_ptrTrans = GetComponent<Transform>();

		//色の設定
		Col4 color(1, 1, 1, 1); //ポリゴンの色
		float widthSize = m_Hp_now; //ポリゴンの幅
		float helfSize = 20.0f; //ポリゴンの高さ

		m_BackupVertices = {
			{VertexPositionColorTexture(Vec3(0, 0, 0), color, Vec2(0, 0))},
			{VertexPositionColorTexture(Vec3(widthSize, 0, 0), color, Vec2(1, 0))},
			{VertexPositionColorTexture(Vec3(0, -helfSize, 0), color, Vec2(0, 1))},
			{VertexPositionColorTexture(Vec3(widthSize, -helfSize, 0), color, Vec2(1, 1))},
		};

		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 2, 1, 3 };
		SetAlphaActive(m_Trace);
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0.0f);
		m_ptrTrans->SetRotation(0, 0, 0);
		m_ptrTrans->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_HpKey);
	}

	void PlayerRusultScore::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();
		auto NPCGauge = GetStage()->GetSharedGameObject<NPCRusultScore>(L"NPCResultGauge");
		auto NPCEndFlag = NPCGauge->m_EndChangeFlag;
		if (m_UpdateStartFlag)
		{
			m_DeltaTime = delta;
			auto MoveSpeed = NPCGauge->m_Speed;
			if (m_ChangeFlag == false && m_StartScale.x <= 12.5f)
			{
				m_StartScale.x += m_DeltaTime * MoveSpeed;
			}
			if (m_StartScale.x >= 12.5f)
			{
				m_ChangeFlag = true;
			}
			if (m_ChangeFlag == true && m_StartScale.x >= 5.5f && NPCEndFlag == false)
			{
				m_StartScale.x -= m_DeltaTime * MoveSpeed;
			}
			if (NPCEndFlag == true && m_StartScale.x <= 8.2f)
			{
				m_StartScale.x += m_DeltaTime * MoveSpeed;
				m_StartFlag = true;
			}
			if (m_StartFlag == true)
			{
				deltaTime += delta;
			}
			if (deltaTime >= 3.5f)
			{
				m_CreateFlag = true;
			}

			m_ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0.0f);

		}
	}
}

namespace basecross {
	void NPCRusultScore::OnCreate() {

		m_ptrTrans = GetComponent<Transform>();

		//色の設定
		Col4 color(1, 1, 1, 1); //ポリゴンの色
		float widthSize = m_Hp_now; //ポリゴンの幅
		float helfSize = 20.0f; //ポリゴンの高さ

		m_BackupVertices = {
			{VertexPositionColorTexture(Vec3(0, 0, 0), color, Vec2(0, 0))},
			{VertexPositionColorTexture(Vec3(-widthSize, 0, 0), color, Vec2(1, 0))},
			{VertexPositionColorTexture(Vec3(0, -helfSize, 0), color, Vec2(0, 1))},
			{VertexPositionColorTexture(Vec3(-widthSize, -helfSize, 0), color, Vec2(1, 1))},
		};

		//インデックス配列
		vector<uint16_t> indices = { 3, 1, 2, 2, 1, 0 };
		SetAlphaActive(m_Trace);
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0.0f);
		m_ptrTrans->SetRotation(0, 0, 0);
		m_ptrTrans->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_HpKey);
	}

	void NPCRusultScore::OnUpdate() {
		auto ptrPlayerGauge = GetStage()->GetSharedGameObject<PlayerRusultScore>(L"PlayerResultGauge");
		auto PlayerGaugeFlag = ptrPlayerGauge->m_ChangeFlag;
		auto delta = App::GetApp()->GetElapsedTime();
		if (m_UpdateStartFlag)
		{
			m_DeltaTime = delta;

			if(PlayerGaugeFlag == false)
			{
				m_StartScale.x -= m_DeltaTime * m_Speed;
			}
			if (PlayerGaugeFlag == true && m_StartScale.x <= 12.5f && m_EndChangeFlag == false)
			{
				m_StartScale.x += m_DeltaTime * m_Speed;
			}
			if (m_StartScale.x >= 12.5f && m_EndChangeFlag == false)
			{
				m_EndChangeFlag = true;
			}
			if (m_EndChangeFlag == true && m_StartScale.x >= 8.2f)
			{
				m_StartScale.x-= m_DeltaTime * m_Speed;
			}
			m_ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0.0f);
		}
	}
}


namespace basecross {
	void PlayerResultGauge::OnCreate() {

		m_ptrTrans = GetComponent<Transform>();

		//色の設定
		Col4 color(1, 1, 1, 1); //ポリゴンの色
		float widthSize = m_Hp_now; //ポリゴンの幅
		float helfSize = 20.0f; //ポリゴンの高さ

		m_BackupVertices = {
			{VertexPositionColorTexture(Vec3(0, 0, 0), color, Vec2(0, 0))},
			{VertexPositionColorTexture(Vec3(widthSize, 0, 0), color, Vec2(1, 0))},
			{VertexPositionColorTexture(Vec3(0, -helfSize, 0), color, Vec2(0, 1))},
			{VertexPositionColorTexture(Vec3(widthSize, -helfSize, 0), color, Vec2(1, 1))},
		};

		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 2, 1, 3 };
		SetAlphaActive(m_Trace);
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0.0f);
		m_ptrTrans->SetRotation(0, 0, 0);
		m_ptrTrans->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_HpKey);	
		

	}

	void PlayerResultGauge::OnUpdate() {
		auto ptrGauge = GetStage()->GetSharedGameObject<GaugeScore>(L"Gauge");
		auto ptrNPCGauge = GetStage()->GetSharedGameObject<GaugeScoreEnemy>(L"GaugeEnemy");
		auto NPCGaugeCount = ptrNPCGauge->Count;
		Count = ptrGauge->Count;
		
		if (m_ResultFlag == false)
		{
			m_StartScale.x += 0.5f * Count;
			m_StartScale.x += 0.5f * NPCGaugeCount;
			m_ResultFlag = true;
		}

		m_ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0.0f);
	}
}
namespace basecross {

	void NPCResultGauge::OnCreate() {

		m_ptrTrans = GetComponent<Transform>();

		//色の設定
		Col4 color(1, 1, 1, 1); //ポリゴンの色
		float widthSize = m_Hp_now; //ポリゴンの幅
		float helfSize = 20.0f; //ポリゴンの高さ

		m_BackupVertices = {
			{VertexPositionColorTexture(Vec3(0, 0, 0), color, Vec2(0, 0))},
			{VertexPositionColorTexture(Vec3(-widthSize, 0, 0), color, Vec2(1, 0))},
			{VertexPositionColorTexture(Vec3(0, -helfSize, 0), color, Vec2(0, 1))},
			{VertexPositionColorTexture(Vec3(-widthSize, -helfSize, 0), color, Vec2(1, 1))},
		};

		//インデックス配列
		vector<uint16_t> indices = { 3, 1, 2, 2, 1, 0 };
		SetAlphaActive(m_Trace);
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0.0f);
		m_ptrTrans->SetRotation(0, 0, 0);
		m_ptrTrans->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_HpKey);
	}

	void NPCResultGauge::OnUpdate() {
		auto ptrGauge = GetStage()->GetSharedGameObject<GaugeScoreEnemy>(L"GaugeEnemy");
		auto ptrPlayerGauge = GetStage()->GetSharedGameObject<GaugeScore>(L"Gauge");
		auto GaugeCount = ptrPlayerGauge->Count;
		Count = ptrGauge->Count;

		if (m_ResultFlag == false)
		{
			m_StartScale.x += 0.5f * Count;
			m_StartScale.x -= 0.5f * GaugeCount;
			m_ResultFlag = true;
		}

		m_ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0.0f);
	}
}


