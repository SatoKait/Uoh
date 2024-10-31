/*!
@file Ground.cpp
@brief ステージなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// Groundキャラ
	//--------------------------------------------------------------------------------------
	void Ground::OnCreate(){
		m_ptrTrans = GetComponent<Transform>();	
		m_ptrTrans->SetScale(m_Scale);
		m_ptrTrans->SetPosition(m_Position);

		auto col = AddComponent<CollisionObb>();
		col->SetDrawActive(true);
		col->SetFixed(true);

		Mat4x4 spanMat; // モデルとトランスフォーム間の差分行列
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
		m_ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		m_ptrDraw->SetTextureResource(m_ResKey);
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);
	}

	void Ground::OnUpdate()
	{
		// デバッグ用ストリーム
		wstringstream wss(L"");
		//ステージの取得
		auto stage = GetStage();
		//ポジションの取得
		auto pos = GetComponent<Transform>()->GetPosition();
		// デルタタイムを取得する
		float delta = App::GetApp()->GetElapsedTime(); // 前フレームからの「経過時間」
		////プレイヤーの参照
		//auto ptrplayer = stage->GetSharedGameObject<Player>(L"Player");
		//Vec3 ptrplayerPos = ptrplayer->m_PlayerPos;

		m_camera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		auto camerapos = m_camera->GetEye();

		
		m_ptrTrans->SetPosition(Vec3(m_Position.x, m_Position.y, m_Position.z));
		m_Position.z += 10.0f * delta * m_Speed;

		if (camerapos.z + 60.0f <= m_Position.z)
		{
			m_Position.z = -250.0f;
		}
	 
		// 座標
		    wss << L"\n\n\n\npos : (" <<
			pos.x << L", " <<
			pos.y << L", " <<
			pos.z << L")"  

			<< endl;

		// デバッグ用文字列
		auto scene = App::GetApp()->GetScene<Scene>();
		auto dstr = scene->GetDebugString();
		scene->SetDebugString(wss.str());	

	}

	//void Ground::OnDestroy()
	//{
	//	delete this;
	//}

};//end basecross