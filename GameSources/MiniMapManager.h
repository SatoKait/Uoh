/*!
@file MiniMapManager.h
@brief ミニマップ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MiniMapManager :public GameObject
	{
	private:
		Vec3 m_startPos;//初期位置(ピポット)
		Vec3 m_startPos2;//初期位置(ピポット)
		Vec3 m_startPos3;//初期位置(ピポット)

		int m_beforeItemNum;//前のアイテムの個数

		float m_mapSize;//マップの直径
		float m_mapMagnification;//マップの倍率
	public:
		bool m_MiniMapDrawFlag;
		MiniMapManager(shared_ptr<Stage>& stage, float mapSize);
		MiniMapManager(shared_ptr<Stage>& stage);
		~MiniMapManager();

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		//void CreateWall();  //ミニマップの壁を生成する
		void CreateMoveGate();//ミニマップの移動するゲートを生成する
		void CreateGate();	  //ミニマップのマンホールを生成する
		void CreateGateRed();	  //ミニマップのマンホールを生成する
		void CreatePoll();
		//void CreateEnemy(); //ミニマップの敵を生成する
		void CreatePlayer();  //ミニマップのプレイヤーを生成する
		void CreateNPC();
		void CreateCircle();
		void CreatCircleGate();
		void CreatRedCircleGate();

		void UpdateMoveGate();//ミニマップのアイテム表示(Update版)

		Vec3 GetStartPos();//ミニマップの原点を渡す
		Vec3 GetStartPos2();//ミニマップの原点を渡す
		Vec3 GetStartPos3();//ミニマップの原点を渡す

	};

}
//end basecross
