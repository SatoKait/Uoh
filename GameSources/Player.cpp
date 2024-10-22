/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"
#define GROUNDED 0.0000000f

namespace basecross{
	Vec2 Player::GetInputState() const
	{
		Vec2 ret;
		ret.x = 0.0f;
		ret.y = 0.0f;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		//キーボードの取得(キーボード優先)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//前
			ret.y = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//左
			ret.x = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//後ろ
			ret.y = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//右
			ret.x = 1.0f;
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

	void Player::MovePlayer()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);
		}
		//回転の計算
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}

		//auto angle = 
	}

	void Player::OnCreate()
	{

		// トランスフォーム
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_StartPos);
		m_ptrTrans->SetRotation(0, 0, 0);
		m_ptrTrans->SetScale(m_StartScale);

		// コリジョン
		auto col = AddComponent<CollisionSphere>();

		// 重力
		auto gra = AddComponent<Gravity>();

		// ジャンプの高さ
		m_JumpHeight = 8.0f;


		//カメラオブジェクトを取得する
		auto ptrCamera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			ptrCamera->SetTarget(GetThis<GameObject>());
		}

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		
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
		ptrShadow->SetMultiMeshResource(L"TOBIUO_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMultiMeshResource(L"TOBIUO_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

	}

	void Player::OnUpdate()
	{
		// デバッグ用ストリーム
		wstringstream wss(L"");

		//重力の取得
		auto gra = GetComponent<Gravity>();
		//ポジションの取得
		auto pos = GetComponent<Transform>()->GetPosition();
		//コントローラの取得
		auto cntl = App::GetApp()->GetInputDevice().GetControlerVec();
		// デルタタイムを取得する
		float delta = App::GetApp()->GetElapsedTime(); // 前フレームからの「経過時間」

		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();

		//地面についてるかの判定
		auto GV = GetComponent<Gravity>()->GetGravityVelocity().y;
		if (GV == GROUNDED) m_grounded = true;
		else m_grounded = false;

		//if (m_JumpHeight/2.0f - 0.1f <= pos.y)
		//{
		//	gra->SetGravity(bsm::Vec3(0.0f, -1.0f, 0.0f));
		//}
		//if(m_grounded == true)
		//{
		//	gra->SetGravity(bsm::Vec3(0.0f, -9.8f, 0.0f));
		//}
		if (cntl[0].wPressedButtons & XINPUT_GAMEPAD_A)
		{
			m_accel = 1.0f;
			if (m_grounded == false)
			{
				pos.y += m_accel * m_Speed * delta;
			}

		}

		// 座標
		wss << L"pos : (" <<
			pos.x << L", " <<
			pos.y << L", " <<
			pos.z << L")" //<< 
			//L"\ngra : " << 
			//gra 
			<<endl;

		// デバッグ用文字列
		auto scene = App::GetApp()->GetScene<Scene>();
		auto dstr = scene->GetDebugString();
		scene->SetDebugString(wss.str());

	}


	//Aボタン
	//void Player::OnPushA() {
	//	if (m_grounded == true)
	//	{
	//		//auto grav = GetComponent<Gravity>();
	//		//grav->StartJump(Vec3(0, m_JumpHeight, 0));

	//		m_accel = 1.0f;
	//	}
	//}
}
//end basecross

