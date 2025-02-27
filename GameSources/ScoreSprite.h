//@file ScoreSprite.h
//@brief Scoreスプライト
//@authors SatouKaito YoshidaTomoki andouTinami


#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	Scoreスプライトクラス
	//--------------------------------------------------------------------------------------
	class ScoreSprite : public GameObject
	{
		vector<VertexPositionColorTexture> m_vertices;

		shared_ptr<PCTSpriteDraw>m_ptrDraw;

	public:
		// 構築と破棄
		ScoreSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~ScoreSprite()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新

		void UpdateValue(int value);
	};

}
//end basecross
