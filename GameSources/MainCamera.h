/*!
@file MainCamera.h
@brief カメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	MyCameraカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	class MainCamera : public Camera {
		weak_ptr<GameObject> m_TargetObject;	//目標となるオブジェクト
		float m_ToTargetLerp;	//目標を追いかける際の補間値
		bsm::Vec3 m_TargetToAt;	//目標から視点を調整する位置ベクトル
		float m_RadY;
		float m_RadXZ;
		//カメラの上下スピード
		float m_CameraUpDownSpeed;
		//カメラを下げる下限角度
		float m_CameraUnderRot;
		//腕の長さの設定
		float m_ArmLen;
		float m_MaxArm;
		float m_MinArm;
		//回転スピード
		float m_RotSpeed;
		//ズームスピード
		float m_ZoomSpeed;
		//左右スティック変更のモード
		bool m_LRBaseMode;
		//上下スティック変更のモード
		bool m_UDBaseMode;
	public:
		MainCamera();
		MainCamera(float ArmLen);
		virtual ~MainCamera();
		virtual void SetEye(const bsm::Vec3& Eye)override;
		virtual void SetEye(float x, float y, float z)override;
		shared_ptr<GameObject> GetTargetObject() const;
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		float GetToTargetLerp() const;
		void SetToTargetLerp(float f);
		float GetArmLengh() const;
		void UpdateArmLengh();
		float GetMaxArm() const;
		void SetMaxArm(float f);
		float GetMinArm() const;
		void SetMinArm(float f);
		float GetRotSpeed() const;
		void SetRotSpeed(float f);
		bsm::Vec3 GetTargetToAt() const;
		void SetTargetToAt(const bsm::Vec3& v);
		bool GetLRBaseMode() const;
		bool IsLRBaseMode() const;
		void SetLRBaseMode(bool b);
		bool GetUDBaseMode() const;
		bool IsUDBaseMode() const;
		void SetUDBaseMode(bool b);
		virtual void SetAt(const bsm::Vec3& At)override;
		virtual void SetAt(float x, float y, float z)override;
		virtual void OnUpdate()override;
	};

}
//end basecross
