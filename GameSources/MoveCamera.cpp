#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void MoveCamera::OnCreate()
	{
		m_ptrTrans = GetComponent<Transform>();//toransformを取得

		m_ptrTrans->SetPosition(m_Position);//位置を設定	
		m_ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);//ローテーション（回転）を設定
		m_ptrTrans->SetScale(m_Scale);//大きさを設定

		//接触のコリジョンを追加
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		auto collider = AddComponent<CollisionObb>();
		//collider->SetFixed(true);//これでぶつかっても動かないようにする
		collider->SetAfterCollision(AfterCollision::None);
		collider->SetDrawActive(false);//コリジョンを見えるようにする
		
		//描画コンポーネント
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		AddTag(L"Ground2");
	}

	void MoveCamera::OnUpdate()
	{
		if (m_Count == 1)//動作①
		{
			//AtをEnemyに合わせる
			auto EnemyPos = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetPosition();
			Vec3 cameraAt = m_MovieCamera->GetAt();//注視点

			if (cameraAt != EnemyPos)
			{
				cameraAt.y = 2.5f;
				cameraAt += MoveVec(5.0f, cameraAt, m_MovieAt);

				m_MovieCamera->SetAt(cameraAt);//数値をセットする

				if (abs(cameraAt.x - m_MovieAt.x) <= 1.5f && abs(cameraAt.z - m_MovieAt.z) <= 1.5f)//ほぼ注視点がEnemyのPosと一緒なら
				{
					EnemyPos.y = cameraAt.y;
					m_MovieCamera->SetAt(EnemyPos);//一緒とみなす
					//GetStage()->RemoveGameObject<Sprite>(m_MovieBand);//帯を消す
					//m_Count = 2;
				}

			}

			/*	if (m_Count > 0)
				{
					wstringstream wss(L"");
					auto scene = App::GetApp()->GetScene<Scene>();
					wss << L"At.X : "
						<< L""
						<< m_MovieCamera->GetAt().x
						<< L"\nAt.Y"
						<< m_MovieCamera->GetAt().y
						<< L"\nAt.Z"
						<< m_MovieCamera->GetAt().z
						<< endl;
					scene->SetDebugString(wss.str());

				}*/

			}
		}

		Vec3 MoveCamera::MoveVec(float speed, Vec3 pos, Vec3 tagetPos)//移動する距離を決めている
		{
			float VecX = tagetPos.x - pos.x;//目標位置とPlayerとのX座標の距離を測っている
			float VecZ = tagetPos.z - pos.z;//目標位置とPlayerとのZ座標の距離を測っている
			float rad = atan2(VecZ, VecX);//角度を求める（ラジアン）

			Vec3 moveVec(0.0f, 0.0f, 0.0f);

			auto& app = App::GetApp();
			float delta = app->GetElapsedTime();//デルタタイムを取得
			moveVec.x = (speed * cos(rad)) * delta;//間接的に距離を足している
			moveVec.z = (speed * sin(rad)) * delta;//間接的に距離を足している

			return moveVec;
		}

		void MoveCamera::OnCollisionEnter(shared_ptr<GameObject>&Other)
		{
			auto stage = GetStage();


			if (Other->FindTag(L"Ground") && m_Count == 0)
			{
				//m_Player = stage->GetSharedGameObject<Player>(L"GamePlayer");//GamePlayerを取得
				//m_AfterPlayerScale = m_Player.lock()->GetComponent<Transform>()->GetScale();//変更前のサイズを取得
				////m_AfterPlayerMat = m_Player.lock()->GetComponent<PNTBoneModelDraw>()->GetMeshToTransformMatrix();//変更前の差分行列を取得

				////stage->GetSharedGameObject<StageManager>(L"StageManager")->SetStartFlag(false);//Playerの操作を効かなくさせる


				//m_Player.lock()->GetComponent<Transform>()->SetScale(1.0f, 1.0f, 1.0f);//ムービー用のサイズにする
				//Mat4x4 spanMat;
				//spanMat.affineTransformation(
				//	Vec3(1.0f, 1.0f, 1.0f),
				//	Vec3(0.0f, 0.0f, 0.0f),
				//	Vec3(0.0f, XM_PI, 0.0f),
				//	Vec3(0.0f, -0.5f, -0.05f)
				//);
				//m_Player.lock()->GetComponent<PNTBoneModelDraw>()->SetMeshToTransformMatrix(spanMat);//ムービー用のメッシュの大きさにする


				//m_Count = 1;
				//m_StageView = GetStage()->GetView();
				//m_StageCamera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());

				//デバック用
				m_MovieCamera = ObjectFactory::Create<Camera>();
				m_MovieCamera->SetEye(m_StageCamera.lock()->GetEye());
				m_MovieCamera->SetAt(m_StageCamera.lock()->GetAt());
				auto testView = GetStage()->CreateView<SingleView>();
				testView->SetCamera(m_MovieCamera);
				GetStage()->SetView(testView);
			}
		}
}
