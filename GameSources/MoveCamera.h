#pragma once
#include "stdafx.h"

namespace basecross {
	class MoveCamera :public GameObject
	{
	private:
		Vec3 m_Scale;
		Vec3 m_Position;
		Vec3 m_Rotate;
		Vec3 m_MoviePos;//カメラの目標の地点
		Vec3 m_MovieAt;//カメラの目標の視点
		Vec3 m_AfterPlayerScale;//ムービー用にする前のPlayerの大きさ
		Mat4x4 m_AfterPlayerMat;//ムービー用にする前のPlayerの差分行列の数値
		shared_ptr<Transform> m_ptrTrans;
		shared_ptr<Camera> m_MovieCamera;//ムービー用のカメラ
		weak_ptr<MainCamera> m_StageCamera;//ステージのカメラ(ゲームプレイ用)
		weak_ptr<ViewBase> m_StageView;//ステージのビュー(ゲームプレイ用)
		//shared_ptr<Sprite> m_MovieBand;//ムービー用の帯
		//shared_ptr<Sprite> m_BossMoji;//Bossを表すための文字
		weak_ptr<Player> m_Player;//Getsharedしなくても見ることが出来る


		int m_Count;//フラグ管理
		float m_Time;

	public:
		MoveCamera::MoveCamera(shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 moviePos, Vec3 movieAt) :
			GameObject(stage),
			m_Position(pos),
			m_Scale(scale),
			m_MoviePos(moviePos),
			m_MovieAt(movieAt),
			m_Count(0),
			m_Time(3.0f)
		{
		}
		MoveCamera::~MoveCamera() {}

		void OnCreate()override;
		void OnUpdate()override;

		Vec3 MoveVec(float speed, Vec3 Pos, Vec3 tagetPos);//移動ベクトルを求める関数

		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;//コリジョンが入った時

	};
}
