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

		// プレイヤーの描画
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetFogEnabled(true);

		//カメラオブジェクトを取得する
		auto ptrCamera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			ptrCamera->SetTarget(GetThis<GameObject>());
		}

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	}
	void Player::OnUpdate()
	{
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();
		auto GV = GetComponent<Gravity>()->GetGravityVelocity().y;
		if (GV == GROUNDED) m_grounded = true;
		else m_grounded = false;
	}


	//Aボタン
	void Player::OnPushA() {
		if (m_grounded == true)
		{
			auto grav = GetComponent<Gravity>();
			grav->StartJump(Vec3(0, 8.0f, 0));
		}
	}

}
//end basecross

