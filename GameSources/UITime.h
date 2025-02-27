/*!
@file UiTime.h
@brief 時間制限の宣言
@authors YoshidaTomoki
*/
#pragma once
#include "stdafx.h"

namespace basecross {
	class UITime : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		Col4 m_color;
		wstring m_TextureKey;
		float m_Score;
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;

	public:
		bool m_isBackGrundDrawFlag;

		UITime(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~UITime() {}
		void SetScore(float f) {
			m_Score = f;
		}
		Col4 GetColor();
		void SetColor(Col4 color);
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

	//00:00の左側の部分
	class UITime2 : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		Col4 m_color;
		wstring m_TextureKey;
		float m_Score;
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;

	public:
		bool m_isBackGrundDrawFlag;

		UITime2(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~UITime2() {}
		void SetScore(float f) {
			m_Score = f;
		}
		Col4 GetColor();
		void SetColor(Col4 color);
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


	//最後の十秒カウント
	class LastTime : public GameObject {
		bool m_Trace3;
		Vec2 m_StartScale3;
		Vec3 m_StartPos3;
		wstring m_TextureKey3;
		float m_Score3;
		int m_DrawLayer;
		//桁数
		UINT m_NumberOfDigits3;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices3;

	public:
		bool m_isDrawFlag;
		LastTime(const shared_ptr<Stage>& StagePtr3, UINT NumberOfDigits3,
			const wstring& TextureKey3, bool Trace3,
			const Vec2& StartScale3, const Vec3& StartPos3);
		virtual ~LastTime() {}
		void SetScore3(float f) {
			m_Score3 = f;
		}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

}//end namespace basecross
