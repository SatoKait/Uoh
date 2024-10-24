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
		Vec3 m_StartScale;		// 初期スケール
		Vec3 m_PlayerPos;		// プレイヤーの位置

		shared_ptr<Transform> m_ptrTrans;		//トランスフォーム
		shared_ptr<DrawComponent> m_ptrDraw;	// 描画
		weak_ptr<MainCamera> m_camera;			// カメラ

		Vec2 GetInputState() const;		//プレイヤーが使用するコントローラとキーボードの入力
		Vec3 GetMoveVector() const;		// コントローラから方向ベクトルを得る
		void MovePlayer();				// プレイヤーの移動
		
		InputHandler<Player> m_InputHandler;//入力ハンドラー

		
		float m_Speed;			//スピード
		bool m_grounded;		//接地しているかどうか
		//float m_JumpHeight;		//ジャンプの高さ
		float m_Accel;			//加速度
		//bool m_Jump;			//ジャンプの
	public:
		// 構築と破棄
		Player::Player(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale

		) :
			GameObject(StagePtr),
			m_StartPos(Position),
			m_StartScale(Scale),
			m_Speed(6.0f),
			m_grounded(1)
		{
		}
		Player::~Player() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//Aボタン
		//void OnPushA();
	};
}
//end basecross

