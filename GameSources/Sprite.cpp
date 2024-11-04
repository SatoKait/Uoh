/*!
@file Sprite.cpp
@brief スプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	TimeSprite::TimeSprite(
		shared_ptr<Stage>& StagePtr,	// ステージ
		UINT NumberOfDigits,			// 桁数
		const wstring& TextureKey,
		const Vec2& StartScale,			// 大きさ
		const Vec3& StartPos):

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

	//GoalSprite::GoalSprite(
	//	shared_ptr<Stage>& StagePtr,
	//	const wstring& TextureKey,
	//	const Vec2& StartScale,
	//	const Vec3& StartPos
	//) :
	//	GameObject(StagePtr),
	//	m_textureKey(TextureKey),
	//	m_startScale(StartScale),
	//	m_startPos(StartPos)
	//{}
	//GoalSprite::~GoalSprite() {};

	//void TimeSprite::OnCreate()
	//{
		//float helfSize = 0.5f;
		//Col4 color = Col4(1.0f);

		//const float GoalImageX = 256;
		//const float GoalImageY = 128;

		//vector<VertexPositionColorTexture> vertices = {
		//	{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),  color, Vec2(0.0f  ,fontH * fontCount))},
		//	{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0),   color, Vec2(fontW  ,fontH * fontCount))},
		//	{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), color, Vec2(0.0f  ,fontH * (fontCount + 1)))},
		//	{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0),  color, Vec2(fontW  ,fontH * (fontCount + 1)))},
		//}
	//}
	
	//void TimeSprite::OnUpdate()
	//{

	//}

}
//end basecross
