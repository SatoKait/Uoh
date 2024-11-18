/*!
@file MoveObject.h
@brief ステージなど
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	// MoveObjectキャラ
	//--------------------------------------------------------------------------------------
	class MoveObject : public GameObject {
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
		MoveObject::MoveObject(const shared_ptr<Stage>& StagePtr,
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
		MoveObject::~MoveObject() {}

		//初期化
		virtual void OnCreate()override;
		//
		virtual void OnUpdate()override;
		//
		//virtual void OnDestroy()override;

	};//end basecross

	//--------------------------------------------------------------------------------------
	// MoveBuyoキャラ
	//--------------------------------------------------------------------------------------
	class MoveBuoy : public GameObject {
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
		MoveBuoy::MoveBuoy(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale,
			const wstring& ResKey

		) :
			GameObject(StagePtr),
			m_Position(Position),
			m_Scale(Scale),
			m_ResKey(ResKey),
			m_Distance(10.0f),
			m_Speed(1.0f)			//スピード
		{
		}
		MoveBuoy::~MoveBuoy() {}

		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		//virtual void OnDestroy()override;
	};//end basecross

	//--------------------------------------------------------------------------------------
	// Pollキャラ
	//--------------------------------------------------------------------------------------
	class Poll : public GameObject {
		shared_ptr<Transform>m_ptrTrans;		// Transformコンポーネント
		shared_ptr<MainCamera>m_camera;
		shared_ptr<BcPNTStaticDraw>m_ptrDraw;
		Vec3 m_Position;
		Vec3 m_Scale;
		Vec3 m_Rotate;

		Vec3 m_Goal;
		wstring m_ResKey;
		float m_Speed;			 //スピード
		bool m_DrawFlag;


	public:
		float m_Distance;       //距離
		shared_ptr<CollisionObb>m_col;

		// 構築と破棄
		Poll::Poll(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale,
			const Vec3& m_Rotate,
			const wstring& ResKey
		) :
			GameObject(StagePtr),
			m_Position(Position),
			m_Scale(Scale),
			m_Rotate(m_Rotate),
			m_ResKey(ResKey),
			m_Distance(10.0f),
			m_Speed(1.0f),		//スピード
			m_DrawFlag(false)

		{
		}
		Poll::~Poll() {}

		//初期化
		virtual void OnCreate()override;	
		//virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
		//virtual void OnUpdate()override;
		//virtual void OnDestroy()override;
	};//end basecross

	//--------------------------------------------------------------------------------------
	// Poll1キャラ
	//--------------------------------------------------------------------------------------
	class Poll1 : public GameObject {
		shared_ptr<Transform>m_ptrTrans;		// Transformコンポーネント
		shared_ptr<MainCamera>m_camera;
		shared_ptr<BcPNTStaticDraw>m_ptrDraw;
		Vec3 m_Position;
		Vec3 m_Scale;	
		Vec3 m_Rotate;	
		Vec3 m_Goal;
		wstring m_sharedName;

		wstring m_ResKey;
		float m_Speed;			 //スピード
		bool m_DrawFlag;


	public:
		float m_Distance;       //距離
		shared_ptr<CollisionObb>m_col;

		// 構築と破棄
		Poll1::Poll1(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale,
			const Vec3& m_Rotate,

			const wstring& ResKey
		) :
			GameObject(StagePtr),
			m_Position(Position),
			m_Scale(Scale),
			m_Rotate(m_Rotate),
			m_ResKey(ResKey),
			m_Distance(10.0f),
			m_Speed(1.0f),		//スピード
			m_DrawFlag(false)

		{
		}
		Poll1::~Poll1() {}

		//初期化
		virtual void OnCreate()override;	
		//virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
		//virtual void OnUpdate()override;
		//virtual void OnDestroy()override;
	};//end basecross

	//--------------------------------------------------------------------------------------
	// CirclePollキャラ
	//--------------------------------------------------------------------------------------
	class CirclePoll : public GameObject {
		shared_ptr<Transform>m_ptrTrans;		// Transformコンポーネント
		shared_ptr<MainCamera>m_camera;
		shared_ptr<BcPNTStaticDraw>m_ptrDraw;
		Vec3 m_Position;
		Vec3 m_Scale;
		Vec3 m_Rotate;

		Vec3 m_Goal;
		wstring m_ResKey;
		wstring m_sharedName;
		////タグ設定
		vector<wstring> m_Tags;
		wstring m_Number;
		int m_Count;
		float m_Speed;			 //スピード
		bool m_DrawFlag;



	public:
		float m_Distance;       //距離
		shared_ptr<CollisionObb>m_col;

		// 構築と破棄
		CirclePoll::CirclePoll(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale,
			const Vec3& m_Rotate,

			const wstring& ResKey
		) :
			GameObject(StagePtr),
			m_Position(Position),
			m_Scale(Scale),
			m_Rotate(m_Rotate),
			m_ResKey(ResKey),
			m_Distance(10.0f),
			m_Speed(1.0f),		//スピード
			m_DrawFlag(false),
			m_Count(0)

		{
		}
		CirclePoll::~CirclePoll() {}

		//初期化
		virtual void OnCreate()override;
		void BaseAddTag(const wstring& tag)
		{
			m_Tags.push_back(tag);
		}
		void BaseAddTag(vector<wstring>& tags)
		{
			for (auto& tag : tags)
			{
				m_Tags.push_back(tag);
			}
		}

		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
		//virtual void OnUpdate()override;
		//virtual void OnDestroy()override;
	};

	//--------------------------------------------------------------------------------------
	// PollCollisionキャラ
	//--------------------------------------------------------------------------------------
	 class PollCollision : public GameObject
	  {
		 shared_ptr<Transform>m_ptrTrans;
		 Vec3 m_Position;
		 Vec3 m_Scale;
		 Vec3 m_Rotate;

		 bool m_DrawFlag;


	public:
		 PollCollision(const std::shared_ptr<Stage>& stage, const Vec3& Position, const Vec3& Scale, const Vec3& m_Rotate) :
			GameObject(stage),
			m_Position(Position),
			m_Scale(Scale),
			 m_Rotate(m_Rotate),
			 m_DrawFlag(false)

		 {
	   	 }
		void OnCreate();

	};
}//end basecros


