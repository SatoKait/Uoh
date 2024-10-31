/*!
@file Ground.h
@brief ステージなど
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	// Groundキャラ
	//--------------------------------------------------------------------------------------
	class Ground : public GameObject {
		shared_ptr<Transform>m_ptrTrans;		// Transformコンポーネント
		shared_ptr<MainCamera>m_camera;
		shared_ptr<BcPNTStaticDraw>m_ptrDraw;
		Vec3 m_Position;
		Vec3 m_Scale;
		Vec3 m_Goal;
		wstring m_ResKey;
		float m_Speed;			 //スピード

	public:
		float m_Distance;       //距離

		// 構築と破棄
		Ground::Ground(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale,
			const wstring& ResKey

		) :
			GameObject(StagePtr),
			m_Position(Position),
			m_Scale(Scale),
			m_ResKey(ResKey),
			m_Distance(10.0f),
			m_Speed(1.0f),			//スピード
			m_Goal(Vec3(0.0f, 0.0f, 100.0f))

		{
		}
		Ground::~Ground() {}

		//初期化
		virtual void OnCreate()override;
		//
		virtual void OnUpdate()override;
        //
		//virtual void OnDestroy()override;

	};//end basecross

}//end basecross

