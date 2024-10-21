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

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
	}


};//end basecross