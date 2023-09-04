#include "Player.h"
#include "Input.h"
#include "Writer.h"

void Player::MoveX(bool isFlipY)
{
    mPlayerState = PlayerState::RUN;

    if (isFlipY)
    {
        m_vPos.mX -= mSpeed * g_SecondPerFrame;
    }
    else
    {
        m_vPos.mX += mSpeed * g_SecondPerFrame;
    }

    if (isFloor && !isDashSound) {
        mDashSound->Play(false);
        isDashSound = true;
    }
    else if (mDashTimer < MAX_Dash_TIME)
    {
        if (isFlipY)
        {
            m_vPos.mX -= (mSpeed * 0.3f) * g_SecondPerFrame;
        }
        else
        {
            m_vPos.mX += (mSpeed * 0.3f) * g_SecondPerFrame;
        }
        mDashTimer += g_SecondPerFrame;
    }
    else if (isFloor)
    {
        mRunSound->Play(false);
    }  
}

void Player::PlayerMove()
{
    //�÷��̾� ����
    if (Input::GetInstance().mkeyState['W'] == static_cast<DWORD>(KeyState::KEY_DOWN) && isFloor)
    {
        mJumpSound->Play(false);
        isJump = true;
        isLandSound = false;
    }
    if (Input::GetInstance().mkeyState['S'] == static_cast<DWORD>(KeyState::KEY_HOLD) && !isFloor)
    {
        m_vPos.mY -= 800.0f * g_SecondPerFrame;
    }
    if (Input::GetInstance().mkeyState['A'] == static_cast<DWORD>(KeyState::KEY_HOLD))
    {
        isFlipY = true;
        MoveX(isFlipY);
    }
    if (Input::GetInstance().mkeyState['D'] == static_cast<DWORD>(KeyState::KEY_HOLD))
    {
        isFlipY = false;
        MoveX(isFlipY);
    }
    if (Input::GetInstance().mkeyState['A'] == static_cast<DWORD>(KeyState::KEY_UP) || 
        Input::GetInstance().mkeyState['D'] == static_cast<DWORD>(KeyState::KEY_UP))
    {
        mPlayerState = PlayerState::IDLE;
        isDashSound = false;
        mDashTimer = 0.0f;
    }

    if (isJump && (mJumpTimer <= MAX_JUMP_TIME))
    {
        m_vPos.mY += (mPower * 0.7f) * g_SecondPerFrame;
        mJumpTimer += g_SecondPerFrame;
        mPlayerState = PlayerState::JUMP;
    }
    else if (isFloor == false)
    {
        m_vPos.mY -= mGrabity * g_SecondPerFrame;
        mJumpTimer = 0.0f;
        isJump = false;
        mPlayerState = PlayerState::FALL;
    }
    else if (!isLandSound)
    {
            mLandSound->VolumeDown();
            mLandSound->Play(false);
            isLandSound = true; 
    }
    else if (mPlayerState != PlayerState::RUN)
    {
        mPlayerState = PlayerState::IDLE;
    }

    //ī�޶� �̵�
    if (m_vPos.mX < -static_cast<float>(g_dwWindowWidth))
    {
        m_vPos.mX = -static_cast<float>(g_dwWindowWidth);
    }
    if (m_vPos.mY <= -static_cast<float>(g_dwWindowHeight))
    {
        m_vPos.mY = -static_cast<float>(g_dwWindowHeight);
    }
    if (m_vPos.mX > static_cast<float>(g_dwWindowWidth))
    {
        m_vPos.mX = static_cast<float>(g_dwWindowWidth);
    }
    if (m_vPos.mY > static_cast<float>(g_dwWindowHeight))
    {
        m_vPos.mY = static_cast<float>(g_dwWindowHeight);
    }
}

void Player::PlayerAttack()
{
    if (mAttackTimer <= MAX_ATTACK_TIME)
    {
        Vector3 direction = Input::GetInstance().curWorldPos - m_vPos;
        Vector3 NormalX;
        direction.Normalize();

        if (direction.mX < 0)
        {
            isFlipY = true;
            NormalX = { -1.0f, 0.0f, 0.0f };
        }
        else
        {
            isFlipY = false;
            NormalX = { 1.0f, 0.0f, 0.0f };
        }

        if (isFloor && direction.mY < 0.0f)
        {
            mVelocity = NormalX * mPower * g_SecondPerFrame;
        }
        else
        {
            mVelocity = direction * mPower * g_SecondPerFrame;
        }
        m_vPos = m_vPos + mVelocity;
        mAttackTimer += g_SecondPerFrame;  
    }
    else if (mDelayTimer <= MAX_DELAY_TIME)
    {

        if (!isFloor) m_vPos = m_vPos + (mVelocity / 2);
        mDelayTimer += g_SecondPerFrame;
    }
    else
    {
        mAttackTimer = 0.0f;
        mDelayTimer = 0.0f;
        mPlayerState = PlayerState::IDLE;
        return;
    }
 }

bool Player::CheckCollision(Object* other)
{
    if (Player::mRect.ToRect(other->mRect) && other->mTag == "Floor")
    {
        isFloor = true;
        return true;
    }
    else
    {
        isFloor = false;
        return false;
    }
}

vector<const Texture*> Player::GetPlayerAnimation()
{
    switch (mPlayerState)
    {
    case PlayerState::IDLE:
        PlaneObject::SetScale(Vector3(36.0f, 35.0f, 1.0f));
        return mIdleList;
        break;
    case PlayerState::RUN:
        PlaneObject::SetScale(Vector3(44.0f, 32.0f, 1.0f));
        return mRunList;
        break;
    case PlayerState::JUMP:
        PlaneObject::SetScale(Vector3(32.0f, 42.0f, 1.0f));
        return mJumpList;
        break;
    case PlayerState::FALL:
        PlaneObject::SetScale(Vector3(42.0f, 48.0f, 1.0f));
        return mFallList;
        break;
    case PlayerState::ATTACK:
        PlaneObject::SetScale(Vector3(62.0f, 48.0f, 1.0f));
        return mAttackList;
        break;
    default:
        break;
    }
}

bool Player::Init()
{
	return true;
}

bool Player::Frame()
{
    if (mPlayerState == PlayerState::ATTACK)
    {
        PlayerAttack();
    }
    else
    {
        PlayerMove();
    }

#ifdef _DEBUG
    wstring fontFPS;
    switch (mPlayerState)
    {
    case PlayerState::IDLE:
        fontFPS = L"State : Idle";
        break;
    case PlayerState::RUN:
        fontFPS = L"State : Run";
        break;
    case PlayerState::JUMP:
        fontFPS = L"State : Jump";
        break;
    case PlayerState::FALL:
        fontFPS = L"State : Fall";
        break;
    case PlayerState::ATTACK:
        fontFPS = L"State : Attack";
        break;
    default:
        fontFPS = L"State : ";
        break;
    }
    Writer::GetInstance().AddText(fontFPS, 10, 100, { 1.0f, 1.0f, 1.0f, 1.0f });
#endif
    Vector2 rt = { m_vPos.mX, m_vPos.mY };
    SetRect(rt, m_vScale.mX * 2.0f, m_vScale.mY * 2.0f);

    Matrix matScale, matRotation, matTranslate;
    matScale.Scale(m_vScale);
    matRotation.ZRotate(m_vRotation.mZ);
    matTranslate.Translation(m_vPos);
    m_matWorld = matScale * matRotation * matTranslate;

	return true;
}

bool Player::Render()
{
    if (isFlipY)
    {
        m_VertexList[0].t.mX = 1.0f; m_VertexList[0].t.mY = 0.0f;
        m_VertexList[1].t.mX = 0.0f; m_VertexList[1].t.mY = 0.0f;
        m_VertexList[2].t.mX = 1.0f; m_VertexList[2].t.mY = 1.0f;
        m_VertexList[3].t.mX = 1.0f; m_VertexList[3].t.mY = 1.0f;
        m_VertexList[4].t.mX = 0.0f; m_VertexList[4].t.mY = 0.0f;
        m_VertexList[5].t.mX = 0.0f; m_VertexList[5].t.mY = 1.0f;
    }
    else
    {
        m_VertexList[0].t.mX = 0.0f; m_VertexList[0].t.mY = 0.0f;
        m_VertexList[1].t.mX = 1.0f; m_VertexList[1].t.mY = 0.0f;
        m_VertexList[2].t.mX = 0.0f; m_VertexList[2].t.mY = 1.0f;
        m_VertexList[3].t.mX = 0.0f; m_VertexList[3].t.mY = 1.0f;
        m_VertexList[4].t.mX = 1.0f; m_VertexList[4].t.mY = 0.0f;
        m_VertexList[5].t.mX = 1.0f; m_VertexList[5].t.mY = 1.0f;
    }
    m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, 0, nullptr, &m_VertexList.at(0), 0, 0);
	return true;
}

bool Player::Release()
{
	return false;
}