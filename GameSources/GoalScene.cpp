/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void GoalScene::CreateViewLight()
	{
		auto cameraView = ObjectFactory::Create<SingleView>(GetThis<GoalScene>());
		auto ptrMyCamera = ObjectFactory::Create<Camera>();
		cameraView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GoalScene::OnCreate()
	{
		try {
			CreateViewLight();
			
		}
		catch(...){
			throw;
		}
	}

	//void GoalScene::OnUpdate()
	//{

	//}
}
//end basecross
