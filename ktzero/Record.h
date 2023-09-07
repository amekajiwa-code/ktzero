#pragma once
#include <stack>
#include "Player.h"
#include "NPC.h"
#include "Timer.h"

struct PlayerSnapshot {
	Vector3 position;
	PlayerState state;
	bool flip;
};

struct NpcSnapshot {
	Vector3 position;
	NpcState state;
};

class Record
{
private:
	stack<PlayerSnapshot> playerSnap;
	stack<NpcSnapshot> npcSnap;
	stack<Timer> timerSnap;
public:
	void RecordPlayer(Player* player);
	bool RewindPlayer(Player* player);
	void RecordNPC(Npc* npc);
	bool RewindNPC(Npc* npc);
};