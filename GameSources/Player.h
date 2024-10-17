/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class Player : public GameObject
	{
		Vec3 m_StartPos;		// 初期位置
		Vec3 m_StartScale;		// 初期位置

		shared_ptr<Transform> m_ptrTrans;	//トランスフォーム
		shared_ptr<DrawComponent> m_ptrDraw;	// オブジェクト
	public:
		// 構築と破棄
		Player::Player(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale

		) :
			GameObject(StagePtr),
			m_StartPos(Position),
			m_StartScale(Scale)
		{
		}
		Player::~Player() {}
		
		virtual void OnCreate() override;
		//virtual void OnUpdate() override;


	};
}
//end basecross

