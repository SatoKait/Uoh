/*!
@file MiniMapManager.cpp
@brief ミニマップなど実体
@authors YoshidaTomoki
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
		m_mapSize(200),
		m_MiniMapDrawFlag(true)
	{

	}

	MiniMapManager::~MiniMapManager()
	{

	}

	void MiniMapManager::OnCreate()
	{
		//ミニマップの灰色部分の作成//もともと灰色のスプライトだったのを
		auto stage = GetStage();//ステージ取得
		float Lenght = 235.0f;//ミニマップの直径
		auto haikei = stage->AddGameObject<MiniMapSprite>(L"Haikei_TX", Vec2(Lenght, Lenght), Vec3(-640 + (Lenght / 2.0f), 400.0f - (Lenght / 2.0f), 0.0f));
		haikei->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.5f));//ここで透明にしている
		GetStage()->SetSharedGameObject(L"haikei", haikei);

		m_startPos = Vec3(-640 + (Lenght / 2.0f), 400.0f - (Lenght / 2.0f), 5.0f);//スタートポジション
		auto test = m_startPos;
		auto a = 0;
		//m_mapSize = 200;//mapの直径
		m_mapMagnification = Lenght / m_mapSize;//マップの倍率

		CreateGate();//マンホールを生成//動かないのでここで書きMiniMapManegerで出てくる
		CreateGateRed();
		CreatCircleGate();
		CreatRedCircleGate();
		CreatePlayer();//最初の位置を設定している？//動くものはGameStageにも書かれている
		CreateCircle();
		CreatePoll();
	}

	void MiniMapManager::OnUpdate()
	{
	}


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
				auto miniMapmovegate = stage->AddGameObject<MiniMapMoveGate>(castitem, L"MiniMap_TX", Vec2(itemScale.x * m_mapMagnification, itemScale.z * m_mapMagnification), 5,
					Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f));
				miniMapmovegate->AddTag(L"MiniMapItem");//タグを追加
				miniMapmovegate->SetDrawLayer(3);
				
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
		int itemNumNow = 1;
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
			if (itemNumNow >= m_beforeItemNum )
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
					}
				}
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
				auto castManhole = dynamic_pointer_cast<PollBlue>(manhole);
				if (castManhole)//アイテム型にキャストする
				{
					auto itemTrans = manhole->GetComponent<Transform>();
					auto itemPos = itemTrans->GetPosition();
					auto itemScale = itemTrans->GetScale();

					auto ptrGate = stage->AddGameObject<MiniMapSprite>(L"BLUE_TX", Vec2((itemScale.x * m_mapMagnification * ScaleBailrtu), (itemScale.z * m_mapMagnification * ScaleBailrtu)),
						Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 10);
				}
			}

		}

		void MiniMapManager::CreatePoll()
		{
			auto ScaleBailrtu = 2.5f;
			auto stage = GetStage();//ステージ取得
			//ステージのオブジェクトを全て取得
			auto obj = stage->GetGameObjectVec();
			//取得したオブジェクトがアイテムに変換できたら配列に入れる
			for (auto manhole : obj)
			{
				auto castManhole = dynamic_pointer_cast<Poll>(manhole);
				if (castManhole)//アイテム型にキャストする
				{
					auto itemTrans = manhole->GetComponent<Transform>();
					auto itemPos = itemTrans->GetPosition();
					auto itemScale = itemTrans->GetScale();
					auto ptrGate = stage->AddGameObject<MiniMapSprite>(L"GREEN_TX", Vec2((itemScale.x * m_mapMagnification * ScaleBailrtu), (itemScale.z * m_mapMagnification * ScaleBailrtu)),
						Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 10);
				}
			}

		}

		void MiniMapManager::CreateGateRed()
		{
			auto ScaleBailrtu = 2.5f;
			auto stage = GetStage();//ステージ取得
			//ステージのオブジェクトを全て取得
			auto obj = stage->GetGameObjectVec();
			//取得したオブジェクトがアイテムに変換できたら配列に入れる
			for (auto manhole : obj)
			{
				auto castManhole = dynamic_pointer_cast<PollRed>(manhole);
				if (castManhole)//アイテム型にキャストする
				{
					auto itemTrans = manhole->GetComponent<Transform>();
					auto itemPos = itemTrans->GetPosition();
					auto itemScale = itemTrans->GetScale();
					auto ptrGate = stage->AddGameObject<MiniMapSprite>(L"RED_TX", Vec2((itemScale.x * m_mapMagnification * ScaleBailrtu), (itemScale.z * m_mapMagnification * ScaleBailrtu)),
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

					auto CircleGate = stage->AddGameObject<MiniMapSprite>(L"BLUE_TX", Vec2((itemScale.x * m_mapMagnification * ScaleBailrtu), (itemScale.z * m_mapMagnification * ScaleBailrtu)),
						Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 10);
					if (m_MiniMapDrawFlag == true)
					{
						CircleGate->SetDrawLayer(-100);
					}
				}
			}

		}

		void MiniMapManager::CreatRedCircleGate()
		{
			auto ScaleBailrtu = 2.5f;
			auto stage = GetStage();//ステージ取得
			//ステージのオブジェクトを全て取得
			auto obj = stage->GetGameObjectVec();
			//取得したオブジェクトがアイテムに変換できたら配列に入れる
			for (auto manhole : obj)
			{
				auto castManhole = dynamic_pointer_cast<RedCirclePoll>(manhole);
				if (castManhole)//アイテム型にキャストする
				{
					auto itemTrans = manhole->GetComponent<Transform>();
					auto itemPos = itemTrans->GetPosition();
					auto itemScale = itemTrans->GetScale();

					auto CircleGate = stage->AddGameObject<MiniMapSprite>(L"RED_TX", Vec2((itemScale.x * m_mapMagnification * ScaleBailrtu), (itemScale.z * m_mapMagnification * ScaleBailrtu)),
						Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 10);
					if (m_MiniMapDrawFlag == true)
					{
						CircleGate->SetDrawLayer(-100);
					}
				}
			}

		}
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

					auto ptrPlayer = stage->AddGameObject<MiniMapActor>(castPlayer, L"MiniMapPlayer_TX", Vec2((10 * m_mapMagnification), (10 * m_mapMagnification)), m_startPos, m_mapSize, Lenght);
					//if (m_MiniMapDrawFlag)
					//{
						ptrPlayer->SetDrawLayer(-100);
					//}
				}
			}
		}

		Vec3 MiniMapManager::GetStartPos()
		{
			return m_startPos;
		}

		void MiniMapManager::CreateNPC()//Playerの場所を出している
		{
			auto stage = GetStage();//ステージ取得
			//ステージのオブジェクトを全て取得
			auto obj = stage->GetGameObjectVec();
			//取得したオブジェクトがアイテムに変換できたら配列に入れる
			for (auto manhole : obj)
			{
				auto castNPC = dynamic_pointer_cast<NPC>(manhole);
				if (castNPC)//Enemy型にキャストする
				{
					float Lenght = 225.0f;//ミニマップの直径

					auto itemTrans = manhole->GetComponent<Transform>();
					auto itemPos = itemTrans->GetPosition();
					auto itemScale = itemTrans->GetScale();
					auto itemRotaiton = itemTrans->GetQuaternion();

					auto ptrNPC = stage->AddGameObject<MiniMapActor>(castNPC, L"MiniMapNPC_TX", Vec2((10 * m_mapMagnification), (10 * m_mapMagnification)), m_startPos, m_mapSize, Lenght);
					//if (m_MiniMapDrawFlag)
					//{
					ptrNPC->SetDrawLayer(-100);
					//}
				}
			}
		}

		Vec3 MiniMapManager::GetStartPos2()
		{
			return m_startPos2;
		}

		void MiniMapManager::CreateCircle()//Playerの場所を出している
		{
			auto stage = GetStage();//ステージ取得
			//ステージのオブジェクトを全て取得
			auto obj = stage->GetGameObjectVec();
			//取得したオブジェクトがアイテムに変換できたら配列に入れる
			for (auto manhole : obj)
			{
				auto castCircle = dynamic_pointer_cast<FloatCircle>(manhole);
				if (castCircle)//Enemy型にキャストする
				{
					float Lenght = 225.0f;//ミニマップの直径

					auto itemTrans = manhole->GetComponent<Transform>();
					auto itemPos = itemTrans->GetPosition();
					auto itemScale = itemTrans->GetScale();
					auto itemRotaiton = itemTrans->GetQuaternion();

					auto ptrCircle = stage->AddGameObject<MiniMapActor>(castCircle, L"CIRCLE_TX", Vec2((13 * m_mapMagnification), (13 * m_mapMagnification)), m_startPos, m_mapSize, Lenght);
				}
			}
		}

		Vec3 MiniMapManager::GetStartPos3()
		{
			return m_startPos3;
		}

}
//end basecross
