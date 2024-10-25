/*!
@file Block.cpp
@brief Blockクラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Block::OnCreate() {
		auto& app = App::GetApp();//アプリケーションの参照
		auto mediaPath = app->GetDataDirWString(); // 「media」パスを文字列として取得する
		auto texturePath = mediaPath + L"Textures/"; // 「Textures/」フォルダのパスを連結する
		app->RegisterTexture(L"block", texturePath + L"block.jpg");

		auto col = AddComponent<CollisionObb>();
		col->SetDrawActive(true);
		col->SetFixed(true);
		col->SetSleepActive(true);

		//Mat4x4 spanMat; // モデルとトランスフォーム間の差分行列
		//spanMat.affineTransformation(
		//	Vec3(1.0f, 1.0f, 1.0f),//スケーリング
		//	Vec3(0.0f, 0.0f, 0.0f),//回転の中心
		//	Vec3(0.0f, 0.0f, 0.0f),//回転のベクトル
		//	Vec3(0.0f, 0.0f, 0.0f) //移動
		//);

		auto drawComp = AddComponent<PNTStaticInstanceDraw>(); //Instanceと付いたドローコンポーネントを生成します
		drawComp->SetMeshResource(m_meshResName);
		drawComp->SetTextureResource(L"block");
		drawComp->SetOwnShadowActive(true);
		//drawComp->SetMeshToTransformMatrix(spanMat);


		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(m_meshResName);

	}
}
