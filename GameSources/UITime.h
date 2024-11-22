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


	class UITimeStage : public GameObject {
		bool m_Trace2;
		Vec2 m_StartScale2;
		Vec3 m_StartPos2;
		wstring m_TextureKey2;
		float m_Score2;
		int m_DrawLayer;
		//桁数
		UINT m_NumberOfDigits2;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices2;

	public:	
		bool m_isDrawFlag;
		UITimeStage(const shared_ptr<Stage>& StagePtr2, UINT NumberOfDigits2,
			const wstring& TextureKey2, bool Trace2,
			const Vec2& StartScale2, const Vec3& StartPos2);
		virtual ~UITimeStage() {}
		void SetScore2(float f) {
			m_Score2 = f;
		}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};
}//end namespace basecross
