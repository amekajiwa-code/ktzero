#pragma once
#include <chrono>
#include <thread>
#include <Windows.h>
#include <iostream>
#pragma comment(lib, "winmm.lib") //timeGetTime()
class Timer
{
public:
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