/*!
@file Ground.h
@brief ステージなど
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	// Groundキャラ
	//--------------------------------------------------------------------------------------
	class Ground : public GameObject {
		// Transformコンポーネント
		shared_ptr<Transform>m_ptrTrans;
		Vec3 m_Position;
		Vec3 m_Scale;

	public:
		// 構築と破棄
		Ground::Ground(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale

		) :
			GameObject(StagePtr),
			m_Position(Position),
			m_Scale(Scale)
		{
		}
		Ground::~Ground() {}

		//初期化
		virtual void OnCreate()override;
	};//end basecross

}//end basecross

