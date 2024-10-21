/*!
@file Character.cpp
@brief キャラクターなど実体a
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
		m_TotalTime(0)
	{}

	ScrollSprite::~ScrollSprite() {}
	void ScrollSprite::OnCreate() {
		float helfSize = 0.5f;
		//頂点配列
		m_BackupVertices = {
			{ VertexPositionTexture(Vec3(-helfSize, helfSize, 0), Vec2(0.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(helfSize, helfSize, 0), Vec2(1.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(-helfSize, -helfSize, 0), Vec2(0.0f, 1.0f)) },
			{ VertexPositionTexture(Vec3(helfSize, -helfSize, 0), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_TextureKey);
	}

	void ScrollSprite::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime > 1.0f) {
			m_TotalTime = 1.0f;
		}
		vector<VertexPositionTexture> newVertices;
		for (size_t i = 0; i < m_BackupVertices.size(); i++) {
			Vec2 uv = m_BackupVertices[i].textureCoordinate;
			if (uv.x == 0.0f) {
				uv.x = m_TotalTime;
			}
			else if (uv.x == 1.0f) {
				uv.x += m_TotalTime;
			}
			auto v = VertexPositionTexture(
				m_BackupVertices[i].position,
				uv
			);
			newVertices.push_back(v);
		}
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
	}

}