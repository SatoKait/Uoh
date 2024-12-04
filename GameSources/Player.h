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

		Vec3 m_change;

		shared_ptr<Transform> m_ptrTrans;		//トランスフォーム
		shared_ptr<DrawComponent> m_ptrDraw;	// 描画
		shared_ptr<CollisionObb>m_ptrPollCol;
		shared_ptr<MainCamera> m_ptrCamera;
		shared_ptr<GameStage> m_Stage;
		shared_ptr<BcPNTBoneModelDraw> m_MoveAnimation;

		Vec2 GetInputState() const;		//プレイヤーが使用するコントローラとキーボードの入力
		Vec3 GetMoveVector();		// コントローラから方向ベクトルを得る
		void MovePlayer();				// プレイヤーの移動
		
		InputHandler<Player> m_InputHandler;//入力ハンドラー

		
		float m_Speed;			//スピード
		float m_JSpeed;			//ジャンプするスピード
		float m_Accel;			//y軸加速度
		float m_JumpTime;		//ジャンプしてからの経過時間
		bool m_MoveFlag;		//動けるまでのフラグ
		float m_GoalTime;		//ゴールタイム
		Vec3 m_Rotate;			//傾き
		float m_ChangeTime;
		bool m_ChangeFlag;
		bool m_PollChangeFlag;
		bool m_CircleChangeFlag;
		bool m_DrawFlag;
		float m_StanTime;
		bool m_StanFlag;
		int m_CircleCount;

	private:
		shared_ptr<Transform> m_trans;
		shared_ptr<CollisionCapsule> m_col;
		//shared_ptr<CollisionObb> m_col;
		//shared_ptr<CollisionObb> m_col2;

	public:
		bool m_Goal;			//ゴール判定
		bool m_SpeedUp;         //
		float m_Angle;
		Vec3 m_bfrAngle;
		Vec3 m_moveAngle;
		float m_rotAng;
		bool m_grounded;		//接地しているかどうか
		int  m_Nextcircle;
		bool  m_GoalFlag;
		bool m_StopFlag;

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
			m_ChangeTime(2.0f),
			m_ChangeFlag(false),
			m_PollChangeFlag(false),
			m_CircleChangeFlag(false),
			m_DrawFlag(true),
			m_Angle(0.0f),
			m_bfrAngle(0.0f),
			m_StanTime(0.0f),
			m_moveAngle(0.0f),
			m_Nextcircle(0),
			m_CircleCount(0),
			m_GoalFlag(false),
			m_StopFlag(false)
		{
		}

		Player::~Player() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//当たり判定(当たった瞬間)
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		void Goaltrue();
		//float PlayerAngle() const;

		//Aボタン
		//void OnPushA();
	};
}
//end basecross

