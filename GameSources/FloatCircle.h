/*!
@file FloatCircle.h
@brief スプライト表示用オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class FloatCircle : public GameObject
	{
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;
		shared_ptr<BcPCTStaticDraw> m_drawComp;
		

		float m_height;
		float m_topRadius;
		float m_bottomRadius;
		int m_angles;
		Vec2 m_loops;
		Col4 m_topColor;
		Col4 m_bottomColor;
		wstring m_textureKeyName;
		Vec2 m_scrollVelocity;

		bool m_isUpdate;

	protected:
		void InitializeVertices();

	public:		
		int m_next;
		int m_ComboCount;

		FloatCircle(const std::shared_ptr<Stage>& stage) :
			FloatCircle(stage, 36)
		{
		}

		FloatCircle(const std::shared_ptr<Stage>& stage, int angles) :
			FloatCircle(stage, L"", angles)
		{
		}

		FloatCircle(const std::shared_ptr<Stage>& stage, const std::wstring& textureKeyName, int angles = 36) :
			GameObject(stage),
			m_height(1.0f),
			m_topRadius(0.5f),
			m_bottomRadius(0.5f),
			m_angles(angles),
			m_loops(1.0f, 1.0f),
			m_topColor(1.0f, 1.0f, 1.0f, 1.0f),
			m_bottomColor(1.0f, 1.0f, 1.0f, 1.0f),
			m_textureKeyName(textureKeyName),
			m_scrollVelocity(0.0f),
			m_isUpdate(false),
			m_next(1)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;

		float GetBottomR()const
		{
			return m_bottomRadius;
		}

		void SetScrollPerSecond(const Vec2& velocity)
		{
			m_scrollVelocity = velocity;
			m_scrollVelocity.y *= -1.0f;
		}

		void SetScrollPerSecond(float u, float v)
		{
			SetScrollPerSecond({ u, v });
		}

		void SetHeight(float height)
		{
			m_isUpdate = true;
			m_height = height;
		}

		void SetRadius(float radius)
		{
			m_isUpdate = true;
			m_bottomRadius = m_topRadius = radius;
		}

		void SetTopRadius(float radius)
		{
			m_isUpdate = true;
			m_topRadius = radius;
		}

		void SetBottomRadius(float radius)
		{
			m_isUpdate = true;
			m_bottomRadius = radius;
		}

		void SetColor(const Col4& color)
		{
			m_isUpdate = true;
			m_bottomColor = m_topColor = color;
		}

		void SetColor(float red, float green, float blue, float alpha = 1.0f)
		{
			SetColor(Col4(red, green, blue, alpha));
		}

		void SetTopColor(const Col4& color)
		{
			m_isUpdate = true;
			m_topColor = color;
		}

		void SetTopColor(float red, float green, float blue, float alpha = 1.0f)
		{
			SetTopColor(Col4(red, green, blue, alpha));
		}

		void SetBottomColor(const Col4& color)
		{
			m_isUpdate = true;
			m_bottomColor = color;
		}

		void SetBottomColor(float red, float green, float blue, float alpha = 1.0f)
		{
			SetBottomColor(Col4(red, green, blue, alpha));
		}

		void SetLoops(const Vec2& uv)
		{
			m_isUpdate = true;
			m_loops = uv;
		}

		void SetBlendState(BlendState state)
		{
			m_drawComp->SetBlendState(state);
		}
	};

}
//end basecross
