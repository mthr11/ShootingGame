// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"

class SLaser : public Actor
{
public:
	SLaser(class Game* game, float rotation);

	void UpdateActor(float deltaTime) override;
private:
	class CollisionComponent* mCircle;
};

