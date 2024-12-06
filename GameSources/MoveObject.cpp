/*!
@file MoveObject.cpp
@brief ステージなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// MoveObjectキャラ
	//--------------------------------------------------------------------------------------
	void MoveObject::OnCreate() {
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_Scale);
		m_ptrTrans->SetPosition(m_Position);

		auto col = AddComponent<CollisionObb>();
		col->SetDrawActive(true);
		col->SetFixed(false);

		Mat4x4 spanMat; // モデルとトランスフ ォーム間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),//スケーリング
			Vec3(0.0f, 0.0f, 0.0f),//回転の中心
			Vec3(0.0f, 0.0f, 0.0f),//回転のベクトル
			Vec3(0.0f, 0.0f, 0.0f) //移動
		);
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//ptrShadow->SetMeshResource(L"BED_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		m_ptrDraw = AddComponent<BcPNTStaticDraw>();
		m_ptrDraw->SetMultiMeshResource(L"POLE_MESH");
		m_ptrDraw->SetTextureResource(m_ResKey);
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);
	}

	void MoveObject::OnUpdate()
	{
		//ステージの取得
		auto stage = GetStage();
		//ポジションの取得
		auto pos = GetComponent<Transform>()->GetPosition();
		// デルタタイムを取得する
		float delta = App::GetApp()->GetElapsedTime(); // 前フレームからの「経過時間」
		////プレイヤーの参照
		auto ptrplayer = stage->GetSharedGameObject<Player>(L"Player");
		auto ptrplayerFlag = ptrplayer->m_SpeedUp;

		m_camera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		auto camerapos = m_camera->GetEye();

		//m_ptrTrans->SetPosition(Vec3(m_Position.x + 30, m_Position.y, m_Position.z));

		//auto  r = rand() % 4;
		//if (camerapos.z + 60.0f <= m_Position.z)
		//{
		//	switch (r) {

		//	case 0:
		//	//	m_ptrTrans->SetPosition(Vec3(m_Position.x + 30, m_Position.y, m_Position.z));
		//	//	break;
		//	//case 1:
		//	//	m_ptrTrans->SetPosition(Vec3(m_Position.x - 30, m_Position.y, m_Position.z));
		//	//	m_Position.z += 10.0f * delta * m_Speed;
		//	//	break;
		//		//case 2:
		//		//	m_ptrTrans->SetPosition(Vec3(m_Position.x + 20, m_Position.y, m_Position.z));
		//		//	break;
		//		//case 3:
		//		//	m_ptrTrans->SetPosition(Vec3(m_Position.x - 20, m_Position.y, m_Position.z));
		//		//	break;
		//	}
		//}

		m_ptrTrans->SetPosition(Vec3(m_Position.x, m_Position.y, m_Position.z));
	    m_Position.z += 10.0f * delta * m_Speed;


		if (ptrplayerFlag == true)
		{
			m_Speed = 2.5f;
		}
		else{
			m_Speed = 1.0f;
		//if (camerapos.z + 60.0f <= m_Position.z)
		//{
		}
		//	m_Position.z = -250.0f;
		//}
		if (camerapos.z + 60.0f <= m_Position.z)
		{
			m_Position.z = -250.0f;
		}

	}

	//--------------------------------------------------------------------------------------
	// MoveBuoyキャラ
	//--------------------------------------------------------------------------------------
	void MoveBuoy::OnCreate() {
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_Scale);
		m_ptrTrans->SetPosition(m_Position);

		auto col = AddComponent<CollisionObb>();
		col->SetDrawActive(true);
		col->SetFixed(false);

		Mat4x4 spanMat; // モデルとトランスフ ォーム間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),//スケーリング
			Vec3(0.0f, 0.0f, 0.0f),//回転の中心
			Vec3(0.0f, 0.0f, 0.0f),//回転のベクトル
			Vec3(0.0f, 0.0f, 0.0f) //移動
		);
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//ptrShadow->SetMeshResource(L"BED_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		m_ptrDraw = AddComponent<BcPNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"BUOY_MESH");
		m_ptrDraw->SetTextureResource(m_ResKey);
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);
	}

	void MoveBuoy::OnUpdate()
	{
		//ステージの取得
		auto stage = GetStage();
		//ポジションの取得
		auto pos = GetComponent<Transform>()->GetPosition();
		// デルタタイムを取得する
		float delta = App::GetApp()->GetElapsedTime(); // 前フレームからの「経過時間」
		m_camera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		auto camerapos = m_camera->GetEye();
		m_ptrTrans->SetPosition(Vec3(m_Position.x, m_Position.y, m_Position.z));
		m_Position.x += 5.0f * delta * m_Speed;
	}

	//--------------------------------------------------------------------------------------
	// Pollキャラ
	//--------------------------------------------------------------------------------------
	void Poll::OnCreate() {
		AddTag(L"Poll2");
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_Scale);
		m_ptrTrans->SetPosition(m_Position);
		m_ptrTrans->SetRotation(m_Rotate);

		//m_col = AddComponent<CollisionObb>();
		//m_col->SetDrawActive(m_DrawFlag);
		//m_col->SetFixed(true);
		//m_col->SetSleepActive(true);
		//m_col->GetAfterCollision();
		//m_col->SetAfterCollision(AfterCollision::None);


		Mat4x4 spanMat; // モデルとトランスフ ォーム間の差分行列
		spanMat.affineTransformation(
			Vec3(0.02f, 0.0405f, 0.25f),//スケーリング
			Vec3(0.0f, 0.0f, 0.0f),//回転の中心
			Vec3(0.0f, 0.0f, 0.0f),//回転のベクトル
			Vec3(0.0f, -2.6f, 0.0f) //移動
		);
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//ptrShadow->SetMeshResource(L"BED_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto m_ptrDraw = AddComponent<PNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"POLL_2_MESH");
		m_ptrDraw->SetTextureResource(L"POLL2_TX");
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);
	}

	//--------------------------------------------------------------------------------------
	// CirclePollキャラ
	//--------------------------------------------------------------------------------------
	void CirclePoll::OnCreate() {
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_Scale);
		m_ptrTrans->SetPosition(m_Position);
		m_ptrTrans->SetRotation(m_Rotate);
		m_Number = (to_wstring(m_Count));
		AddTag(L"CirclePoll");
		m_Count++;

		//m_col = AddComponent<CollisionObb>();
		//m_col->SetDrawActive(m_DrawFlag);
		//m_col->SetFixed(true);
		//m_col->SetSleepActive(true);
		//m_col->GetAfterCollision();
		//m_col->SetAfterCollision(AfterCollision::None);


		Mat4x4 spanMat; // モデルとトランスフ ォーム間の差分行列
		spanMat.affineTransformation(
			Vec3(0.09f, 0.125f, 0.3f),//スケーリング
			Vec3(0.0f, 0.0f, 0.0f),//回転の中心
			Vec3(0.0f, 0.0f, 0.0f),//回転のベクトル
			Vec3(0.0f, 0.0f, 0.0f) //移動
		);
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//ptrShadow->SetMeshResource(L"BED_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto m_ptrDraw = AddComponent<PNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"POLL3_MESH");
		m_ptrDraw->SetTextureResource(m_ResKey);
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);
	}

	void CirclePoll::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Player"))
		{
			m_col->SetAfterCollision(AfterCollision::None);
		}

	}

	//--------------------------------------------------------------------------------------
	// Poll1キャラ
	//--------------------------------------------------------------------------------------
	void Poll1::OnCreate() {
		AddTag(L"Poll");
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_Scale);
		m_ptrTrans->SetPosition(m_Position);
		m_ptrTrans->SetRotation(m_Rotate);

		//m_col = AddComponent<CollisionObb>();
		//m_col->SetDrawActive(m_DrawFlag);
		//m_col->SetFixed(true);
		//m_col->SetSleepActive(true);
		//m_col->GetAfterCollision();
		//m_col->SetAfterCollision(AfterCollision::None);


		Mat4x4 spanMat; // モデルとトランスフ ォーム間の差分行列
		spanMat.affineTransformation(
			Vec3(0.04f,0.01f,0.04f),//スケーリング
			Vec3(0.0f, 0.0f, 0.0f),//回転の中心
			Vec3(0.0f, 0.0f, 0.0f),//回転のベクトル
			Vec3(0.0f, -0.35f, 0.0f) //移動
		);
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//ptrShadow->SetMeshResource(L"BED_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto m_ptrDraw = AddComponent<PNTStaticModelDraw>();
		m_ptrDraw->SetMeshResource(L"POLL_1_MESH");
		m_ptrDraw->SetTextureResource(L"POLL_TX");
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);
	}


	//--------------------------------------------------------------------------------------
	// PollCollisionキャラ
	//--------------------------------------------------------------------------------------

	void PollCollision::OnCreate() {
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_Scale);
		m_ptrTrans->SetPosition(m_Position);
		m_ptrTrans->SetRotation(m_Rotate);
		 

		auto col = AddComponent<CollisionObb>();
		col->SetDrawActive(m_DrawFlag);
		col->SetFixed(true);

		AddTag(L"StanObject");
	}

	//--------------------------------------------------------------------------------------
	// GoalTrophyキャラ
	//--------------------------------------------------------------------------------------
	void GoalTrophy::OnCreate() {
		AddTag(L"GoalTrophy");
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_Scale);
		m_ptrTrans->SetPosition(m_Position);
		m_ptrTrans->SetRotation(m_Rotate);


		auto col = AddComponent<CollisionObb>();
		col->SetDrawActive(m_DrawFlag);
		col->SetFixed(true);


		Mat4x4 spanMat; // モデルとトランスフ ォーム間の差分行列
		spanMat.affineTransformation(
			Vec3(0.1f, 0.1f, 0.2f),//スケーリング
			Vec3(0.0f, 0.0f, 0.0f),//回転の中心
			Vec3(0.0f, 0.0f, 0.0f),//回転のベクトル
			Vec3(0.0f, -0.25f, 0.1f) //移動
		);

		//影の形（メッシュ）を設定        
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		m_ptrDraw = AddComponent<BcPNTStaticDraw>();
		m_ptrDraw->SetMultiMeshResource(L"TROPHY_MESH");
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);
	}


};//end basecross