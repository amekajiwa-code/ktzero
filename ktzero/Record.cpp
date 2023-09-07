#include "Record.h"
#include "Input.h"

void Record::RecordPlayer(Player* player)
{
	PlayerSnapshot pss;
	pss.position = player->m_vPos;
	pss.state = player->GetPlayerState();
	pss.flip = player->GetFlip();
	playerSnap.push(pss);
}

void Record::RecordNPC(Npc* npc)
{
	NpcSnapshot nss;
	nss.position = npc->m_vPos;
	nss.state = npc->GetNPCState();
	npcSnap.push(nss);
}

bool Record::RewindPlayer(Player* player)
{
	if (playerSnap.empty())
	{
		Timer::GetInstance().mTimeScale = 1.0f;
		Timer::GetInstance().mGameTimer = 0.0f;
		return false;
	}
	else
	{
		PlayerSnapshot pss = playerSnap.top();
		playerSnap.pop();
		player->m_vPos = pss.position;
		player->SetPlayerState(pss.state);
		player->SetFlip(pss.flip);
		return true;
	}
}