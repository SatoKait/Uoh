/*!
@file OpningCamera.cpp
@brief オープニングカメラ実体
@authors SatouKaito YoshidaTomoki
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//　ゴールオブジェクト
	//--------------------------------------------------------------------------------------
	//構築と破棄
	GoalObject::GoalObject(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}
	GoalObject::~GoalObject() {}
	//初期化
	void GoalObject::OnCreate() {
		
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.5f, 0.5f, 0.5f);
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(18.0f, 0.25f, 18.0f);
		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetDiffuse(Col4(1.0f, 0, 0, 1.0f));
	}


	//--------------------------------------------------------------------------------------
	//　球体のカメラマン
	//--------------------------------------------------------------------------------------
	//構築と破棄
	Cameraman::Cameraman(const shared_ptr<Stage>& StagePtr,
		float ToPlayerLen
	) :
		GameObject(StagePtr),
		m_ToPlayerLen(ToPlayerLen)
	{}
	Cameraman::~Cameraman() {}

	//初期化
	void Cameraman::OnCreate() {
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(0, -m_ToPlayerLen, 1.0f);
		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
	}
	//操作
	void Cameraman::OnUpdate() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		Vec3 span = pos - playerPos;
		float nowLen = length(span);
		span.normalize();
		span *= m_ToPlayerLen;
		Vec3 target = playerPos + span;
		target.y = playerPos.y + 1.0f;
		Easing<Vec3> easig;
		Vec3 v;
		if (nowLen < 1.5f) {
			v = easig.EaseIn(EasingType::Cubic, pos, target, 0.7, 1.0f);
		}
		else {
			v = easig.EaseIn(EasingType::Cubic, pos, target, 0.3f, 1.0f);
		}
		ptrTrans->SetPosition(v);
	}

	//--------------------------------------------------------------------------------------
	//　オープニングカメラマン
	//--------------------------------------------------------------------------------------
	//構築と破棄
	OpeningCameraman::OpeningCameraman(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_StartPos(-20.0f, 5.0f, -20.0f),
		m_EndPos(18.0f, 2.0f, 10.0f),
		m_AtStartPos(0.0f, 0.0f, 0.0f),
		m_AtEndPos(18.0f, 0.0f, 18.0f),
		m_AtPos(m_AtStartPos),
		m_TotalTime(0.0f),
		m_ChangeFlag(false)
	{}
	OpeningCameraman::~OpeningCameraman() {}
	//初期化
	void OpeningCameraman::OnCreate() {
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_StartPos);
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<OpeningCameraman>(GetThis<OpeningCameraman>()));
		//最初のステートをOpeningCameramanToGoalStateに設定
		m_StateMachine->ChangeState(OpeningCameramanToGoalState::Instance());
	}
	//操作
	void OpeningCameraman::OnUpdate() {
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
	}

	//ここがゴール（赤ブロック）までの場所
	void OpeningCameraman::ToGoalEnterBehavior() {
		m_StartPos = Vec3(-50.0f, 30.0f, -50.0f);
		m_EndPos = Vec3(50.0f, 30.0f, 50.0f);
		m_AtStartPos = Vec3(-10.0f, 0.0f, 0.0f);
		m_AtEndPos = Vec3(0.0f, 0.0f, 0.0f);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;//ここが5.0fになったら下のChangeStateが発生する//何秒地点にいるかというもの
	}

	//ここがゴールからPlayerまでの場所
	void OpeningCameraman::ToStartEnterBehavior() {
		m_StartPos = Vec3(50.0f, 30.0f, 50.0f);
		m_EndPos = Vec3(-2.5f, 1.0f, -48.0f);
		m_AtStartPos = Vec3(18.0f, 0.0f, 18.0f);
		m_AtEndPos = Vec3(0.0f, 0.0f, 0.0f);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	bool OpeningCameraman::ExcuteBehavior(float totaltime) {
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

	void OpeningCameraman::EndStateEnterBehavior() {
		m_ChangeFlag = true;
		auto ptrGameGtage = GetTypeStage<GameStage>();
		ptrGameGtage->ToMyCamera();
	}
	//フェードイン
	//カメラをPlayerの位置
	//マリオカート見たいな奴



	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToGoalState> OpeningCameramanToGoalState::Instance() {
		static shared_ptr<OpeningCameramanToGoalState> instance(new OpeningCameramanToGoalState);
		return instance;
	}
	void OpeningCameramanToGoalState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->ToGoalEnterBehavior();
	}
	void OpeningCameramanToGoalState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
		if (Obj->ExcuteBehavior(5.0f)) {
			Obj->GetStateMachine()->ChangeState(OpeningCameramanToStartState::Instance());
		}
	}
	void OpeningCameramanToGoalState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToStartState> OpeningCameramanToStartState::Instance() {
		static shared_ptr<OpeningCameramanToStartState> instance(new OpeningCameramanToStartState);
		return instance;
	}
	void OpeningCameramanToStartState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->ToStartEnterBehavior();
	}
	void OpeningCameramanToStartState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
		if (Obj->ExcuteBehavior(3.0f)) {
			Obj->GetStateMachine()->ChangeState(OpeningCameramanEndState::Instance());
		}
	}
	void OpeningCameramanToStartState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanEndState> OpeningCameramanEndState::Instance() {
		static shared_ptr<OpeningCameramanEndState> instance(new OpeningCameramanEndState);
		return instance;
	}
	void OpeningCameramanEndState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->EndStateEnterBehavior();
	}
	void OpeningCameramanEndState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
	}
	void OpeningCameramanEndState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}
}