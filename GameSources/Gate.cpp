/*!
@file Score.cpp
@brief スコアの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

    void Gate::OnCreate() 
    {
        AddTag(L"Gate");
        m_Trans = GetComponent<Transform>();
        m_Trans->SetPosition(m_Pos);
        m_Trans->SetScale(m_Scale);

        remainingPasses = flag;  // フラグに基づいて初期化
        isActive = true;         // アクティブ状態に設定
        
        m_col = AddComponent<CollisionObb>();
        m_col->SetDrawActive(m_DrawFlag);
        m_col->SetFixed(true);
        m_col->SetSleepActive(true);
        m_col->GetAfterCollision();
        m_col->SetAfterCollision(AfterCollision::None);

        Mat4x4 spanMat; // モデルとトランスフ ォーム間の差分行列
        spanMat.affineTransformation(
            Vec3(0.02f, 0.0405f, 0.25f),//スケーリング
            Vec3(0.0f, 0.0f, 0.0f),//回転の中心
            Vec3(0.0f, 0.0f, 0.0f),//回転のベクトル
            Vec3(0.0f, -2.6f, -0.5f) //移動
        );
        //影をつける（シャドウマップを描画する）
        auto ptrShadow = AddComponent<Shadowmap>();
        //影の形（メッシュ）を設定
        //ptrShadow->SetMeshResource(L"BED_MESH");
        ptrShadow->SetMeshToTransformMatrix(spanMat);

        m_ptrDraw = AddComponent<BcPNTStaticDraw>();
        m_ptrDraw->SetMeshResource(L"POLL_2_MESH");
        m_ptrDraw->SetTextureResource(L"POLL2_TX");
        m_ptrDraw->SetMeshToTransformMatrix(spanMat);

    }

    void Gate::OnUpdate(bool hasPassed)
    {
        if (hasPassed) {
            pass();  // 通過処理
        }
    }

    void Gate::pass()
    {
        switch (flag)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            handlePass();
            break;
        }
    }

    void Gate::handlePass() {
        remainingPasses--;
        
        if (remainingPasses <= 0)
        {
            respawn();
        }
    }

    void Gate::respawn()
    {
        remainingPasses = flag;
        isActive = true;

        m_Pos = Vec3(rand() % 10, 0.0f, rand() % 10);  // 例: X, Z 座標をランダムに設定
        m_Trans->SetPosition(m_Pos);
    }
}