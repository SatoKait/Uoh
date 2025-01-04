/*!
@file NPC.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class NPC : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		shared_ptr<Action> m_ptrAction;
	public:
		//構築と破棄
		NPC(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~NPC();

		virtual void OnCreate();
		virtual void OnUpdate();

	};

}
//end basecross
