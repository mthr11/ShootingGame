// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Enemy.h"

#define MAX_CROW_HEALTH 1

class Crow : public Enemy
{
public:
	Crow(class Game* game, Vector2 pos);
	~Crow();

	void UpdateActor(float deltaTime) override;
};

