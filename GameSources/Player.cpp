/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

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


	Vec3 Player::GetMoveVector()
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
			m_Angle = frontAngle + cntlAngle;
			//角度からベクトルを作成
			angle = Vec3(cos(m_Angle), 0, sin(m_Angle));
			//正規化する
			angle.normalize();
			//移動サイズを設定。
			angle *= moveSize;
			//Y軸は変化させない
			angle.y = 0;
		}

		return angle;
	}

	// ------------------------------------------ //
	// ほぼこの中にUpdate()関数内の内容が入ってる //
	// ------------------------------------------ //
	void Player::MovePlayer() {
		//キーボードの取得(キーボード優先)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		//カメラオブジェクトを取得する
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());

		float delta = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		//トランスフォームの取得
		auto trans = GetComponent<Transform>();
		//ポジションの取得
		auto pos = trans->GetPosition();
		// 大きさの取得
		auto scale = trans->GetScale();
		//コントローラの取得
		auto cntl = App::GetApp()->GetInputDevice().GetControlerVec();
		auto ptrMana = App::GetApp()->GetXAudio2Manager();

		bool Release = true;

		const float deltatime = 4.0f;

		Vec2 ret;
		if (cntl[0].bConnected)
		{
			if (m_MoveFlag)//フラグがたっていなければ操作ができない
			{
				ret.x = cntl[0].fThumbLX;
				ret.y = cntl[0].fThumbLY;
			}
			if (m_Movetime <= deltatime)
			{
				m_Movetime += delta;
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
			if (m_Movetime <= deltatime)
			{
				m_Movetime += delta;
			}

		}
		if (m_Movetime >= deltatime && !m_StartFlag)
		{
			m_MoveFlag = true;
			m_StartFlag = true;
		}

		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * delta * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);
		}

		//回転の計算
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			if (m_grounded)
			{
				m_rotAng = -m_Angle + XM_PI / 2;
				m_ptrTrans->SetRotation(0.0f, m_rotAng, 0.0f);
			}
			else m_ptrTrans->SetRotation(0.0f, m_rotAng, -m_Rotate.z);
			//ptrCamera->SetEye(pos.x + 10.0f, 1.0f, pos.z);
		}
		if (m_MoveFlag)
		{
			// 飛んだ瞬間の判定
			if (cntl[0].wPressedButtons & XINPUT_GAMEPAD_B || KeyState.m_bPressedKeyTbl[VK_SPACE])
			{
				if (m_grounded == true)
				{
					ptrMana->Start(L"FloatSE", 0, 0.5f);
					m_grounded = false;
					m_JumpTime = 0;
					if (Release == false) m_Accel = 2.0f;
					else				 m_Accel = 2.2f;
					m_SpeedUp = true;
					m_bfrAngle = angle;
				}
			}
		}
		// ジャンプと左右移動したときの傾き
		if (m_grounded == false)
		{
			pos.y += m_JSpeed * m_Accel * delta;

			// 傾きの制限
			if (m_Rotate.z <= 1.0f && m_Rotate.z >= -1.0f)
			{
				m_Rotate.z += ret.x * 0.025;
			}
			// 傾きの制限以上になった時のリセット的なやつ
			if (m_Rotate.z >= 1.0f && ret.x <= -0.1f)
			{
				m_Rotate.z = 0.9f;
			}
			if (m_Rotate.z <= -1.0f && ret.x >= 0.1f)
			{
				m_Rotate.z = -0.9f;
			}
			// 滞空時間の引き延ばし
			if (m_JumpTime <= 2.0f)
			{
					m_Accel -= 0.025f;

			}
			else
			{
				if (Release == false)	m_Accel -= 0.005f;
				else					m_Accel -= 0.0005f;

			}
		}
		//高速着水
		//if (m_grounded == false && m_JumpTime >= 2.0f && cntl[0].wPressedButtons & XINPUT_GAMEPAD_B ||
		//	m_grounded == false && m_JumpTime >= 2.0f && cntl[0].wReleasedButtons & XINPUT_GAMEPAD_B ||
		//	m_grounded == false && m_JumpTime >= 2.0f && KeyState.m_bPressedKeyTbl[VK_SPACE] ||
		//	m_grounded == false && m_JumpTime >= 2.0f && KeyState.m_bUpKeyTbl[VK_SPACE])
		//{
		//	pos.y += m_JSpeed * m_Accel * delta;
		//	m_Accel = -3.0f;
		//}
		const float posYcnst = 1.6f;
		if (pos.y < scale.y * posYcnst)
		{
			if (m_grounded == false)
			{
				ptrMana->Start(L"EnterWaterSE", 0, 0.5f);
			}
			m_grounded = true;
			pos.y = scale.y * posYcnst;
			m_Accel = 0.0f;
			m_Rotate.z = 0;
			m_SpeedUp = false;
		}
		const float AngleLim = 1.1f, lim = 0.1f;
		if (m_MoveFlag)
		{
			// プレイヤーの移動
			if (m_grounded)
			{
				ChangeAnimation(L"Swim");

				if (ret.x || ret.y)
				{
					pos += angle * m_Speed * delta; // デルタタイムを掛けて「秒間」の移動量に変換する
					if ((ret.x <= AngleLim && ret.x >= -AngleLim) ||
						(ret.y <= AngleLim && ret.y >= -AngleLim))
					{
						m_moveAngle = angle;
						if (m_moveAngle.x <= lim || m_moveAngle.x >= -lim)
						{
							m_moveAngle.x *= 1.5f;
						}
						if (m_moveAngle.z <= lim || m_moveAngle.z >= -lim)
						{
							m_moveAngle.z *= 1.5f;
						}
					}
				}
				else pos += m_moveAngle * m_Speed * delta;
			}

			if (!m_grounded)
			{
				ChangeAnimation(L"Jump");

				// 飛んでいるときの移動処理
				if (!ret.x || !ret.y)
				{
					pos += m_moveAngle * m_Speed * delta;
				}
				else if (ret.x || ret.y)
				{
					pos += angle * m_Speed * delta;
				}
				//else  pos += m_bfrAngle * m_Speed * delta;
			}
		}

		// 位置の更新
		m_ptrTrans->SetPosition(pos);
	}

	void Player::OnCreate()
	{
		AddTag(L"Player");
		// トランスフォーム
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_StartPos);
		m_ptrTrans->SetRotation(m_StartRot);
		m_ptrTrans->SetScale(m_StartScale);

		// コリジョン
		m_col = AddComponent<CollisionCapsule>();
		m_col->SetAfterCollision(AfterCollision::Auto);

		//m_col->SetDrawActive(true);
		//m_col2->SetDrawActive(true);

		//カメラオブジェクトを取得する
		auto ptrCamera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			ptrCamera->SetTarget(GetThis<GameObject>());
			//ptrCamera->
		}

		// プレイヤーの描画
		m_spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 0.2f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PIDIV2, 0.0f),
			Vec3(0.0f, -1.3f, -2.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"TOBIUO_MESH");
		ptrShadow->SetMeshToTransformMatrix(m_spanMat);

		//m_Animation = AddComponent<BcPNTBoneModelDraw>();
		//m_Animation->SetMeshResource(L"TOBIUO_MESH");
		//m_Animation->SetMeshToTransformMatrix(m_spanMat);

		//m_Animation->AddAnimation(L"Default", 0, 50, true, 20.0f);
		//m_Animation->ChangeCurrentAnimation(L"Default");

		//透明処理
		SetAlphaActive(true);

		m_Animation = AddComponent<BcPNTBoneModelDraw>();
		m_Animation->SetMeshResource(L"TOBIUO_MESH");
		m_Animation->SetMeshToTransformMatrix(m_spanMat);

		m_Animation->AddAnimation(L"Close", 0, 10, true, 30.0f);
		m_Animation->AddAnimation(L"Swim", 15, 40, true, 30.0f);
		m_Animation->AddAnimation(L"Jump", 66, 50, false, 60.0f);
		m_Animation->AddAnimation(L"Goal", 123, 140, true, 30.0f);

		m_Animation->ChangeCurrentAnimation(L"Swim");

		SetAlphaActive(true);
	}

	void Player::OnUpdate()
	{
		//アニメーションを更新する
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

		// デバッグ用ストリーム
		wstringstream wss(L"");
		// カメラの取得
		auto ptrCamera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
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

		// ジャンプしてからの経過時間
		m_JumpTime += delta;
		m_StanTime += delta;
		// 開始してからの経過時間
		if (m_Goal == false)
		{
			m_GoalTime += delta;
		}

		Vec2 ret;
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();

		if (m_StanFlag)
		{
			m_ptrTrans->SetRotation(0.0f, m_StanTime * 10.0f, 0.0f);
		}
		if (m_grounded)
		{
			m_ptrTrans->SetScale(0.25f, 0.25f, 0.25f);

		}
		else if (!m_grounded)
		{
			m_ptrTrans->SetScale(1.5f, 0.25f, 0.25f);
		}

		if (cntl[0].bConnected)
		{
			if (m_MoveFlag)//フラグがたっていなければ操作ができない
			{
				ret.x = cntl[0].fThumbLX;
				ret.y = cntl[0].fThumbLY;
			}

		}


		ptrCamera->SetAt(Vec3(pos.x, ptrCamera->m_at, pos.z));

		//auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();

		// 座標
		//wss << L"\n\n\npos : (" <<
		//	pos.x << L", " <<
		//	pos.y << L", " <<
		//	pos.z << L")" <<

		//// ゲーム画面fps
		//	L"\nFPS : "					<<
		//	fps							<<

			//endl;

		// //ゴール判定
		//	if (m_Goal){ wss << "Goal : true" << endl; }
		//	else       { wss << "Goal : false" << endl; }

		 ////ゴール判定
			//if (m_MoveFlag){ wss << "moveflag : true" << endl; }
			//else       { wss << "moveflag : false" << endl; }

		// デバッグ用文字列
		auto scene = App::GetApp()->GetScene<Scene>();
		auto dstr = scene->GetDebugString();
		scene->SetDebugString(wss.str());

		if (m_Goal)
		{
			Player::Goaltrue();
		}
		if (m_ChangeFlag == true)
		{
			m_ChangeTime -= delta;
		}
		if (m_CircleChangeFlag == true)
		{
			m_ChangeTime -= delta;
		}

		if (m_StanTime >= 2.0f && m_StanFlag)
		{
			m_StanFlag = false;
			m_MoveFlag = true;
		}

		if (m_ChangeTime <= 0.0)
		{
			m_ChangeTime = 2.0f;
			m_ptrPollCol->SetAfterCollision(AfterCollision::Auto);
			m_ChangeFlag = false;
			m_CircleChangeFlag = false;
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

	void Player::ChangeAnimation(const wstring& animationName)
	{
		if (m_Animation->GetCurrentAnimation() != animationName)
		{
			m_Animation->ChangeCurrentAnimation(animationName);
		}
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other)
	{

		auto scene = App::GetApp()->GetScene<Scene>();
		auto stage = GetStage();
		auto ptrMana = App::GetApp()->GetXAudio2Manager();

		auto ptrCircle = stage->GetSharedGameObject<FloatCircle>(L"FloatCircle");

		// デルタタイムを取得する
		float delta = App::GetApp()->GetElapsedTime(); // 前フレームからの「経過時間」
		auto  Time = 0;
		auto  flag = false;


		if (other->FindTag(L"Goal"))
		{
			stage->AddGameObject<GoalSprite>(L"GOAL_TX",
				Vec2(600.0f, 360.0f), Vec3(0.0f, 10.0f, 0.0f));

			m_Goal = true;
		}

		auto ScoreFlag = false;

		if (other->FindTag(L"FloatCircle") && ScoreFlag == false)
		{
			ptrMana->Start(L"PointSE", 0, 1.0f);

			ScoreFlag = true;
			auto ciclenext = ptrCircle->m_next++;
			auto comboCount = ptrCircle->m_ComboCount;
			comboCount++;
			if (ScoreFlag && comboCount == 1)
			{
				if (m_CircleCount < 5)
				{
					m_CircleCount++;
				}
				App::GetApp()->GetScene<Scene>()->AddScore(100 * m_CircleCount);
				App::GetApp()->GetScene<Scene>()->AddPoint(100 * m_CircleCount);
				ScoreFlag = false;
				comboCount--;
			}
		}

		if (other->FindTag(L"GoalTrophy"))
		{
			m_GoalFlag = true;
			if (m_StopFlag == true)
			{
				//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGoalScene");
			}
		}

		if (other->FindTag(L"StanObject"))
		{
			m_CircleCount = 0;
			m_Accel = -4.0f;
			m_MoveFlag = false;
			m_StanFlag = true;
			if (m_StanTime >= 3.5f)
			{
				ptrMana->Start(L"DamageSE", 0, 2.0f);
				m_StanTime = 0.0f;
			}
		}
	}
}
//end basecross

