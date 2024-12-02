#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//　オープニングカメラマン
	//--------------------------------------------------------------------------------------
	class Startcamera : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;
		//ステートマシーン
		unique_ptr< StateMachine<Startcamera> >  m_StateMachine;
	public:
		//構築と破棄
		Startcamera(const shared_ptr<Stage>& StagePtr);
		virtual ~Startcamera();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;
		//アクセサ
		const unique_ptr<StateMachine<Startcamera>>& GetStateMachine() {
			return m_StateMachine;
		}

		Vec3 GetAtPos() const {
			return m_AtPos;
		}
		void ToGoalEnterBehavior();
		void ToStartEnterBehavior();
		bool ExcuteBehavior(float totaltime);
		//void EndStateEnterBehavior();
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class CameramanToGoalState : public ObjState<Startcamera>
	{
		CameramanToGoalState() {}
	public:
		static shared_ptr<CameramanToGoalState> Instance();
		virtual void Enter(const shared_ptr<Startcamera>& Obj)override;
		virtual void Execute(const shared_ptr<Startcamera>& Obj)override;
		virtual void Exit(const shared_ptr<Startcamera>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class CameramanToStartState : public ObjState<Startcamera>
	{
		CameramanToStartState() {}
	public:
		static shared_ptr<CameramanToStartState> Instance();
		virtual void Enter(const shared_ptr<Startcamera>& Obj)override;
		virtual void Execute(const shared_ptr<Startcamera>& Obj)override;
		virtual void Exit(const shared_ptr<Startcamera>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class CameramanEndState : public ObjState<Startcamera>
	{
		CameramanEndState() {}
	public:
		static shared_ptr<CameramanEndState> Instance();
		virtual void Enter(const shared_ptr<Startcamera>& Obj)override;
		virtual void Execute(const shared_ptr<Startcamera>& Obj)override;
		virtual void Exit(const shared_ptr<Startcamera>& Obj)override;
	};

}
