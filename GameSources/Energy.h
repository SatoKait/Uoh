/*!
@file Energy.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"
namespace basecross {
	//--------------------------------------------------------------------------------------
	///	スクロールするスプライト
	//--------------------------------------------------------------------------------------
	class ScrollSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_TotalTime;
		float m_Count;
		float m_MovePos;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
		shared_ptr<PTSpriteDraw>m_ptrDraw;

	public:
		ScrollSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~ScrollSprite();
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};
}

