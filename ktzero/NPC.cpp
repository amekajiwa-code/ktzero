#include "NPC.h"
#include "Timer.h"

void Npc::Move()
{
	Vector3 vVelocity = m_vDirection * 300.0f * Timer::GetInstance().mSecondPerFrame * Timer::GetInstance().mTimeScale;
	m_vPos.mX = m_vPos.mX + vVelocity.mX;

	if (m_vPos.mX < -static_cast<float>(g_dwWindowWidth))
	{
		m_vDirection.mX *= -1.0f;
		m_vPos.mX = -static_cast<float>(g_dwWindowWidth);
	}
	if (m_vPos.mY < -static_cast<float>(g_dwWindowHeight))
	{
		m_vDirection.mY *= -1.0f;
		m_vPos.mY = -static_cast<float>(g_dwWindowHeight);
	}
	if (m_vPos.mX > static_cast<float>(g_dwWindowWidth))
	{
		m_vDirection.mX *= -1.0f;
		m_vPos.mX = static_cast<float>(g_dwWindowWidth);
	}
	if (m_vPos.mY > static_cast<float>(g_dwWindowHeight))
	{
		m_vDirection.mY *= -1.0f;
		m_vPos.mY = static_cast<float>(g_dwWindowHeight);
	}

};

bool Npc::Init()
{
	return true;
}

bool Npc::Frame()
{
	switch(mNPCState)
	{
	case NPCState::IDLE:
		break;
	case NPCState::RUN:
		Move();
		break;
	case NPCState::ATTACK:
		break;
	case NPCState::DEAD:
		break;
	default:
		break;
	}

	Matrix matScale, matRotation, matTranslate;
	matScale.Scale(m_vScale);
	matRotation.ZRotate(m_vRotation.mZ);
	matTranslate.Translation(m_vPos);
	m_matWorld = matScale * matRotation * matTranslate;

	return true;
}

bool Npc::Render()
{
	PlaneObject::PreRender();

	if (!mAniList.empty())
	{
		vector<const Texture*> texList = GetAnimationList(mNPCState);

		if (mAniTimer < 0.1f)
		{
			mAniTimer += Timer::GetInstance().mSecondPerFrame * Timer::GetInstance().mTimeScale;
		}
		else
		{
			++mAniCount;
			mAniTimer = 0.0f;
		}

		if (mAniCount >= texList.size()) mAniCount = 0;
		else texList[mAniCount]->Apply(m_pImmediateContext, 0);
	}
	PlaneObject::PostRender();

	return true;
}


bool Npc::Release()
{
	return false;
}

NPCState Npc::GetNPCState()
{
	return mNPCState;
}

void Npc::SetNPCState(NPCState state)
{
	mNPCState = state;
}

vector<const Texture*> Npc::GetAnimationList(NPCState state)
{	
	vector<const Texture*> texList;

	for (auto it = mAniList.begin(); it != mAniList.end(); ++it)
	{
		if (it->first == state) {
			texList.push_back(it->second);
		}
	}

	return texList;
}

void Npc::AddAnimationList(NPCState state, const Texture* texture)
{
	mAniList.push_back(make_pair(state, texture));
}

Npc::Npc()
{
	m_vDirection = { randstep(-1, +1), randstep(-1, +1), 0 };
}

Npc::~Npc()
{
	//something cool code~!
}