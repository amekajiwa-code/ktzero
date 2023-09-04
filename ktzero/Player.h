#pragma once
#include "PlaneObject.h"
#include "SoundManager.h"

enum class PlayerState
{
	IDLE,
	RUN,
	JUMP,
	FALL,
	ATTACK,
};

class Player : public PlaneObject
{
public:
	//행동 관련
	const float MAX_JUMP_TIME = 0.3f;
	float mJumpTimer = 0.0f;
	const float MAX_ATTACK_TIME = 0.2f;
	float mAttackTimer = 0.0f;
	const float MAX_DELAY_TIME = 0.2f;
	float mDelayTimer = 0.0f;
	const float mSpeed = 600.0f;
	const float mPower = 800;
	const float mGrabity = 9.81f * 50.0f;
	Vector3 mVelocity;
	bool isFloor;
	bool isJump;
	bool isFlipY;
	PlayerState mPlayerState;
	//사운드
	Sound* mJumpSound = SoundManager::GetInstance().Load(L"res/sound/player_jump.wav");
	Sound* mLandSound = SoundManager::GetInstance().Load(L"res/sound/player_land.wav");
	bool isLandSound;
	Sound* mDashSound = SoundManager::GetInstance().Load(L"res/sound/player_prerun.wav");
	bool isDashSound;
	float mDashTimer = 0.0f;
	const float MAX_Dash_TIME = 0.3f;
	Sound* mRunSound = SoundManager::GetInstance().Load(L"res/sound/player_running_2.wav");
	//이펙트 스프라이트
	
public:
	Sound* mEffectSound = SoundManager::GetInstance().Load(L"res/sound/slash_1.wav");

	void PlayerMove();
	void MoveX(bool isFlipY);

	vector<const Texture*>  mIdleList = vector<const Texture*>();
	vector<const Texture*>  mRunList = vector<const Texture*>();
	vector<const Texture*>  mJumpList = vector<const Texture*>();
	vector<const Texture*>  mFallList = vector<const Texture*>();
	vector<const Texture*>  mAttackList = vector<const Texture*>();

	//vector<std::pair<PlayerState, const Texture*>>; <---수정예정

	bool CheckCollision(Object* other);
	vector<const Texture*> GetPlayerAnimation();
	void PlayerAttack();

	PlayerState GetPlayerState()
	{
		return mPlayerState;
	}
	void SetPlayerState(PlayerState state)
	{
		mPlayerState = state;
	}

	bool GetFlip() { return isFlipY; }

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

