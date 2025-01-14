/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapManager::MiniMapManager(shared_ptr<Stage>& stagePtr, float mapSize) :
		GameObject(stagePtr),
		m_mapSize(mapSize)
	{

	}
	MiniMapManager::MiniMapManager(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_mapSize(200)
	{

	}

	MiniMapManager::~MiniMapManager()
	{

	}

	void MiniMapManager::OnCreate()
	{
		//ミニマップの灰色部分の作成//もともと灰色のスプライトだったのを
		auto stage = GetStage();//ステージ取得
		float Lenght = 225.0f;//ミニマップの直径
		auto haikei = stage->AddGameObject<MiniMapSprite>(L"Haikei_TX", Vec2(Lenght, Lenght), Vec3(-640 + (Lenght / 2.0f), 400.0f - (Lenght / 2.0f), 0.0f));
		haikei->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.5f));//ここで透明にしている
		m_startPos = Vec3(-640 + (Lenght / 2.0f), 400.0f - (Lenght / 2.0f), 5.0f);//スタートポジション
		auto test = m_startPos;
		auto a = 0;
		//m_mapSize = 200;//mapの直径
		m_mapMagnification = Lenght / m_mapSize;//マップの倍率

		CreateMoveGate();
		CreateGate();//マンホールを生成//動かないのでここで書きMiniMapManegerで出てくる
		CreatCircleGate();
		//CreateEnemy();
		CreatePlayer();//最初の位置を設定している？//動くものはGameStageにも書かれている
	}

	void MiniMapManager::OnUpdate()
	{
		UpdateMoveGate();//ここで新しく出た物を更新してマップに反映している
	}

	////ミニマップ用の壁を生成
	//void MiniMapManager::CreateWall()
	//{

	//}

	//ミニマップ用のアイテムを生成
	void MiniMapManager::CreateMoveGate()
	{
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto objVec = stage->GetGameObjectVec();
		auto count = 0;
		//取得したオブジェクトがアイテムに変換できたら配列に入れる
		for (auto item : objVec)
		{
			auto castitem = dynamic_pointer_cast<Gate>(item);
			if (castitem)//アイテム型にキャストする
			{
				auto itemTrans = item->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();

				auto miniMapItem = stage->AddGameObject<MiniMapMoveGate>(castitem, L"MiniMap_TX", Vec2(itemScale.x * m_mapMagnification, itemScale.z * m_mapMagnification), 5,
					Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f));

				miniMapItem->AddTag(L"MiniMapItem");//タグを追加
				count++;
			}
		}
		m_beforeItemNum = count;
	}

	//ミニマップ用のアイテムを生成(Updeta版)
	void MiniMapManager::UpdateMoveGate()
	{
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto objVec = stage->GetGameObjectVec();
		int itemNumNow = 0;
		//ステージにあるアイテムの数をカウントする
		for (auto item : objVec)
		{
			auto castitem = dynamic_pointer_cast<Gate>(item);
			if (castitem)//アイテム型にキャストする
			{
				itemNumNow++;
			}
		}

			//今あるアイテムの数が前よりも多かったらミニマップのアイテムの表示を更新する
			if (itemNumNow <= m_beforeItemNum)//同じ数になったので更新処理をするようになった
			{
				//ミニマップにあるアイテムをリセットする
				for (auto sprite : objVec)
				{
					auto castsprite = dynamic_pointer_cast<MiniMapSprite>(sprite);
					if (castsprite)//アイテム型にキャストする
					{
						//タグがMiniMapItem
						if (castsprite->FindTag(L"MiniMapItem"))
						{
							castsprite->MyDestroy();//自分自身を消去する
						}
						itemNumNow--;
					}
				}
				//再生成する
				CreateMoveGate();
			}
			m_beforeItemNum = itemNumNow;//更新する
	}


	void MiniMapManager::CreateGate()
	{
			auto ScaleBailrtu = 2.5f;
			auto stage = GetStage();//ステージ取得
			//ステージのオブジェクトを全て取得
			auto obj = stage->GetGameObjectVec();
			//取得したオブジェクトがアイテムに変換できたら配列に入れる
			for (auto manhole : obj)
			{
				auto castManhole = dynamic_pointer_cast<Poll1>(manhole);
				if (castManhole)//アイテム型にキャストする
				{
					auto itemTrans = manhole->GetComponent<Transform>();
					auto itemPos = itemTrans->GetPosition();
					auto itemScale = itemTrans->GetScale();

					stage->AddGameObject<MiniMapSprite>(L"MiniMap_TX", Vec2((itemScale.x * m_mapMagnification * ScaleBailrtu), (itemScale.z * m_mapMagnification * ScaleBailrtu)),
						Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 10);
				}
			}

	}

	void MiniMapManager::CreatCircleGate()
	{
			auto ScaleBailrtu = 2.5f;
			auto stage = GetStage();//ステージ取得
			//ステージのオブジェクトを全て取得
			auto obj = stage->GetGameObjectVec();
			//取得したオブジェクトがアイテムに変換できたら配列に入れる
			for (auto manhole : obj)
			{
				auto castManhole = dynamic_pointer_cast<CirclePoll>(manhole);
				if (castManhole)//アイテム型にキャストする
				{
					auto itemTrans = manhole->GetComponent<Transform>();
					auto itemPos = itemTrans->GetPosition();
					auto itemScale = itemTrans->GetScale();

					stage->AddGameObject<MiniMapSprite>(L"MiniMap_TX", Vec2((itemScale.x * m_mapMagnification * ScaleBailrtu), (itemScale.z * m_mapMagnification * ScaleBailrtu)),
						Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 10);
				}
			}

	}


		//ミニマップ用の敵を作成
		//void MiniMapManager::CreateEnemy()//敵の場所を出している
		//{
		//	auto stage = GetStage();//ステージ取得
		//	ステージのオブジェクトを全て取得
		//	auto obj = stage->GetGameObjectVec();
		//	取得したオブジェクトがアイテムに変換できたら配列に入れる
		//	for (auto manhole : obj)
		//	{
		//		auto castEnemy = dynamic_pointer_cast<Enemy>(manhole);
		//		if (castEnemy)//Enemy型にキャストする
		//		{
		//			float Lenght = 225.0f;//ミニマップの直径

		//			auto itemTrans = manhole->GetComponent<Transform>();
		//			auto itemPos = itemTrans->GetPosition();
		//			auto itemScale = itemTrans->GetScale();

		//			stage->AddGameObject<MiniMapActor>(castEnemy, L"MiniEnemy", Vec2((itemScale.x / m_mapMagnification) * 3, (itemScale.z / m_mapMagnification) * 3), m_startPos, m_mapSize, Lenght);
		//		}
		//	}

		//}

		void MiniMapManager::CreatePlayer()//Playerの場所を出している
		{
			auto stage = GetStage();//ステージ取得
			//ステージのオブジェクトを全て取得
			auto obj = stage->GetGameObjectVec();
			//取得したオブジェクトがアイテムに変換できたら配列に入れる
			for (auto manhole : obj)
			{
				auto castPlayer = dynamic_pointer_cast<Player>(manhole);
				if (castPlayer)//Enemy型にキャストする
				{
					float Lenght = 225.0f;//ミニマップの直径

					auto itemTrans = manhole->GetComponent<Transform>();
					auto itemPos = itemTrans->GetPosition();
					auto itemScale = itemTrans->GetScale();
					auto itemRotaiton = itemTrans->GetQuaternion();

					stage->AddGameObject<MiniMapActor>(castPlayer, L"MiniMapPlayer_TX", Vec2((10 * m_mapMagnification), (10 * m_mapMagnification)), m_startPos, m_mapSize, Lenght);
				}
			}
		}

		Vec3 MiniMapManager::GetStartPos()
		{
			return m_startPos;
		}
}
//end basecross
