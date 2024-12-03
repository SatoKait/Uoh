#pragma once
#include "stdafx.h"

namespace basecross {
	class MoveCamera :public GameObject
	{
		private:
			weak_ptr<MainCamera> m_Owner;

			// …•½Šp
			float m_AlphaAngle;

			// ‹ÂŠp
			float m_BetaAngle;

			// ‹——£
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
}
