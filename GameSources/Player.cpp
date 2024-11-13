/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Vec2 Player::GetInputState() const
	{
		float delta = App::GetApp()->GetElapsedTime();
		Vec2 ret;
		ret.x = 0.0f;
		ret.y = 0.0f;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;

			//m_FrontRadian += (XM_PI / (m_Status.turnPaformanve / m_SpeedRate)) * m_ElapsedTime * (m_Slope.x / 20.0f);

		}
		//キーボードの取得(キーボード優先)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		float BaseSpeed = 3.0f;
		if (KeyState.m_bPushKeyTbl['W']) {
			//前
			ret.y = BaseSpeed * m_Speed * delta;
		}
		if (KeyState.m_bPushKeyTbl['A']) {
			//左
			ret.x = -BaseSpeed * m_Speed * delta;
		}
		if (KeyState.m_bPushKeyTbl['S']) {
			//後ろ
			ret.y = -BaseSpeed * m_Speed * delta;
		}
		if (KeyState.m_bPushKeyTbl['D']) {
			//右
			ret.x = BaseSpeed * m_Speed * delta;
		}
		return ret;
	}


	Vec3 Player::GetMoveVector() const
	{
		Vec3 angle(0, 0, 0);
		//入力の取得
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;
		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0;	//動いた時のスピード
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//進行方向の向きを計算
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//進行方向向きからの角度を算出
			float frontAngle = atan2(front.z, front.x);
			//コントローラの向き計算
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//コントローラの向きから角度を計算
			float cntlAngle = atan2(-moveX, moveZ);
			//トータルの角度を算出
			float totalAngle = frontAngle + cntlAngle;
			//角度からベクトルを作成
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//正規化する
			angle.normalize();
			//移動サイズを設定。
			angle *= moveSize;
			//Y軸は変化させない
			angle.y = 0;
		}

		return angle;

	}

	void Player::MovePlayer() {
		//キーボードの取得(キーボード優先)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		//カメラオブジェクトを取得する
		auto ptrCamera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());

		float delta = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		//トランスフォームの取得
		auto trans = GetComponent<Transform>();
		//ポジションの取得
		auto pos = trans->GetPosition();
		// 大きさの取得
		auto scale = trans->GetScale();
		// 傾きの取得
		//auto rotate = trans->GetRotation();
		//コントローラの取得
		auto cntl = App::GetApp()->GetInputDevice().GetControlerVec();

		Vec2 ret;

		if (cntl[0].bConnected)
		{
			if (m_MoveFlag)//フラグがたっていなければ操作ができない
			{
				ret.x = cntl[0].fThumbLX;
				ret.y = cntl[0].fThumbLY;
			}
		}
		else if (!cntl[0].bConnected)
		{
			if (m_MoveFlag)
			{
				if (KeyState.m_bPushKeyTbl['W'])
					ret.y = 1;

				if (KeyState.m_bPushKeyTbl['A'])
					ret.x = -1;

				if (KeyState.m_bPushKeyTbl['S'])
					ret.y = -1;

				if (KeyState.m_bPushKeyTbl['D'])
					ret.x = 1;
			}
		}

		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * delta * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);
		}
		//回転の計算
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
		if (cntl[0].wPressedButtons & XINPUT_GAMEPAD_A || KeyState.m_bPressedKeyTbl[VK_SPACE])
		{

			if (m_grounded == true)
			{
				m_grounded = false;
				m_JumpTime = 0;
				m_Accel = 2.0f;
				m_SpeedUp = true;
			}
		}
		if (m_grounded == false)
		{
			pos.y += m_JSpeed * m_Accel * delta;

			if (m_Rotate.z <= 1.5f && m_Rotate.z >= -1.5f)
			{
				m_Rotate.z += ret.x * 0.015;
				ptrCamera->SetTargetToAt(Vec3(m_Rotate.z * 1.2f, 1.0f, 0));
			}


			m_Accel -= 0.02f;

			//if (ret.x >= 0.1)
			//{
			//	rotate.z += -4.0f * delta;
			//}
			//else if (ret.x <= -0.1)
			//{
			//	rotate.z += 4.0f * delta;
			//}
			//else
			//{
			//	rotate.z = 0;
			//}
		}
		if (m_grounded == false && m_JumpTime >= 2.0f && cntl[0].wPressedButtons & XINPUT_GAMEPAD_A ||
			m_grounded == false && m_JumpTime >= 2.0f && cntl[0].wReleasedButtons & XINPUT_GAMEPAD_A ||
			m_grounded == false && m_JumpTime >= 2.0f && KeyState.m_bPressedKeyTbl[VK_SPACE] ||
			m_grounded == false && m_JumpTime >= 2.0f && KeyState.m_bUpKeyTbl[VK_SPACE])
		{
			pos.y += m_JSpeed * m_Accel * delta;
			m_Accel = -3.0f;
		}
		const float posYcnst = 1.25f;
		if (pos.y < scale.y * posYcnst)
		{
			m_grounded = true;
			pos.y = scale.y * posYcnst;
			m_Accel = 0.0f;
			m_Rotate.z = 0;
			m_SpeedUp = false;
			ptrCamera->SetTargetToAt(Vec3(0, 1.0f, 0));
		}

		// プレイヤーの移動
		pos += angle * m_Speed * delta; // デルタタイムを掛けて「秒間」の移動量に変換する
		m_ptrTrans->SetPosition(pos);

		m_ptrTrans->SetRotation(0, 0, -m_Rotate.z);
	}

	void Player::OnCreate()
	{

		// トランスフォーム
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_StartPos);
		m_ptrTrans->SetRotation(m_StartRot);
		m_ptrTrans->SetScale(m_StartScale);

		// コリジョン
		auto col = AddComponent<CollisionSphere>();

		//カメラオブジェクトを取得する
		auto ptrCamera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			ptrCamera->SetTargetObject(GetThis<GameObject>());
			ptrCamera->SetTargetToAt(Vec3(0, 1.0f, 0));
			//ptrCamera->
		}
		
		// プレイヤーの描画
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PIDIV2, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"TOBIUO_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"TOBIUO_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

	}

	void Player::OnUpdate()
	{

		// デバッグ用ストリーム
		wstringstream wss(L"");

		//トランスフォームの取得
		auto trans = GetComponent<Transform>();
		//ポジションの取得
		auto pos = trans->GetPosition();
		// 大きさの取得
		auto scale = trans->GetScale();
		// 傾きの取得
		auto rotate = trans->GetRotation();
		//コントローラの取得
		auto cntl = App::GetApp()->GetInputDevice().GetControlerVec();

		// デルタタイムを取得する
		float delta = App::GetApp()->GetElapsedTime(); // 前フレームからの「経過時間」

		//auto stage = GetStage();
		//auto ptrGround = stage->GetSharedGameObject<Ground>(L"Ground");
		//auto ptrGroundflag = ptrGround->m_Speed = 5;
		// ジャンプしてからの経過時間
		m_JumpTime += delta;
		// 開始してからの経過時間
		if (m_Goal == false)
		{
			m_GoalTime += delta;
		}

		Vec2 ret;
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();


		if (cntl[0].bConnected)
		{
			if (m_MoveFlag)//フラグがたっていなければ操作ができない
			{
				ret.x = cntl[0].fThumbLX;
				ret.y = cntl[0].fThumbLY;
			}

		}

		//// プレイヤーの描画
		//Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		//spanMat.affineTransformation(
		//	Vec3(1.0f, 1.0f, 1.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(ret.x, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f)
		//);

		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();

		// 座標
			wss		<< L"\n\n\npos : (" <<
			pos.x	<< L", "			<<
			pos.y	<< L", "			<<
			pos.z	<< L")"				<< 
		// ゲーム画面fps
			L"\nFPS : "					<<
			fps							<<
		// 加速度
			L"\naccel : "				<< 
			m_Accel						<<
		// ジャンプからの経過時間
			L"\nJumpTime : "			<<
			m_JumpTime					<<
		// プレイヤーの傾き
			L"\nrotateZ : "				<<
			m_Rotate.z					<<
		// ゴールまでの時間
			L"\nGoalTime : "			<<
			m_GoalTime					<<
			endl;

		 //ゴール判定
			if (m_Goal){ wss << "Goal : true" << endl; }
			else       { wss << "Goal : false" << endl; }

		//auto Draw = AddComponent<BcPNTStaticDraw>();

		//Draw->SetMeshToTransformMatrix(spanMat);

		// デバッグ用文字列
		auto scene = App::GetApp()->GetScene<Scene>();
		auto dstr = scene->GetDebugString();
		scene->SetDebugString(wss.str());


		//m_ptrTrans->SetRotation(rotate);
		
		if (m_Goal)
		{
			Player::Goaltrue();
		}

	}

	void Player::Goaltrue()
	{
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_BACK)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}

	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Goal"))
		{
			auto Stage = GetStage();

			Stage->AddGameObject<GoalSprite>(L"GOAL_TX",
		    Vec2(600.0f, 360.0f), Vec3(0.0f, 10.0f, 0.0f));

			//Stage->AddGameObject<TimeSprite>(L"",
			//	Vec2(600.0f, 360.0f), Vec3(0.0f, 10.0f, 0.0f));

			m_Goal = true;
		     
			//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGoalScene");
		}
	}
}
//end basecross

