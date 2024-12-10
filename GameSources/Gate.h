#pragma once
#include "stdafx.h"

namespace basecross {
    //--------------------------------------------------------------------------------------
    //　　Gateクラス	
    //--------------------------------------------------------------------------------------
    class Gate : public GameObject 
    { 
        shared_ptr<Transform> m_Trans;
        shared_ptr<BcPNTStaticDraw>m_ptrDraw;
        shared_ptr<CollisionObb> m_col;
        int id;                  // 旗門のID
        int flag;                // 下がるまでの回数フラグ
        int remainingPasses;     // 残り回数
        bool isActive;           // 現在アクティブかどうか
        bool m_DrawFlag;
        Vec3 m_Pos;              // 旗門の位置情報
        Vec3 m_Scale;

    public:
        bool hasPassed;

        Gate::Gate(const shared_ptr<Stage>& StagePtr, int id, int flag, Vec3 Position, Vec3 Scale
        ) :
            GameObject(StagePtr),
            id(id),
            flag(flag),
            remainingPasses(flag),
            isActive(true),
            m_Pos(Position),
            m_Scale(Scale),
            hasPassed(false),
            m_DrawFlag(true)
        {
        }
        void OnCreate();         // 初期化処理
        void OnUpdate(bool hasPassed);         // 毎フレームの更新処理
        void pass();             // 通過処理
        void handlePass();       // 通過処理の共通ロジック
        void respawn();          // リスポーン処理
    };
}

