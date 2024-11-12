#pragma once
#include "stdafx.h"

namespace basecross {
	class UITime : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Score;
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;

	public:
		UITime(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~UITime() {}
		void SetScore(float f) {
			m_Score = f;
		}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};
}
//end namespace basecross
