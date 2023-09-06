#include "sample.h"

bool  sample::Init()
{
    #pragma region ���ĺ���
    D3D11_BLEND_DESC bsd;
    ZeroMemory(&bsd, sizeof(bsd));
    bsd.RenderTarget[0].BlendEnable = true;
    bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bsd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    bsd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bsd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

    bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    m_pDevice->CreateBlendState(&bsd, &mAlphaBlend);

    TextureManager::GetInstance().Set(m_pDevice, m_pImmediateContext);
    ShaderManager::GetInstance().Set(m_pDevice, m_pImmediateContext);
    #pragma endregion

    #pragma region ����
    mSound = SoundManager::GetInstance().Load(L"res/sound/song_youwillneverknow.ogg");
    mSound->Play(true);
    mSound->VolumeDown();
    mSlashDeath = SoundManager::GetInstance().Load(L"res/sound/death_sword.wav");
    #pragma endregion

    #pragma region ������Ʈ����
    srand(time(NULL));
    mMapObj = new PlaneObject;
    mMapObj->Set(m_pDevice, m_pImmediateContext);
    mMapObj->SetScale(Vector3(static_cast<float>(g_dwWindowWidth), static_cast<float>(g_dwWindowHeight), 1.0f));
    mMapObj->Create(TextureManager::GetInstance(), L"res/background/LastStage.bmp", ShaderManager::GetInstance(), L"Plane.hlsl");

    mFloorObj = new PlaneObject;
    mFloorObj->Set(m_pDevice, m_pImmediateContext);
    mFloorObj->SetPos({ 0.0f, -static_cast<float>(g_dwWindowHeight) + 170.0f, 0.0f });
    mFloorObj->SetScale(Vector3(static_cast<float>(g_dwWindowWidth), 20.0f, 1.0f));
    Vector2 rt = { mFloorObj->m_vPos.mX, mFloorObj->m_vPos.mY};
    mFloorObj->SetRect(rt, mFloorObj->m_vScale.mX * 2.0f, mFloorObj->m_vScale.mY * 2.0f);
    mFloorObj->SetTag("Floor");
    mFloorObj->Create(TextureManager::GetInstance(), L"res/floor.png", ShaderManager::GetInstance(), L"Plane.hlsl");

    mCursorObj = new PlaneObject;
    mCursorObj->Set(m_pDevice, m_pImmediateContext);
    mCursorObj->SetPos({ 0.0f, 0.0f, 0.0f });
    mCursorObj->SetScale(Vector3(25.0f, 25.0f, 1.0f));
    mCursorObj->Create(TextureManager::GetInstance(), L"res/ui/cursor_0.png", ShaderManager::GetInstance(), L"Plane.hlsl");

    mPlayer = new Player;
    mPlayer->Set(m_pDevice, m_pImmediateContext);
    mPlayer->SetPos({ 0.0f, 0.0f, 0.0f });
    mPlayer->SetScale(Vector3(36.0f, 35.0f, 1.0f));
    rt = { mPlayer->m_vPos.mX * 2.0f, mPlayer->m_vPos.mY * 2.0f };
    mPlayer->SetRect(rt, mPlayer->m_vScale.mX * 2.0f, mPlayer->m_vScale.mY * 2.0f);
    mPlayer->Create(TextureManager::GetInstance(), L"res/player/spr_idle/idle_0.png", ShaderManager::GetInstance(), L"Plane.hlsl");

    mEffectObj = new PlaneObject;
    mEffectObj->Set(m_pDevice, m_pImmediateContext);
    mEffectObj->SetPos({ 0.0f, 0.0f, 0.0f });
    mEffectObj->SetScale(Vector3(123.0f, 30.0f, 1.0f));
    mEffectObj->Create(TextureManager::GetInstance(), L"res/effect/spr_master_slash/master_slash_0.png", ShaderManager::GetInstance(), L"Plane.hlsl");

    mJumpObj = new PlaneObject;
    mJumpObj->Set(m_pDevice, m_pImmediateContext);
    mJumpObj->SetPos({ 0.0f, 0.0f, 0.0f });
    mJumpObj->SetScale(Vector3(32.0f, 51.0f, 1.0f));
    mJumpObj->Create(TextureManager::GetInstance(), L"res/effect/spr_jumpcloud/jumpcloud_0.png", ShaderManager::GetInstance(), L"Plane.hlsl");

    for (int iObj = 0; iObj < 10; iObj++)
    {
        Npc* pObj = new Npc;
        pObj->Set(m_pDevice, m_pImmediateContext);
        pObj->SetPos(Vector3(randstep(-600, 600), -500.0f, 0.0f));
        pObj->SetScale(Vector3(30.0f, 36.0f, 1.0f));
        Vector2 rt = { pObj->m_vPos.mX, pObj->m_vPos.mY };
        pObj->SetRect(rt, pObj->m_vScale.mX * 2.0f, pObj->m_vScale.mY * 2.0f);
        pObj->Create(TextureManager::GetInstance(), L"res/npc/Grunt/spr_grunt_idle/grunt_idle_0.png",
            ShaderManager::GetInstance(), L"Plane.hlsl");
        mNpcList.push_back(pObj);
    }
    #pragma endregion

    #pragma region �÷��̾�_�ִϸ��̼�
    const Texture* tex = TextureManager::GetInstance().Load(L"res/player/spr_idle/idle_0.png");
    mPlayer->mIdleList.push_back(tex);
    tex = TextureManager::GetInstance().Load(L"res/player/spr_idle/idle_1.png");
    mPlayer->mIdleList.push_back(tex);
    tex = TextureManager::GetInstance().Load(L"res/player/spr_idle/idle_2.png");
    mPlayer->mIdleList.push_back(tex);
    tex = TextureManager::GetInstance().Load(L"res/player/spr_idle/idle_3.png");
    mPlayer->mIdleList.push_back(tex);
    tex = TextureManager::GetInstance().Load(L"res/player/spr_idle/idle_4.png");
    mPlayer->mIdleList.push_back(tex);
    tex = TextureManager::GetInstance().Load(L"res/player/spr_idle/idle_5.png");
    mPlayer->mIdleList.push_back(tex);
    tex = TextureManager::GetInstance().Load(L"res/player/spr_idle/idle_6.png");
    mPlayer->mIdleList.push_back(tex);
    tex = TextureManager::GetInstance().Load(L"res/player/spr_idle/idle_7.png");
    mPlayer->mIdleList.push_back(tex);
    tex = TextureManager::GetInstance().Load(L"res/player/spr_idle/idle_8.png");
    mPlayer->mIdleList.push_back(tex);
    tex = TextureManager::GetInstance().Load(L"res/player/spr_idle/idle_9.png");
    mPlayer->mIdleList.push_back(tex);
    tex = TextureManager::GetInstance().Load(L"res/player/spr_idle/idle_10.png");
    mPlayer->mIdleList.push_back(tex);

    const Texture* tex1 = TextureManager::GetInstance().Load(L"res/player/spr_run/run_0.png");
    mPlayer->mRunList.push_back(tex1);
    tex1 = TextureManager::GetInstance().Load(L"res/player/spr_run/run_1.png");
    mPlayer->mRunList.push_back(tex1);
    tex1 = TextureManager::GetInstance().Load(L"res/player/spr_run/run_2.png");
    mPlayer->mRunList.push_back(tex1);
    tex1 = TextureManager::GetInstance().Load(L"res/player/spr_run/run_3.png");
    mPlayer->mRunList.push_back(tex1);
    tex1 = TextureManager::GetInstance().Load(L"res/player/spr_run/run_4.png");
    mPlayer->mRunList.push_back(tex1);
    tex1 = TextureManager::GetInstance().Load(L"res/player/spr_run/run_5.png");
    mPlayer->mRunList.push_back(tex1);
    tex1 = TextureManager::GetInstance().Load(L"res/player/spr_run/run_6.png");
    mPlayer->mRunList.push_back(tex1);
    tex1 = TextureManager::GetInstance().Load(L"res/player/spr_run/run_7.png");
    mPlayer->mRunList.push_back(tex1);
    tex1 = TextureManager::GetInstance().Load(L"res/player/spr_run/run_8.png");
    mPlayer->mRunList.push_back(tex1);
    tex1 = TextureManager::GetInstance().Load(L"res/player/spr_run/run_9.png");
    mPlayer->mRunList.push_back(tex1);

    const Texture* tex2 = TextureManager::GetInstance().Load(L"res/player/spr_jump/jump_0.png");
    mPlayer->mJumpList.push_back(tex2);
    tex2 = TextureManager::GetInstance().Load(L"res/player/spr_jump/jump_1.png");
    mPlayer->mJumpList.push_back(tex2);
    tex2 = TextureManager::GetInstance().Load(L"res/player/spr_jump/jump_2.png");
    mPlayer->mJumpList.push_back(tex2);
    tex2 = TextureManager::GetInstance().Load(L"res/player/spr_jump/jump_3.png");
    mPlayer->mJumpList.push_back(tex2);

    const Texture* tex3 = TextureManager::GetInstance().Load(L"res/player/spr_fall/fall_0.png");
    mPlayer->mFallList.push_back(tex3);
    tex3 = TextureManager::GetInstance().Load(L"res/player/spr_fall/fall_1.png");
    mPlayer->mFallList.push_back(tex3);
    tex3 = TextureManager::GetInstance().Load(L"res/player/spr_fall/fall_2.png");
    mPlayer->mFallList.push_back(tex3);
    tex3 = TextureManager::GetInstance().Load(L"res/player/spr_fall/fall_3.png");
    mPlayer->mFallList.push_back(tex3);

    const Texture* tex4 = TextureManager::GetInstance().Load(L"res/player/spr_attack/attack_0.png");
    mPlayer->mAttackList.push_back(tex4);
    tex4 = TextureManager::GetInstance().Load(L"res/player/spr_attack/attack_1.png");
    mPlayer->mAttackList.push_back(tex4);
    tex4 = TextureManager::GetInstance().Load(L"res/player/spr_attack/attack_2.png");
    mPlayer->mAttackList.push_back(tex4);
    tex4 = TextureManager::GetInstance().Load(L"res/player/spr_attack/attack_3.png");
    mPlayer->mAttackList.push_back(tex4);
    tex4 = TextureManager::GetInstance().Load(L"res/player/spr_attack/attack_4.png");
    mPlayer->mAttackList.push_back(tex4);
    tex4 = TextureManager::GetInstance().Load(L"res/player/spr_attack/attack_5.png");
    mPlayer->mAttackList.push_back(tex4);
    tex4 = TextureManager::GetInstance().Load(L"res/player/spr_attack/attack_6.png");
    mPlayer->mAttackList.push_back(tex4);
    #pragma endregion
    
    #pragma region ����Ʈ_�ִϸ��̼�
    const Texture* tex5 = TextureManager::GetInstance().Load(L"res/effect/spr_slash/slash_0.png");
    mEffectList.push_back(tex5);
    tex5 = TextureManager::GetInstance().Load(L"res/effect/spr_slash/slash_1.png");
    mEffectList.push_back(tex5);
    tex5 = TextureManager::GetInstance().Load(L"res/effect/spr_slash/slash_2.png");
    mEffectList.push_back(tex5);
    tex5 = TextureManager::GetInstance().Load(L"res/effect/spr_slash/slash_3.png");
    mEffectList.push_back(tex5);
    tex5 = TextureManager::GetInstance().Load(L"res/effect/spr_slash/slash_4.png");
    mEffectList.push_back(tex5);
    #pragma endregion

#pragma region NPC_�ִϸ��̼�
    for (Npc* npc : mNpcList)
    {
        tex = TextureManager::GetInstance().Load(L"res/npc/Grunt/spr_grunt_idle/grunt_idle_0.png");
        npc->AddAnimationList(NPCState::IDLE, tex);
        tex = TextureManager::GetInstance().Load(L"res/npc/Grunt/spr_grunt_idle/grunt_idle_1.png");
        npc->AddAnimationList(NPCState::IDLE, tex);
        tex = TextureManager::GetInstance().Load(L"res/npc/Grunt/spr_grunt_idle/grunt_idle_2.png");
        npc->AddAnimationList(NPCState::IDLE, tex);
        tex = TextureManager::GetInstance().Load(L"res/npc/Grunt/spr_grunt_idle/grunt_idle_3.png");
        npc->AddAnimationList(NPCState::IDLE, tex);
        tex = TextureManager::GetInstance().Load(L"res/npc/Grunt/spr_grunt_idle/grunt_idle_4.png");
        npc->AddAnimationList(NPCState::IDLE, tex);
        tex = TextureManager::GetInstance().Load(L"res/npc/Grunt/spr_grunt_idle/grunt_idle_5.png");
        npc->AddAnimationList(NPCState::IDLE, tex);
        tex = TextureManager::GetInstance().Load(L"res/npc/Grunt/spr_grunt_idle/grunt_idle_6.png");
        npc->AddAnimationList(NPCState::IDLE, tex);
        tex = TextureManager::GetInstance().Load(L"res/npc/Grunt/spr_grunt_idle/grunt_idle_7.png");
        npc->AddAnimationList(NPCState::IDLE, tex);
    }
#pragma endregion

    #pragma region ��Ʈ
    HRESULT hr;

    if (m_pSwapChain)
    {
        IDXGISurface1* pBackBuffer;
        hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
            (LPVOID*)&pBackBuffer);
        if (SUCCEEDED(hr))
        {
            Writer::GetInstance().Create(pBackBuffer);
        }
        if (pBackBuffer) pBackBuffer->Release();
    }
    #pragma endregion

    //ī�޶����
    mMainCamera.Create(mPlayer->m_vPos, { static_cast<float>(m_dwWindowWidth), static_cast<float>(m_dwWindowHeight) });

    return true;
}
bool  sample::Frame()
{
    curMouse = Input::GetInstance().GetWorldPos(
        { static_cast<float>(g_dwWindowWidth),
        static_cast<float>(g_dwWindowHeight) },
        mMainCamera.mCameraPos);
    mCursorObj->SetPos(curMouse);
    Vector2 rt = { mCursorObj->m_vPos.mX * 2.0f, mCursorObj->m_vPos.mY * 2.0f };
    mCursorObj->SetRect(rt, mCursorObj->m_vScale.mX * 2.0f, mCursorObj->m_vScale.mY * 2.0f);

    mEffectObj->SetPos(mPlayer->m_vPos);
    rt = { mEffectObj->m_vPos.mX, mEffectObj->m_vPos.mY };
    mEffectObj->SetRect(rt, mEffectObj->m_vScale.mX * 2.0f, mEffectObj->m_vScale.mY * 2.0f);

    mPlayer->Frame();
    if (mPlayer->isJump)
    {
        mJumpObj->SetPos(mPlayer->m_vPos);
        mJumpObj->Frame();
    }
    mMapObj->Frame();
    mFloorObj->Frame();
    mCursorObj->Frame();
    mEffectObj->Frame();

    for (auto obj : mNpcList)
    {
        if (obj->m_bDead == false)
        {
            obj->Frame();
            Vector2 rt = { obj->m_vPos.mX, obj->m_vPos.mY };
            obj->SetRect(rt, obj->m_vScale.mX * 2.0f, obj->m_vScale.mY * 2.0f);
        }
    }

    if ((Input::GetInstance().mkeyState[VK_LBUTTON] == 2) &&
        (mPlayer->GetPlayerState() != PlayerState::ATTACK))
    {
        mPlayer->mEffectSound->PlayEffect();
        mPlayer->SetPlayerState(PlayerState::ATTACK);

        // �ٴ� ���� (0��)�� �������� �� curMouse�� ���� ���
        float deltaX = curMouse.mX - mMainCamera.mCameraPos.mX; // X ��ǥ ����
        float deltaY = curMouse.mY - mMainCamera.mCameraPos.mY; // Y ��ǥ ����
        float angleToMouse = atan2(deltaY, deltaX); // ���� ������ ���� ���
        mEffectObj->mRect.SetAngle(RadianToDegree(angleToMouse));
    
        Input::GetInstance().curWorldPos = curMouse;
    }


    if (mPlayer->GetPlayerState() == PlayerState::ATTACK)
    {
        for (auto obj : mNpcList)
        {
            if (obj->m_bDead) continue;

            if (obb.RectToRect(mEffectObj->mRect, obj->mRect))
            {
                obj->m_bDead = true;
                mSlashDeath->Play(false);
            }
        }
    }

    mPlayer->CheckCollision(mFloorObj);
    return true;
}
bool  sample::Render()
{
    m_pImmediateContext->OMSetBlendState(mAlphaBlend, 0, -1);
    mMainCamera.mCameraPos = mPlayer->m_vPos;

    mMapObj->SetMatrix(nullptr, &mMainCamera.mMatView, &mMainCamera.mMatOrthonormalProjection);
    mMapObj->Render();

    mFloorObj->SetMatrix(nullptr, &mMainCamera.mMatView, &mMainCamera.mMatOrthonormalProjection);
    //mFloorObj->Render();

    for (auto obj : mNpcList)
    {
        if (obj->m_bDead) continue;
        obj->SetMatrix(nullptr, &mMainCamera.mMatView, &mMainCamera.mMatOrthonormalProjection);
        obj->Render();
    }

    #pragma region �÷��̾�_����
    mPlayer->SetMatrix(nullptr, &mMainCamera.mMatView, &mMainCamera.mMatOrthonormalProjection);
    mPlayer->PreRender();
    mPlayer->Render();
    mTexList.clear();
    mTexList = mPlayer->GetPlayerAnimation();
    if (!mTexList.empty())
    {
        mTexIndex = (int)(g_GameTimer * 10) % mTexList.size();
        if (mTexList[mTexIndex] != nullptr)
        {
            mTexList[mTexIndex]->Apply(m_pImmediateContext, 0);
        }
    }
    mPlayer->PostRender();
    #pragma endregion

    #pragma region ����Ʈ_����
    if (mPlayer->GetPlayerState() == PlayerState::ATTACK)
    {
        m_pImmediateContext->UpdateSubresource(mEffectObj->m_pVertexBuffer, 0, nullptr, &mEffectObj->m_VertexList.at(0), 0, 0);
        mEffectObj->m_matWorld.ZRotate(DegreeToRadian(mEffectObj->mRect.mAngle));
        mEffectObj->SetMatrix(nullptr, &mMainCamera.mMatView, &mMainCamera.mMatOrthonormalProjection);
        mEffectObj->PreRender();

        if (!mEffectList.empty())
        {
            mEffectIndex = (int)(g_GameTimer * 10 * Timer::GetInstance().mTimeScale) % mEffectList.size();
            if (mEffectList[mEffectIndex] != nullptr)
            {
                mEffectList[mEffectIndex]->Apply(m_pImmediateContext, 0);
            }
        }
        mEffectObj->PostRender();
    }

    if (mPlayer->isJump)
    {
        mJumpObj->Render();
    }
    #pragma endregion

   mCursorObj->SetMatrix(nullptr, &mMainCamera.mMatView, &mMainCamera.mMatOrthonormalProjection);
   mCursorObj->Render();

    return true;
}
bool  sample::Release()
{
    mMapObj->Release();
    delete mMapObj;
    mMapObj = nullptr;

    mPlayer->Release();
    delete mPlayer;
    mPlayer = nullptr;
    
    for (auto obj : mNpcList)
    {
        obj->Release();
        delete obj;
    }
    mNpcList.clear();
    mAlphaBlend->Release();
    return true;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) // ����
{
    sample mySample;
    mySample.SetRegisterClassWindow(hInstance);
    mySample.SetWindow(L"�ƹ��ų�", 1280, 720);
    ::ShowCursor(FALSE);
    mySample.Run();

    return 0;
}