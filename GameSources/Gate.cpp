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

        auto m_ptrDraw = AddComponent<PNTStaticDraw>();
        m_ptrDraw->SetMeshResource(L"POLL_2_MESH");
        m_ptrDraw->SetTextureResource(m_ResKey);
        m_ptrDraw->SetMeshToTransformMatrix(spanMat);

    }

    void Gate::OnUpdate()
    {
        float delta = App::GetApp()->GetElapsedTime();

        // 旗門を下げる処理
        if (flag == 0 && m_Pos.y >= -2.0f && m_DownFlag ) {
            m_Pos.y -= Speed * delta;
            m_Trans->SetPosition(m_Pos);
        }

        // 旗門が沈んだらランダムに新しいフラグを設定
        if (flag == 0 && m_Pos.y <= -2.0f && !m_RandFlag) {
            flag = rand() % 4; // 0〜3のランダムな値を生成
            m_RandFlag = true;
        }

        // フラグごとの処理
        switch (flag) {
        case 0:
            handleFlag(delta); // 再びランダム化を許可
            break;
        case 1:
            handleFlag1(delta);
            break;
        case 2:
            handleFlag2(delta);
            break;
        case 3:
           handleFlag3(delta);
            break;
        }
    }

    void Gate::handleFlag(float delta) {
        if (!m_EndFlag) {
            m_Pos = Vec3(0.0f, DrawPos, 20.0f);
            m_EndFlag = true;
        }
        if (m_Pos.y <= 5.55f && m_EndFlag && !m_DownFlag) {
            m_Pos.y += Speed * delta;
            m_Trans->SetPosition(m_Pos);
            m_ChangeUpDown = true;
        }
        else if (m_Pos.y >= 5.55f) {
            m_ChangeFlag = false;
            //m_EndFlag = false;
        }
        else if (m_Pos.y >= -2.0f && m_DownFlag)
        {
            m_DeleteFlag = true;
        }
    }


    void Gate::handleFlag1(float delta) {
        if (!m_EndFlag) {
            m_Pos = Vec3(20.0f, DrawPos, 0.0f);
            m_EndFlag = true;
        }
        if (m_Pos.y <= 5.55f && m_EndFlag && !m_DownFlag) {
            m_Pos.y += Speed * delta;
            m_Trans->SetPosition(m_Pos);
        }
        else if (m_Pos.y >= 5.55f ) {
            m_ChangeFlag1 = false;
            //m_EndFlag = false;
        }
        else if (m_Pos.y >= -2.0f && m_DownFlag)
        {
            m_DeleteFlag = true;
        }

    }

    void Gate::handleFlag2(float delta) {
        if (!m_EndFlag) {
            m_Pos = Vec3(0.0f, DrawPos, -20.0f);
            m_EndFlag = true;
        }
        if (m_Pos.y <= 5.55f && m_EndFlag && !m_DownFlag) {
            m_Pos.y += Speed * delta;
            m_Trans->SetPosition(m_Pos);
        }
        else if (m_Pos.y >= 5.55f) {
            m_ChangeFlag2 = false;
            //m_EndFlag = false;
        }
        else if (m_Pos.y >= -2.0f && m_DownFlag)
        {
            m_DeleteFlag = true;
        }

    }

    void Gate::handleFlag3(float delta) {
        if (!m_EndFlag) {
            m_Pos = Vec3(-20.0f, DrawPos, 0.0f);
            m_EndFlag = true;
        }
        if (m_Pos.y <= 5.55f && m_EndFlag && !m_DownFlag) {
            m_Pos.y += Speed * delta;
            m_Trans->SetPosition(m_Pos);
        }
        else if (m_Pos.y >= 5.55f ) {
            m_ChangeFlag3 = false;
            //m_EndFlag = false;
        }
        else if (m_Pos.y >= -2.0f && m_DownFlag)
        {
            m_DeleteFlag = true;
        }
    }
}