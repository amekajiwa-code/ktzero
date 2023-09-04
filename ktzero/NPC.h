#pragma once
#include "PlaneObject.h"

class Npc : public PlaneObject
{
	Vector3 m_vDirection = { 0.0f, 0.0f, 0.0f };
public:
	void Move();
	virtual bool Frame();

	Npc();
	virtual ~Npc();
};

