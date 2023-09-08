#pragma once
#include "Core.h"
#include "PlaneObject.h"
#include "Player.h"
#include "NPC.h"
#include "OBB.h"
#include "GameManager.h"

class sample : public Core
{
private:
    ID3D11BlendState* mAlphaBlend = nullptr;

    Object* mMapObj = nullptr;
    Player* mPlayer = nullptr;
    Object* mFloorObj = nullptr;
    Object* mCursorObj = nullptr;
    Object* mEffectObj = nullptr;
    vector<Object*> mNpcEffectObjList; //이펙트 오브젝트 배열

    Vector3 curMouse = { 0, 0, 0 };

    int mTexIndex = 0;
    int mEffectIndex = 0;
    int mNpcEffectIndex = 0; // 이펙트 인덱스

    vector<const Texture*>  mTexList;
    vector<Npc*> mNpcList;
    vector<Object*> mFloorList;
    vector<const Texture*>  mEffectList;
    vector<const Texture*>  mNpcEffectList; //스프라이트 배열

    OBB obb;
public:
    bool  Init();
    bool  Frame();
    bool  Render();
    bool  Release();

    sample() {};
    virtual ~sample() {};
};