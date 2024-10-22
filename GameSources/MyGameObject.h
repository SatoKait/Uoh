/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MyGameObject : public GameObject {
	protected:
		shared_ptr<Transform>m_ptrTrans;
	public:


		explicit MyGameObject(const shared_ptr<Stage>& stagePtr);
		

	};
}
//end basecross
