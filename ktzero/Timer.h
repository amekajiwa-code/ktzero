#pragma once
#include <chrono>
#include <thread>
#include <Windows.h>
#include <iostream>
#pragma comment(lib, "winmm.lib") //timeGetTime()
class Timer
{
private:
	Timer() {}
public:
	virtual ~Timer() {}

	static Timer& GetInstance()
	{
		static Timer instance;
		return instance;
	}
	float mTimeScale = 1.0f;
	float mGameTimer;
	float mSecondPerFrame;
	std::chrono::high_resolution_clock::time_point mBeforeTime;
	float mFramePerSecond;
	int mFPS;
public:
	int		GetFPS();
public:
	bool	Init();		// �ʱ�ȭ �۾�
	bool	Frame();	// �ǽð� ���
	bool	Render();	// �ǽð� ������, ��ο�
	bool	Release();	// ��ü�� �Ҹ� �۾�
};