#include "stdafx.h"
#include "Project.h"

namespace basecross {

	MoveCamera::MoveCamera(const shared_ptr<Stage>& ptrStage) :
		GameObject(ptrStage),
		m_AlphaAngle(XMConvertToRadians(-90.0f)),
		m_BetaAngle(XMConvertToRadians(45.0f)),
		m_Distance(5)
	{
	}

	MoveCamera::~MoveCamera()
	{

	}

	void MoveCamera::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(1.5f));

		auto ptrColl = AddComponent<CollisionSphere>();
	}

	void MoveCamera::CameraOperate()
	{
		//// ゲームクリアのフラグが立っている場合、コントローラーの受付を必要とする処理は一切行わない
		//auto& gptrGameManager = GameManager::GetGameManager();
		//auto isSelected = gptrGameManager->IsStageSelected();
		//auto isClear = gptrGameManager->IsStageClear();
		//if (isSelected && isClear)
		//{
		//	return;
		//}

		auto& app = App::GetApp();
		auto elapsed = app->GetElapsedTime();
		auto inputDevice = app->GetInputDevice();
		auto pad = inputDevice.GetControlerVec()[0];

		m_AlphaAngle += -XMConvertToRadians(90.0f * pad.fThumbRX) * elapsed;
		m_BetaAngle += -XMConvertToRadians(90.0f * pad.fThumbRY) * elapsed;

		if (m_BetaAngle > XMConvertToRadians(45.0f))
		{
			m_BetaAngle = XMConvertToRadians(45.0f);
		}
		else if (m_BetaAngle < XMConvertToRadians(-30.0f))
		{
			m_BetaAngle = XMConvertToRadians(-30.0f);
		}
	}

	void MoveCamera::CameraReset()
	{
		auto ptrCameraTrans = GetComponent<Transform>();
		auto ptrTargetTrans = m_Owner.lock()->GetTarget()->GetComponent<Transform>();

		auto cameraPos = ptrCameraTrans->GetPosition();
		auto targetPos = ptrTargetTrans->GetPosition();

		auto distance = (cameraPos - targetPos).length();

		if (m_Distance * 2.0f < distance)
		{
			Vec3 pos = Vec3(0.0f);
			pos.x = m_Distance * cosf(m_BetaAngle) * cosf(m_AlphaAngle);
			pos.y = m_Distance * sinf(m_BetaAngle);
			pos.z = m_Distance * cosf(m_BetaAngle) * sinf(m_AlphaAngle);
			pos += ptrTargetTrans->GetPosition();

			ptrCameraTrans->SetPosition(pos);
		}
	}

	void MoveCamera::OnUpdate()
	{
		auto ptrOwner = m_Owner.lock();
		if (ptrOwner == nullptr) return;

		auto ptrTarget = ptrOwner->GetTarget();
		if (ptrTarget == nullptr) return;

		auto& app = App::GetApp();
		auto elapsed = app->GetElapsedTime();

		auto ptrCameraTrans = GetComponent<Transform>();
		auto ptrTargetTrans = ptrTarget->GetComponent<Transform>();

		// カメラの操作
		CameraOperate();

		// カメラとプレイヤーの距離が離れ過ぎたら即座に正しい位置に戻す
		CameraReset();

		// 壁などを考慮しないで操作出来た場合のカメラの位置
		Vec3 imaginaryEyePos = Vec3(0.0f);
		imaginaryEyePos.x = m_Distance * cosf(m_BetaAngle) * cosf(m_AlphaAngle);
		imaginaryEyePos.y = m_Distance * sinf(m_BetaAngle);
		imaginaryEyePos.z = m_Distance * cosf(m_BetaAngle) * sinf(m_AlphaAngle);
		imaginaryEyePos += ptrTargetTrans->GetPosition();

		// 実際の位置
		Vec3 realityEyePos = ptrCameraTrans->GetPosition();

		// t秒後の距離が現在の距離のn倍になるようなスピードを計算
		float decayRate = 0.9f;
		float decayConstant = log(decayRate);
		float speed = -(imaginaryEyePos - realityEyePos).length() * decayConstant * exp(decayConstant * elapsed);

		// 空想の位置と実際の位置からカメラの動く方向を計算
		Vec3 moveDirection = imaginaryEyePos - realityEyePos;
		moveDirection = moveDirection.normalize();

		// 計算したスピードと方向から移動ベクトルを作成し位置ベクトルに足す
		Vec3 moveVec = speed * moveDirection;
		realityEyePos += moveVec;
		if ((imaginaryEyePos - realityEyePos).length() < speed)
		{
			realityEyePos = imaginaryEyePos;
		}

		ptrCameraTrans->SetPosition(realityEyePos);

		// 空想位置から見たプレイヤーの方向と同じ方向を見る
		auto atPos = Vec3(0.0f);
		atPos.x = ptrTargetTrans->GetPosition().x;
		atPos.y = realityEyePos.y + ptrTargetTrans->GetPosition().y - imaginaryEyePos.y;
		atPos.z = ptrTargetTrans->GetPosition().z;

		// カメラの位置と注視点を設定
		ptrOwner->SetAngleY(m_AlphaAngle);
		ptrOwner->SetEye(realityEyePos);
		ptrOwner->SetAt(atPos);
	}

	MainCamera2::MainCamera2() :
		m_AngleY(XMConvertToRadians(-90.0f))
	{
	}

	MainCamera2::~MainCamera2()
	{

	}

	void MainCamera2::OnCreate()
	{

	}

	void MainCamera2::OnUpdate()
	{

	}

}
