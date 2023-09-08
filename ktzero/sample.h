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
    vector<Object*> mNpcEffectObjList; //����Ʈ ������Ʈ �迭

    Vector3 curMouse = { 0, 0, 0 };

    int mTexIndex = 0;
    int mEffectIndex = 0;
    int mNpcEffectIndex = 0; // ����Ʈ �ε���

    vector<const Texture*>  mTexList;
    vector<Npc*> mNpcList;
    vector<Object*> mFloorList;
    vector<const Texture*>  mEffectList;
    vector<const Texture*>  mNpcEffectList; //��������Ʈ �迭

    OBB obb;
public:
    bool  Init();
    bool  Frame();
    bool  Render();
    bool  Release();

    sample() {};
    virtual ~sample() {};
};