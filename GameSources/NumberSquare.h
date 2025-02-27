/*!
@file NumberSquare.h
@brief 立体的なスプライトの宣言
@authors SatouKaito YoshidaTomoki AndouTinami
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	数字のスクエア
	//--------------------------------------------------------------------------------------
	class NumberSquare : public GameObject {
		weak_ptr<Poll> m_PollObject;
		weak_ptr<Player> m_Player;
		//このオブジェクトのみで使用するスクエアメッシュ
		shared_ptr<MeshResource> m_SquareMeshResource;
		//背番号
		wstring m_ResKey;

		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}

	public:
		//構築と破棄
		NumberSquare(const shared_ptr<Stage>& StagePtr,
			const shared_ptr<Poll>& PollObjectPtr, const wstring& ResKey);
		virtual ~NumberSquare();
		//初期化
		virtual void OnCreate() override;
		//変化
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	///	BullPollのスクエア
	//--------------------------------------------------------------------------------------
	class NumberSquare2 : public GameObject {
		weak_ptr<PollBlue> m_PollObject;
		weak_ptr<Player> m_Player;
		//このオブジェクトのみで使用するスクエアメッシュ
		shared_ptr<MeshResource> m_SquareMeshResource;
		//背番号
		wstring m_ResKey;

		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}

	public:
		//構築と破棄
		NumberSquare2(const shared_ptr<Stage>& StagePtr,
			const shared_ptr<PollBlue>& PollObjectPtr, const wstring& ResKey);
		virtual ~NumberSquare2();
		//初期化
		virtual void OnCreate() override;
		//変化
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	///	RedPollのスクエア
	//--------------------------------------------------------------------------------------
	class NumberSquare3 : public GameObject {
		weak_ptr<PollRed> m_PollObject;
		weak_ptr<Player> m_Player;
		//このオブジェクトのみで使用するスクエアメッシュ
		shared_ptr<MeshResource> m_SquareMeshResource;
		//背番号
		wstring m_ResKey;

		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}

	public:
		//構築と破棄
		NumberSquare3(const shared_ptr<Stage>& StagePtr,
			const shared_ptr<PollRed>& PollObjectPtr, const wstring& ResKey);
		virtual ~NumberSquare3();
		//初期化
		virtual void OnCreate() override;
		//変化
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	///	CirclePollのスクエア
	//--------------------------------------------------------------------------------------
	class NumberSquare4 : public GameObject {
		weak_ptr<CirclePoll> m_PollObject;
		weak_ptr<Player> m_Player;
		//このオブジェクトのみで使用するスクエアメッシュ
		shared_ptr<MeshResource> m_SquareMeshResource;
		//背番号
		wstring m_ResKey;

		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}

	public:
		//構築と破棄
		NumberSquare4(const shared_ptr<Stage>& StagePtr,
			const shared_ptr<CirclePoll>& PollObjectPtr, const wstring& ResKey);
		virtual ~NumberSquare4();
		//初期化
		virtual void OnCreate() override;
		//変化
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	///	CirclePollのスクエア
	//--------------------------------------------------------------------------------------
	class NumberSquare5 : public GameObject {
		weak_ptr<RedCirclePoll> m_PollObject;
		weak_ptr<Player> m_Player;
		//このオブジェクトのみで使用するスクエアメッシュ
		shared_ptr<MeshResource> m_SquareMeshResource;
		//背番号
		wstring m_ResKey;

		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}

	public:
		//構築と破棄
		NumberSquare5(const shared_ptr<Stage>& StagePtr,
			const shared_ptr<RedCirclePoll>& PollObjectPtr, const wstring& ResKey);
		virtual ~NumberSquare5();
		//初期化
		virtual void OnCreate() override;
		//変化
		virtual void OnUpdate() override;
	};

}