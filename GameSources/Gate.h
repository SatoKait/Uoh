#pragma once
#include "stdafx.h"

namespace basecross {
    //--------------------------------------------------------------------------------------
    //　　Gateクラス	
    //--------------------------------------------------------------------------------------
    class Gate : public GameObject 
    { 
        shared_ptr<Transform> m_Trans;
        shared_ptr<PNTStaticDraw>m_ptrDraw;
        shared_ptr<CollisionObb> m_col;
        int id;                  // 旗門のID
        int remainingPasses;     // 残り回数
        bool isActive;           // 現在アクティブかどうか
        bool m_DrawFlag;
        bool m_EndFlag;
        Vec3 m_Scale;

    public:      
        Vec3 m_Pos;              // 旗門の位置情報
        int flag;                // 下がるまでの回数フラグ
        bool hasPassed;
        bool m_RandFlag;
        bool m_DownFlag;
        bool m_ChangeFlag;
        bool m_ChangeFlag2;
        bool m_ChangeFlag3;

        Gate::Gate(const shared_ptr<Stage>& StagePtr, int id, int flag, Vec3 Scale
        ) :
            GameObject(StagePtr),
            id(id),
            flag(flag),
            remainingPasses(flag),
            isActive(true),
            m_Pos(0.0f,0.0f,0.0f),
            m_Scale(Scale),
            hasPassed(false),
            m_DrawFlag(true),
            m_ChangeFlag(false),
            m_EndFlag(false),
            m_RandFlag(false),
            m_DownFlag(false)
        {
        }
        void OnCreate();         // 初期化処理
        void OnUpdate();         // 毎フレームの更新処理
        void handleFlag(float delta);
        void handleFlag1(float delta);
        void handleFlag2(float delta);
        void handleFlag3(float delta);
    };
}

