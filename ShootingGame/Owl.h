// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Enemy.h"

#define MAX_OWL_HEALTH 100

class Owl : public Enemy
{
public:
	Owl(class Game* game, Vector2 pos);
	~Owl();

	void UpdateActor(float deltaTime) override;
};

