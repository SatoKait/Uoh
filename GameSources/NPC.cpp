/*!
@file NPC.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	NPC::NPC(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}

	NPC::~NPC() {};

	// 初期化
	void NPC::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		auto m_ptrAction = AddComponent<Action>();
		//m_ptrAction->AddRotateBy(1.0f, Vec3(0, XM_PI, 0));
		//m_ptrAction->AddRotateInterval(1.0f);
		const float debug = 0.3f, lotsec = 0.5f,
			deg180 = XM_PI, deg90 = XM_PIDIV2, deg45 = XM_PIDIV4,
			jump = 7.5f;
		bool debugFlag = false;
		if (debugFlag == false)
		{
			m_ptrAction->AddMoveBy(2.0f, Vec3(-15.0f, 0, 5.0f));
			m_ptrAction->AddMoveBy(1.5f, Vec3(0.0f, jump, 8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);
			m_ptrAction->AddMoveBy(2.0f, Vec3(-15.0f, -jump, 5.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			m_ptrAction->AddMoveBy(1.5f, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(3.3f, Vec3(0.0f, 0, 33.0f));
			m_ptrAction->AddMoveBy(1.5f, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(2.0f, Vec3(15.0f, 0, 5.0f));
			m_ptrAction->AddMoveBy(1.5f, Vec3(0.0f, jump, 8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);
			m_ptrAction->AddMoveBy(1.0f, Vec3(5.0f, -jump, 1.5f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			m_ptrAction->AddMoveBy(2.8f, Vec3(10.0f, 0, -35.5f));
			m_ptrAction->AddMoveBy(1.5f, Vec3(0.0f, jump, -8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);
			m_ptrAction->AddMoveBy(1.3f, Vec3(1.5f, -jump, -17.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			m_ptrAction->AddMoveBy(1.5f, Vec3(8.5f, 0, -18.5f));
			m_ptrAction->AddMoveBy(1.0f, Vec3(5.0f, 0, 1.5f));
			m_ptrAction->AddMoveBy(1.5f, Vec3(0.0f, jump, 8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);
			m_ptrAction->AddMoveBy(2.0f, Vec3(15.0f, -jump, 4.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			m_ptrAction->AddMoveBy(1.5f, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(3.3f, Vec3(0.0f, 0, 33.0f));
			m_ptrAction->AddMoveBy(1.5f, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(2.2f, Vec3(-9.0f, 0, 15.0f));
			m_ptrAction->AddMoveBy(1.0f, Vec3(-2.0f, jump, 5.0f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear); //20
			m_ptrAction->AddMoveBy(1.7f, Vec3(-5.0f,  -jump, -10.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			m_ptrAction->AddMoveBy(2.5f, Vec3(-14.0f, 0, -30.0f));
			m_ptrAction->AddMoveBy(1.5f, Vec3(0.0f, jump, -8.5f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);
			m_ptrAction->AddMoveBy(1.5f, Vec3(0.0f, -jump, -20.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
			m_ptrAction->AddMoveBy(1.5f, Vec3(0.0f, 0, -20.0f));

			// 回転
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, -deg45, 0));
			m_ptrAction->AddRotateInterval(1.0f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, deg45, 0));
			m_ptrAction->AddRotateInterval(1.0f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, -deg45, 0));
			m_ptrAction->AddRotateInterval(1.5f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, deg45, 0));
			m_ptrAction->AddRotateInterval(5.5f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, deg45, 0));
			m_ptrAction->AddRotateInterval(2.0f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, -deg45, 0));
			m_ptrAction->AddRotateInterval(1.5f);
			m_ptrAction->AddRotateBy(lotsec * 4, Vec3(0, -deg180, 0));
			m_ptrAction->AddRotateInterval(5.0f);
			m_ptrAction->AddRotateBy(lotsec * 4, Vec3(0, deg180, 0));
			m_ptrAction->AddRotateInterval(1.0f);
			m_ptrAction->AddRotateBy(lotsec * 2, Vec3(0, deg45, 0));
			m_ptrAction->AddRotateInterval(1.0f);
			m_ptrAction->AddRotateBy(lotsec * 2, Vec3(0, -deg45, 0));
			m_ptrAction->AddRotateInterval(5.5f);
			m_ptrAction->AddRotateBy(lotsec, Vec3(0, -deg45, 0));
			m_ptrAction->AddRotateInterval(1.5f);
			m_ptrAction->AddRotateBy(2.0f, Vec3(0, deg180 + deg45, 0));
			m_ptrAction->AddRotateInterval(8.0f);
			m_ptrAction->AddRotateBy(0.0f, Vec3(0, deg180, 0));

		}
		else
		{
			// 移動
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 0.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(-15.0f, 0, 5.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(-15.0f, 0, 5.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 33.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(15.0f, 0, 5.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(5.0f, 0, 1.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(10.0f, 0, -35.5f)); //10
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, -8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(10.0f, 0, -35.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(5.0f, 0, 1.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(15.0f, 0, 4.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 33.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, 8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(-9.0f, 0, 15.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(-2.0f, 0, 5.0f)); //20
			m_ptrAction->AddMoveBy(debug, Vec3(-5.0f, 0, -10.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(-12.0f, 0, -30.0f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, -8.5f));
			m_ptrAction->AddMoveBy(debug, Vec3(0.0f, 0, -40.0f));
		}

		//m_ptrAction->AddMoveBy(0.5f, Vec3(0, 1.0f, -1.0f), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);
		//m_ptrAction->AddMoveBy(0.5f, Vec3(0, -1.0f, -1.0f), Lerp::Linear, Lerp::Easein, Lerp::Linear);
		//m_ptrAction->AddMoveBy(2.0f, Vec3(-4.0f, 0, 0));
		//m_ptrAction->AddMoveBy(1.0f, Vec3(0, 0, 2.0f));
		//m_ptrAction->AddMoveBy(1.0f, Vec3(2.0f, 0, 0));

		//ループする
		m_ptrAction->SetLooped(true);
		//アクション開始
		m_ptrAction->Run();

		//衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetFixed(true);
		//描画処理
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"TOBIUO_MESH");
		ptrDraw->SetTextureResource(L"TOBIUO_TX");
		ptrDraw->SetOwnShadowActive(true);

	}

	void NPC::OnUpdate()
	{

	}

}
//end basecross
