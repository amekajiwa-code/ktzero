#pragma once
#include <vector>
#include "Player.h"
#include "NPC.h"
#include "Record.h"

class GameManager
{
private:
	GameManager();
public:
	Player* player;
	vector<Npc*> npcList;
	Record record;
	float recordTimer = 0.0f;
	bool isRewind = false;
	bool isReplay = false;
	const float MAX_GAME_TIME = 60.0f;
	float gameTimer = 0.0f;
	const float MAX_END_DELAY = 1.0f;
	float gameEndDelay = 0.0f;

	virtual ~GameManager();

	static GameManager& GetInstance()
	{
		static GameManager instance;
		return instance;
	}

	bool isWin();
	bool isLose();

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

