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
		Vec3 m_StartRot;
		Vec3 m_PlayerPos;		// プレイヤーの位置

		shared_ptr<Transform> m_ptrTrans;		//トランスフォーム
		shared_ptr<DrawComponent> m_ptrDraw;	// 描画
		weak_ptr<MainCamera> m_camera;			// カメラ

		Vec2 GetInputState() const;		//プレイヤーが使用するコントローラとキーボードの入力
		Vec3 GetMoveVector() const;		// コントローラから方向ベクトルを得る
		void MovePlayer();				// プレイヤーの移動
		
		InputHandler<Player> m_InputHandler;//入力ハンドラー

		
		float m_Speed;			//スピード
		float m_JSpeed;			//ジャンプするスピード
		bool m_grounded;		//接地しているかどうか
		float m_Accel;			//y軸加速度
		float m_JumpTime;		//ジャンプしてからの経過時間
		bool m_MoveFlag;		//動けるまでのフラグ
		float m_GoalTime;		//ゴールタイム
		Vec3 m_Rotate;			//傾き
		float m_ChangeTime;
		bool m_ChangeFlag;
		//int m_Score;

	public:
		bool m_Goal;			//ゴール判定
		bool m_SpeedUp;         //

		// 構築と破棄
		Player::Player(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale,
			const Vec3& Rot

		) :
			GameObject(StagePtr),
			m_StartPos(Position),
			m_StartScale(Scale),
			m_StartRot(Rot),
			m_Speed(10.0f),
			m_JSpeed(6.0f),
			m_grounded(true),
			m_MoveFlag(true),
			m_Goal(false),
			m_GoalTime(0.0f),
			m_SpeedUp(false),
			m_Rotate(0.0f),
			m_ChangeTime(0),
			m_ChangeFlag(false)
		{
		}
		Player::~Player() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//当たり判定(当たった瞬間)
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		void Goaltrue();
		//Aボタン
		//void OnPushA();
	};
}
//end basecross

