#include "GameManager.h"
#include "Timer.h"
#include "Writer.h"

bool GameManager::isWin()
{
	bool isAlive = false;
	for (Npc* npc : npcList)
	{
		if (npc->m_bDead == false)
		{
			isAlive = true;
		}
	}

	if (isAlive == false)
	{
		return true;
	}

	return false;
}

bool GameManager::isLose()
{
	if (player->m_bDead) {
		return true;
	}

	if (gameTimer >= MAX_GAME_TIME)
	{
		return true;
	}
	return false;
}

bool GameManager::Init()
{
	return false;
}

bool GameManager::Frame()
{
	if (gameTimer <= MAX_GAME_TIME)
	{
		gameTimer += Timer::GetInstance().mSecondPerFrame;
	}

	if (recordTimer <= (0.016f))
	{
		recordTimer += Timer::GetInstance().mSecondPerFrame;
	}
	else if (isRewind)
	{
		for (Npc* npc : npcList)
		{
			record.RewindNPC(npc);
		}
		isRewind = record.RewindPlayer(player);
		
		if (isRewind == false) gameTimer = 0.0f;
	}
	else
	{
		for (Npc* npc : npcList)
		{
			record.RecordNPC(npc);
		}
		record.RecordPlayer(player);

		recordTimer = 0.0f;
	}

	wstring fontMSG;

	if (isWin())
	{
		fontMSG = L"그래, 이렇게 하면 되겠지.";
		Timer::GetInstance().mTimeScale = 0.0f;
	}

	if (isLose())
	{
		fontMSG = L"아니... 통하지 않을 거야.";
		Timer::GetInstance().mTimeScale = 1.0f;
		isRewind = true;
	}

	Writer::GetInstance().AddText(fontMSG, 400, 200, { 1.0f, 1.0f, 1.0f, 1.0f });

	return true;
}

bool GameManager::Render()
{
	return false;
}

bool GameManager::Release()
{
	return false;
}

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}