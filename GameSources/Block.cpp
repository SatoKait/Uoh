/*!
@file Block.cpp
@brief Blockクラスの実装
@authors YoshidaTomoki
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


		auto drawComp = AddComponent<PNTStaticInstanceDraw>(); //Instanceと付いたドローコンポーネントを生成します
		drawComp->SetMeshResource(m_meshResName);
		drawComp->SetTextureResource(L"block");
		drawComp->SetOwnShadowActive(true);
		//drawComp->SetMeshToTransformMatrix(spanMat);


		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(m_meshResName);

	}
}
