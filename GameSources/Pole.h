/*!
@file Pole.h
@brief 障害物など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Pole : public MyGameObject {
		// Transformコンポーネント
		Vec3 m_Position;
		Vec3 m_Scale;

	public:
		// 構築と破棄
		Pole::Pole(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale

		) :
			MyGameObject(StagePtr),
			m_Position(Position),
			m_Scale(Scale)
		{
		}
		Pole::~Pole() {}

		//初期化
		virtual void OnCreate()override;
		//virtual void OnUpdate()override;
	};//end basecross
}