/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class Player : public Actor
	{
		Vec3 m_StartPos;		// 初期位置
		Vec3 m_StartScale;		// 初期スケール
		Vec3 m_StartRot;
		Vec3 m_PlayerPos;		// プレイヤーの位置

		Vec3 m_change;

		Mat4x4 m_spanMat; // モデルとトランスフォームの間の差分行列

		shared_ptr<DrawComponent> m_ptrDraw;	// 描画
		shared_ptr<CollisionObb>m_ptrPollCol;
		shared_ptr<MainCamera> m_ptrCamera;
		shared_ptr<GameStage> m_Stage;
		//shared_ptr<Gate> m_ptrGate;
		shared_ptr<BcPNTBoneModelDraw> m_Animation;

		Vec2 GetInputState() const;		//プレイヤーが使用するコントローラとキーボードの入力
		void MovePlayer();				// プレイヤーの移動

		InputHandler<Player> m_InputHandler;//入力ハンドラー

		Effekseer::Handle m_handle;
		Effekseer::ManagerRef m_manager;
		EffekseerRendererDX11::RendererRef m_renderer;
		Effekseer::EffectRef m_effect;

		float m_Speed;			//スピード
		float m_JSpeed;			//ジャンプするスピード
		float m_Accel;			//y軸加速度
		float m_JumpTime;		//ジャンプしてからの経過時間
		float m_GoalTime;		//ゴールタイム
		Vec3 m_Rotate;			//傾き
		float m_ChangeTime;
		bool m_ChangeFlag;
		bool m_PollChangeFlag;
		bool m_CircleChangeFlag;
		bool m_DrawFlag;
		float m_StanTime;
		bool m_StanFlag;
		float m_Movetime;
		bool m_StartFlag;
		bool m_ShadowFlag;
		bool m_StopFly;
	private:
		shared_ptr<Transform> m_trans;
		shared_ptr<CollisionCapsule> m_col;
		shared_ptr<BcPNTStaticDraw> m_Draw;

	public:	
		shared_ptr<Transform> m_ptrTrans;		//トランスフォーム
		float deltatime;
		bool m_MoveFlag;		//動けるまでのフラグ
		int m_CircleCount;
		int m_EffectCount;
		bool  m_GoalFlag;	
		bool m_StopFlag;
		bool m_Goal;			//ゴール判定
		bool m_SpeedUp;         //
		float m_Angle;
		Vec3 m_bfrAngle;
		Vec3 m_moveAngle;
		float m_rotAng;
		bool m_grounded;		//接地しているかどうか
		int  m_Nextcircle;
		bool m_CameraFlag;

		Vec3 GetMoveVector();		// コントローラから方向ベクトルを得る

		Player::Player(shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale,
			const Vec3& Rot
		) :
			Actor(StagePtr),
			m_StartPos(Position),
			m_StartScale(Scale),
			m_StartRot(Rot),
			m_Speed(10.0f),
			m_JSpeed(6.0f),
			m_grounded(true),
			m_MoveFlag(false),
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
			m_StopFlag(false),
			m_StartFlag(false),
			m_CameraFlag(false),
			m_ShadowFlag(true),
			m_StopFly(true),
			m_handle(0),
			m_manager(nullptr), 
			m_renderer(nullptr), 
			m_effect(nullptr),
			m_EffectCount(0), 
			deltatime(11.0f)
		{
		}

		Player::~Player() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//当たり判定(当たった瞬間)
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		void Goaltrue();
		void ChangeAnimation(const wstring& animationName);
	};

	class PlShadow : public Actor
	{
		Vec3 m_StartPos;		// 初期位置
		Vec3 m_StartScale;		// 初期スケール
		Vec3 m_StartRot;

	private:
		shared_ptr<BcPNTStaticDraw> m_Draw;

	public:
		PlShadow::PlShadow(
			shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale,
			const Vec3& Rot
		) :
			Actor(StagePtr),
			m_StartPos(Position),
			m_StartScale(Scale),
			m_StartRot(Rot)
		{
		}

		PlShadow::~PlShadow() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;


	};
}
//end basecross

