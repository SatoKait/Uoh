#pragma once
#include "stdafx.h"

namespace basecross {
	class MoveCamera :public GameObject
	{
		private:
			weak_ptr<MainCamera> m_Owner;

			// 水平角
			float m_AlphaAngle;

			// 仰角
			float m_BetaAngle;

			// 距離
			float m_Distance;

		public:
			MoveCamera(const shared_ptr<Stage>& ptrStage);
			virtual ~MoveCamera();

			void OnCreate() override;

			void CameraOperate();
			void CameraReset();
			void OnUpdate() override;

			void SetOwner(const shared_ptr<MainCamera>& ptrCamera)
			{
				m_Owner = ptrCamera;
			}
   };
	class MainCamera2 : public Camera
	{
		// 注視対象オブジェクトのトランスフォームコンポーネント
		weak_ptr<GameObject> m_Target;

		// カメラの回り込み（ラジアン）
		float m_AngleY;

	public:
		MainCamera2();
		virtual ~MainCamera2();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		/*!
		 @brief カメラが注視する対象物を設定する
		 @param[in] ptrTarget 注視する対象物
		 @return なし
		 */
		void SetTarget(const shared_ptr<GameObject>& ptrTarget)
		{
			m_Target = ptrTarget;
		}

		/*!
		 @brief カメラが注視する対象物を取得する
		 @return 注視する対象物
		 */
		shared_ptr<GameObject> GetTarget() const
		{
			return m_Target.lock();
		}

		/*!
		 @brief カメラの回り込みの角度を設定する
		 @param[in] angle カメラの回り込みの角度（ラジアン角）
		 @return なし
		 */
		void SetAngleY(const float& angle)
		{
			m_AngleY = angle;
		}

		/*!
		 @brief カメラの回り込みの角度を取得する
		 @return カメラの回り込みの角度（ラジアン角）
		 */
		float GetAngleY() const
		{
			return m_AngleY;
		}
	};
}
//end basecross
