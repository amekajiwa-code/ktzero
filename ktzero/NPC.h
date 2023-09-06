#pragma once
#include "PlaneObject.h"

enum class NPCState
{
	IDLE,
	RUN,
	ATTACK,
	DEAD,
};

class Npc : public PlaneObject
{
private:
	Vector3 m_vDirection = { 0.0f, 0.0f, 0.0f };
	NPCState mNPCState;
	vector<pair<NPCState, const Texture*>> mAniList;
	int mAniCount = 0;
	float mAniTimer = 0.0f;
public:
	Npc();
	virtual ~Npc();

	NPCState GetNPCState();
	void SetNPCState(NPCState state);
	vector<const Texture*> GetAnimationList(NPCState state);
	void AddAnimationList(NPCState state, const Texture* texture);

	void Move();

	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

