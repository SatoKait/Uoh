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
		ptrTrans->SetScale(m_startScale.x , m_startScale.y, 1.0f);
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
}//end basecross
