#pragma once
#include "Core.h"
#include "PlaneObject.h"
#include "Player.h"
#include "NPC.h"
#include "OBB.h"

class sample : public Core
{
private:
    ID3D11BlendState* mAlphaBlend = nullptr;

    Object* mMapObj = nullptr;
    Player* mPlayer = nullptr;
    Object* mFloorObj = nullptr;
    Object* mCursorObj = nullptr;
    Object* mEffectObj = nullptr;
    Object* mJumpObj = nullptr;

    Vector3 curMouse = { 0, 0, 0 };

    int mTexIndex = 0;
    int mEffectIndex = 0;
    int mJumpIndex = 0;

    vector<const Texture*>  mTexList;
    vector<Npc*> mNpcList;
    vector<Object*> mFloorList;
    vector<const Texture*>  mEffectList;

    OBB obb;
public:
    bool  Init();
    bool  Frame();
    bool  Render();
    bool  Release();

    sample() {};
    virtual ~sample() {};
};