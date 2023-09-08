#include "GameManager.h"
#include "Timer.h"
#include "Writer.h"
#include "Input.h"

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

	if (gameTimer >= MAX_GAME_TIME && (isReplay == false))
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

	if (recordTimer <= (0.01f))
	{
		recordTimer += Timer::GetInstance().mSecondPerFrame;
	}
	else if (isReplay)
	{
		isReplay = record.ReplayPlayer(player);
		for (Npc* npc : npcList)
		{
			record.ReplayNPC(npc);
		}
		recordTimer = 0.0f;
	}
	else if (isRewind)
	{
		auto it = SoundManager::GetInstance().playListMap.find("rewindSound");
		if (it != SoundManager::GetInstance().playListMap.end())
		{
			it->second->Play(false);
			SoundManager::GetInstance().playListMap.erase(it);
		}
		
  		isRewind = record.RewindPlayer(player);
		if (isRewind == false)
		{
			Sound* rewindSound = SoundManager::GetInstance().Load(L"res/sound/Rewind.wav");
			SoundManager::GetInstance().playListMap.insert(make_pair("rewindSound", rewindSound));
			gameTimer = 0.0f;
		}
		for (Npc* npc : npcList)
		{
			record.RewindNPC(npc);
		}
		
		recordTimer = 0.0f;
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
		if (gameEndDelay <= MAX_END_DELAY)
		{
			gameEndDelay += Timer::GetInstance().mSecondPerFrame;
		}
		else {
			fontMSG = L"	 �׷�,\n   �̷��� �ϸ� �ǰ���.";
			isReplay = true;
		}
	}

	if (isLose())
	{
		fontMSG = L"	 �ƴ�...\n   ������ ���� �ž�.\n\n  (Space ���� �����)";
		//Timer::GetInstance().mTimeScale = 0.0f;

		if (Input::GetInstance().mkeyState[VK_SPACE] == static_cast<DWORD>(KeyState::KEY_DOWN))
		{
			Timer::GetInstance().mTimeScale = 10.0f;
			isRewind = true;
		}
	}

	Writer::GetInstance().AddText(fontMSG, static_cast<float>(g_dwWindowHeight / 2) + 80, 200, { 1.0f, 1.0f, 1.0f, 1.0f });

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