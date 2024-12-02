
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//　オープニングカメラマン
	//--------------------------------------------------------------------------------------
	//構築と破棄
		Startcamera::Startcamera(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_StartPos(-20.0f, 0.0f, -20.0f),
		m_EndPos(18.0f, 2.0f, 10.0f),
		m_AtStartPos(0.0f, 0.0f, 0.0f),
		m_AtEndPos(18.0f, 0.0f, 18.0f),
		m_AtPos(m_AtStartPos),
		m_TotalTime(0.0f)
	{}
		Startcamera::~Startcamera() {}
	//初期化
	void Startcamera::OnCreate() {
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_StartPos);
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<Startcamera>(GetThis<Startcamera>()));
		//最初のステートをOpeningCameramanToGoalStateに設定
		m_StateMachine->ChangeState(CameramanToGoalState::Instance());
	}
	//操作
	void Startcamera::OnUpdate() {
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
	}

	void Startcamera::ToGoalEnterBehavior() {
		m_StartPos = Vec3(-20.0f, 10.0f, -20.0f);
		m_EndPos = Vec3(18.0f, 2.0f, 10.0f);
		m_AtStartPos = Vec3(-10.0f, 0.0f, 0.0f);
		m_AtEndPos = Vec3(18.0f, 0.0f, 18.0f);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	void Startcamera::ToStartEnterBehavior() {
		m_StartPos = Vec3(18.0f, 2.0f, 10.0f);
		m_EndPos = Vec3(0.0f, 3.0f, -5.0f);
		m_AtStartPos = Vec3(18.0f, 0.0f, 18.0f);
		m_AtEndPos = Vec3(0.0f, 0.0f, 0.0f);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	bool Startcamera::ExcuteBehavior(float totaltime) {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime;
		if (m_TotalTime > totaltime) {
			return true;
		}
		Easing<Vec3> easing;
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_StartPos, m_EndPos, m_TotalTime, totaltime);
		m_AtPos = easing.EaseInOut(EasingType::Cubic, m_AtStartPos, m_AtEndPos, m_TotalTime, totaltime);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(TgtPos);
		return false;
	}

	//void Startcamera::EndStateEnterBehavior() {
	//	auto ptrGameGtage = GetTypeStage<GameStage>();
	//	ptrGameGtage->ToMyCamera();
	//}




	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<CameramanToGoalState> CameramanToGoalState::Instance() {
		static shared_ptr<CameramanToGoalState> instance(new CameramanToGoalState);
		return instance;
	}
	void CameramanToGoalState::Enter(const shared_ptr<Startcamera>& Obj) {
		Obj->ToGoalEnterBehavior();
	}
	void CameramanToGoalState::Execute(const shared_ptr<Startcamera>& Obj) {
		if (Obj->ExcuteBehavior(5.0f)) {
			Obj->GetStateMachine()->ChangeState(CameramanToStartState::Instance());
		}
	}
	void CameramanToGoalState::Exit(const shared_ptr<Startcamera>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<CameramanToStartState> CameramanToStartState::Instance() {
		static shared_ptr<CameramanToStartState> instance(new CameramanToStartState);
		return instance;
	}
	void CameramanToStartState::Enter(const shared_ptr<Startcamera>& Obj) {
		Obj->ToStartEnterBehavior();
	}
	void CameramanToStartState::Execute(const shared_ptr<Startcamera>& Obj) {
		if (Obj->ExcuteBehavior(3.0f)) {
			Obj->GetStateMachine()->ChangeState(CameramanEndState::Instance());
		}
	}
	void CameramanToStartState::Exit(const shared_ptr<Startcamera>& Obj) {
	}
	
	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<CameramanEndState> CameramanEndState::Instance() {
		static shared_ptr<CameramanEndState> instance(new CameramanEndState);
		return instance;
	}
	void CameramanEndState::Enter(const shared_ptr<Startcamera>& Obj) {
		//Obj->EndStateEnterBehavior();
	}
	void CameramanEndState::Execute(const shared_ptr<Startcamera>& Obj) {
	}
	void CameramanEndState::Exit(const shared_ptr<Startcamera>& Obj) {
	}
}
