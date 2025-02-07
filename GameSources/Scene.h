/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase {
	public:
		int m_Score;
		int m_Score2;
		int m_Point; 
		int m_Point2;
		int m_GoalScore;


		//--------------------------------------------------------------------------------------
		 /*!
		@brief リソースの追加
		@return	リソースのファイルの追加をする
		*/
		//--------------------------------------------------------------------------------------
		void CreateResourses();

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		Scene(
		) :
			SceneBase(),
			m_Score(0),
			m_Score2(0),
			m_Point(0),
			m_Point2(0),
			m_GoalScore(10000)
		{}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		// スコアをAdd
		int SetScore(int score) {
		  return	m_Score = score;
		}

		// スコアを足す
		void AddScore(int score) {
			m_Score += score;
		}

		// スコアを取得する
		int GetScore() {
			return m_Score;
		}

		// スコアをAdd
		int SetScore2(int score) {
			return	m_Score2 = score;
		}

		// スコアを足す
		void AddScore2(int score) {
			m_Score2 += score;
		}
		// スコアを取得する
		int GetScore2() {
			return m_Score2;
		}

		// ポイントをAdd
		int SetPoint(int point) {
			return	m_Point = point;
		}

		// ポイントを足す
		void AddPoint(int point) {
			m_Point += point;
		}

		// ポイントを取得する
		int GetPoint() {
			return m_Point;
		}

		// ポイントをAdd
		int SetPoint2(int point) {
			return	m_Point2 = point;
		}

		// ポイントを足す
		void AddPoint2(int point) {
			m_Point2 += point;
		}

		// ポイントを取得する
		int GetPoint2() {
			return m_Point2;
		}

		// ポイントを取得する
		int GetGoalScore() {
			return m_GoalScore;
		}
	};
}

//end basecross
