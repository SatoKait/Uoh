/*!
@file Sprite.h
@brief スプライト
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// タイムスプライト
	class TimeSprite : public GameObject {
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;

		//桁数
		UINT m_NumberOfDigits;

		float m_Time;

	public:
		TimeSprite(
			shared_ptr<Stage>& StagePtr,	// ステージ
			UINT NumberOfDigits,			// 桁数
			const wstring& TextureKey,
			const Vec2& StartScale,			// 大きさ
			const Vec3& StartPos);			// 初期位置
		~TimeSprite();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	class GoalSprite :public GameObject
	{
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		bool m_Trace;
		shared_ptr<PCTSpriteDraw>m_ptrDraw;


	public:
		GoalSprite(
			shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& StartScale,
			const Vec3& StartPos
		);
		~GoalSprite();

		virtual void OnCreate() override;
		//virtual void OnUpdate() override;
	};
}
namespace basecross {

	//--------------------------------------------------------------------------------------
	///	                             Stageスプライト
	//--------------------------------------------------------------------------------------
	class StageSprite : public GameObject {
		shared_ptr<PCTSpriteDraw>PtrDraw;
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		Col4 m_color;
		wstring m_ClearKey;
	public:

		StageSprite(const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~StageSprite();
		//初期化
		virtual void OnCreate() override;
		//色の取得
		Col4 GetColor();
		void SetColor(Col4 color);

		//更新
		//virtual void OnUpdate()override {}
	};


}

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	                             GameScoreスプライト
	//--------------------------------------------------------------------------------------
	class GameScoreSprite : public GameObject {
		shared_ptr<Transform>m_ptrTrans;
		shared_ptr<PCTSpriteDraw>m_ptrDraw;
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_ClearKey;
		float m_elapsedTime;

		float m_NewPos;
		float m_maxPos;
		float m_minPos;
		float m_yPosSpeed;
		float m_highly;
		float m_time;
		float m_speed;
		bool m_isPosMax;
		bool m_isPosMin;
		bool m_isDraw;
		bool m_istimeFlag;

		Vec3 m_nowpos;



	public:

		GameScoreSprite(const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~GameScoreSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override;

		//virtual void OnDestroy()override;
	};
}

namespace basecross {

		//--------------------------------------------------------------------------------------
		///明減スプライト
		//--------------------------------------------------------------------------------------
		class Flickering : public GameObject {
			bool m_Trace;
			Vec2 m_StartScale;
			Vec2 m_StartPos;
			wstring m_TextureKey;
			//トータル時間
			float m_TotalTime;
		public:
			Flickering(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
				const Vec2& StartScale, const Vec2& StartPos);
			//破棄
			virtual ~Flickering();
			//初期化
			virtual void OnCreate() override;
			//更新
			virtual void OnUpdate()override;
		};
}

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	                             Comboスプライト
	//--------------------------------------------------------------------------------------
	class ComboSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_ClearKey;
	public:

		ComboSprite(const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		//破棄
		virtual ~ComboSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		//virtual void OnUpdate()override {}
	};


}

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	Scoreスプライトクラス
	//--------------------------------------------------------------------------------------
	class ComboSpriteNumber : public GameObject
	{
		vector<VertexPositionColorTexture> m_vertices;

		shared_ptr<PCTSpriteDraw>m_ptrDraw;

		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_ClearKey;

	public:
		// 構築と破棄
		ComboSpriteNumber(
			const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos
		) :
			GameObject(StagePtr),
			m_ClearKey(ClearKey),
			m_Trace(Trace),
			m_StartScale(StartScale),
			m_StartPos(StartPos)
		{
		}
		virtual ~ComboSpriteNumber()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新

		void UpdateValue(int value);
	};
}

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	Scoreスプライトクラス
	//--------------------------------------------------------------------------------------
	class RankSpriteNumber : public GameObject
	{
		vector<VertexPositionColorTexture> m_vertices;

		shared_ptr<PCTSpriteDraw>m_ptrDraw;

		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		Col4 m_color;
		wstring m_ClearKey;

	public:
		// 構築と破棄
		RankSpriteNumber(
			const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos
		) :
			GameObject(StagePtr),
			m_ClearKey(ClearKey),
			m_Trace(Trace),
			m_StartScale(StartScale),
			m_StartPos(StartPos)
		{
		}
		virtual ~RankSpriteNumber()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新

		Col4 GetColor();
		void SetColor(Col4 color);
		void UpdateValue(int value);
	};
}

	namespace basecross {

		//--------------------------------------------------------------------------------------
		//	Scoreスプライトクラス
		//--------------------------------------------------------------------------------------
		class GaugeSpriteNumber : public GameObject
		{
			vector<VertexPositionColorTexture> m_vertices;

			shared_ptr<PCTSpriteDraw>m_ptrDraw;

			bool m_Trace;
			Vec2 m_StartScale;
			Vec3 m_StartPos;
			wstring m_ClearKey;

		public:
			// 構築と破棄
			GaugeSpriteNumber(
				const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
				const Vec2& StartScale, const Vec3& StartPos
			) :
				GameObject(StagePtr),
				m_ClearKey(ClearKey),
				m_Trace(Trace),
				m_StartScale(StartScale),
				m_StartPos(StartPos)
			{
			}
			virtual ~GaugeSpriteNumber()
			{
			}

			virtual void OnCreate() override; // 初期化
			virtual void OnUpdate() override; // 更新

			void UpdateValue(int value);
		};

	}


	namespace basecross {
		class MiniMapSprite :public GameObject
		{
		protected:
			//画像の表示サイズ
			float m_width;
			float m_heigth;
			int m_layer;
			Vec2 m_size;//画像の大きさ
			shared_ptr<PCTSpriteDraw> m_drawComp;//ドローコンポーネント

		
			wstring m_textureName;//テクスチャの名前

			shared_ptr<Transform> m_trans;

			Vec3 m_pos;
			Vec3 m_rot;
			Col4 m_color;


		public:
			MiniMapSprite(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size, Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), Vec3 rot = Vec3(0.0f, 0.0f, 0.0f), Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f), int layer = 1);//コンストラクタ
			virtual ~MiniMapSprite();//デストラクタ

			virtual void OnCreate()override;//作成
			virtual void OnUpdate()override;//更新

			void SetColor(Col4 coler);//セッター
			void MyDestroy();//自分自身を消す
			Col4 GetColor();//ゲッター

		};
	}


	namespace basecross {
		class GateSprite : public MiniMapSprite
		{
		private:
			//weak_ptr<Poll1> m_parent;
			float m_countTime;
		public:
			GateSprite(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size, Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), Vec3 rot = Vec3(0.0f, 0.0f, 0.0f), Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f), int layer = 1);
			~GateSprite();

			void OnUpdate()override;
		};
	}

	namespace basecross {
		class MiniMapMoveGate :public GameObject
		{
		protected:
			//画像の表示サイズ
			float m_width;
			float m_heigth;
			int m_layer;
			Vec2 m_size;//画像の大きさ

			wstring m_textureName;//テクスチャの名前

			Vec3 m_pos;
			Vec3 m_rot;
			Col4 m_color;

			weak_ptr<Gate> m_parentObj;//元となるオブジェクトを保管する変数

		public:
			MiniMapMoveGate(shared_ptr<Stage>& stagePtr, weak_ptr<Gate> parentObj, wstring textureName, Vec2 size, int layer = 1, Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), Vec3 rot = Vec3(0.0f, 0.0f, 0.0f));//コンストラクタ
			virtual ~MiniMapMoveGate();//デストラクタ

			virtual void OnCreate()override;//作成
			virtual void OnUpdate()override;//更新

		};

	//--------------------------------------------------------------------------------------
	///	                             JumpSprite
	//--------------------------------------------------------------------------------------
	class  JumpSprite : public GameObject {
		shared_ptr<PCTSpriteDraw>PtrDraw;
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		Col4 m_color;
		wstring m_ClearKey;
	
	public:		
		bool m_MoveFlag;
		bool m_DownMoveFlag;
		bool m_UpFlag;
		bool m_DownFlag;
		JumpSprite(const shared_ptr<Stage>& StagePtr, const wstring& ClearKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~JumpSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override;
		//色の取得
		Col4 GetColor();
		void SetColor(Col4 color);
	};
}
		

	//end basecross
