// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy(class Game* game, Vector2 pos);
	virtual ~Enemy();

	class CollisionComponent* GetCircle() { return mCircle; }
	float GetSpeed() { return mSpeed; }
	void SetSpeed(float speed) { mSpeed = speed; }
	int GetHealth() { return mHealth; }
	void SetHealth(int health) { mHealth = health; }
protected:
	class AnimSpriteComponent* asc;
	class MoveComponent* mc;
	class CollisionComponent* mCircle;

	float mSpeed;
	float mLaserCooldown;
	int mHealth;
};

