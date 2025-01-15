/*!
@file FloatCircle.cpp
@brief スプライト用オブジェクトの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void FloatCircle::InitializeVertices()
	{
		// ポリゴンの頂点データ
		m_vertices.clear();
		m_vertices.reserve((m_angles + 1) * 2); // 「円の角」の数(m_angles)×上下(2)（一周回って最後の頂点は最初の頂点と重なるため1セット多く作る）
		for (int i = 0; i <= m_angles; i++)
		{
			Vec3 position; // 頂点座標
			VertexPositionColorTexture vtx; // 1頂点のデータ

			// 上下の頂点の共通データ
			float rad = XMConvertToRadians(360.0f * i / m_angles);
			float u = m_loops.x * static_cast<float>(i) / static_cast<float>(m_angles);
			float v = m_loops.y;

			// 上の円の頂点
			position = Vec3(cosf(rad), 0.0f, sinf(rad)) * m_topRadius + Vec3(0.0f, m_height, 0.0f); // Y座標をm_height分ずらす
			vtx = VertexPositionColorTexture(position, m_topColor, Vec2(u, 0.0f)); // V座標を最小値にする
			m_vertices.push_back(vtx);

			// 下の円の頂点
			position = Vec3(cosf(rad), 0.0f, sinf(rad)) * m_bottomRadius;
			vtx = VertexPositionColorTexture(position, m_bottomColor, Vec2(u, v)); // V座標を最大値にする
			m_vertices.push_back(vtx);
		}

		// 頂点インデックス(頂点をつなげる順番)
		const vector<uint16_t> baseIndices = {
			 2, 1, 0,
			 3, 1, 2,
		};

		//m_indices.clear();
		//m_indices.reserve(m_angles * baseIndices.size());
		for (int i = 0; i < m_angles; i++)
		{
			// baseIndicesの数だけループ
			for (auto baseIndex : baseIndices)
			{
				m_indices.push_back(baseIndex + (2 * i));
			}
		}
	}

	void FloatCircle::OnCreate()
	{
		AddTag(L"FloatCircle");
		InitializeVertices();


		// 頂点データとインデックスを元にポリゴンを生成する
		m_drawComp = AddComponent<BcPCTStaticDraw>();
		m_drawComp->SetOriginalMeshUse(true);
		m_drawComp->CreateOriginalMesh(m_vertices, m_indices);
		//m_drawComp->SetSamplerState(SamplerState::LinearWrap);
		m_drawComp->SetDepthStencilState(DepthStencilState::Read);
		m_drawComp->SetBlendState(BlendState::Additive);

		if (m_textureKeyName.length() > 0)
		{
			m_drawComp->SetTextureResource(m_textureKeyName);
		}
		// アルファ値を反映できるようにする
		SetAlphaActive(true);

		auto col = AddComponent<CollisionObb>();
		col->SetDrawActive(false);
		col->SetFixed(true);

		Mat4x4 spanMat; // モデルとトランスフ ォーム間の差分行列
		spanMat.affineTransformation(
			Vec3(0.7f, 3.0f, 0.7f),//スケーリング
			Vec3(0.0f, 0.0f, 0.0f),//回転の中心
			Vec3(0.0f, 0.0f, 0.0f),//回転のベクトル
			Vec3(0.0f, -1.5f, 0.0f) //移動
			
		);

		m_drawComp->SetMeshToTransformMatrix(spanMat);

	}

	void FloatCircle::OnUpdate()
	{

		if (m_scrollVelocity.length() > 0.0f && m_textureKeyName != L"")
		{
			float delta = App::GetApp()->GetElapsedTime();
			for (auto& vertex : m_vertices)
			{
				vertex.textureCoordinate += m_scrollVelocity * delta;
			}
		}

		if (m_isUpdate)
		{
			m_isUpdate = false;
			InitializeVertices();
		}

		m_drawComp->UpdateVertices(m_vertices);

	}
}

//end basecross
