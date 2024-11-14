/*!
@file Sprite.h
@brief スプライト
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// タイムスプライト
	class TimeSprite : public GameObject {
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;

		//桁数
		UINT m_NumberOfDigits;

		float m_Time;

	public:
		TimeSprite(
			shared_ptr<Stage>& StagePtr,	// ステージ
			UINT NumberOfDigits,			// 桁数
			const wstring& TextureKey,
			const Vec2& StartScale,			// 大きさ
			const Vec3& StartPos);			// 初期位置
		~TimeSprite();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	class GoalSprite :public GameObject
	{
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		bool m_Trace;
		shared_ptr<PCTSpriteDraw>m_ptrDraw;


	public:
		GoalSprite(
			shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& StartScale,
			const Vec3& StartPos
		);
		~GoalSprite();

		virtual void OnCreate() override;
		//virtual void OnUpdate() override;
	};
}
namespace basecross {

	//--------------------------------------------------------------------------------------
	///	                             Stageスプライト
	//--------------------------------------------------------------------------------------
	class StageSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_ClearKey;
	public:

		StageSprite(const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~StageSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		//virtual void OnUpdate()override {}
	};


}

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	                             GameScoreスプライト
	//--------------------------------------------------------------------------------------
	class GameScoreSprite : public GameObject {
		shared_ptr<Transform>m_ptrTrans;
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_ClearKey;

		float m_NewPos;
		float m_maxPos;
		float m_minPos;
		float m_yPosSpeed;
		float m_highly;
		float m_time;
		float m_speed;
		bool m_isPosMax;
		bool m_isPosMin;
		bool m_isDraw;

		Vec3 m_nowpos;



	public:

		GameScoreSprite(const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~GameScoreSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override;

		//void OnDestroy();
	};
}

namespace basecross {

		//--------------------------------------------------------------------------------------
		///明減スプライト
		//--------------------------------------------------------------------------------------
		class Flickering : public GameObject {
			bool m_Trace;
			Vec2 m_StartScale;
			Vec2 m_StartPos;
			wstring m_TextureKey;
			//トータル時間
			float m_TotalTime;
		public:
			Flickering(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
				const Vec2& StartScale, const Vec2& StartPos);
			//破棄
			virtual ~Flickering();
			//初期化
			virtual void OnCreate() override;
			//更新
			virtual void OnUpdate()override;
		};
}

