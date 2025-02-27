/*!
@file NPC.h
@brief キャラクターなど
@authors SatouKaito AndouTinami
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class NPC : public Actor
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_Time;
		shared_ptr<Action> m_ptrAction;
		shared_ptr<GameObject> m_player;
		bool m_OnceFlag;
	public:
		int m_CircleCount;
		bool m_OnceFlag1;
		bool m_stopFlag;

		//構築と破棄
		NPC(shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~NPC();

		bool RandJump();

		virtual void OnCreate();
		virtual void OnUpdate();

		//当たり判定(当たった瞬間)
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};

}
//end basecross
