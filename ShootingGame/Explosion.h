// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"

class Explosion : public Actor
{
public:
	Explosion(class Game* game);
	~Explosion();

	void UpdateActor(float deltaTime) override;
private:
	class AnimSpriteComponent* asc;
};

