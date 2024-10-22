/*!
@file Energy.cpp
@brief スクロールの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	スクロールするスプライト
	//--------------------------------------------------------------------------------------
	ScrollSprite::ScrollSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_Count(10),
		m_MovePos(0)
	{}

	ScrollSprite::~ScrollSprite() {}
	void ScrollSprite::OnCreate() {
		float helfSize = 0.5f;//サイズ
		float numberW = 1.0f;
		float numberH = 1.0f;

		//頂点配列
		m_BackupVertices = {
			{ VertexPositionTexture(Vec3(-helfSize,  helfSize, 0),  Vec2(   0.0f,    0.0f)) },
			{ VertexPositionTexture(Vec3( helfSize,  helfSize, 0),  Vec2(numberW,    0.0f)) },
			{ VertexPositionTexture(Vec3(-helfSize, -helfSize, 0),  Vec2(   0.0f, numberH)) },
			{ VertexPositionTexture(Vec3( helfSize, -helfSize, 0),  Vec2(numberW, numberH)) },
		};

		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);//透過処理
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x , m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		m_ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		m_ptrDraw->SetTextureResource(m_TextureKey);

	}

	void ScrollSprite::OnUpdate() { 
		//float elapsedTime = App::GetApp()->GetElapsedTime();
		//m_TotalTime -= elapsedTime;
		//if (m_TotalTime > 1.0f) {
		//	m_TotalTime = 1.0f;
		//}
		//vector<VertexPositionTexture> newVertices;
		//for (size_t i = 0; i < m_BackupVertices.size(); i++) {
		//	Vec2 uv = m_BackupVertices[i].textureCoordinate;
		//	if (uv.y == 0.0f) {
		//		uv.y = m_TotalTime;
		//	}
		//	if (uv.y == 0.5f) {
		//		uv.y += m_TotalTime;
		//	}

		//	auto v = VertexPositionTexture(
		//		m_BackupVertices[i].position,
		//		uv
		//	);
		//	newVertices.push_back(v);
		//}
		//auto ptrDraw = GetComponent<PTSpriteDraw>();
		//ptrDraw->UpdateVertices(newVertices);
	}
}