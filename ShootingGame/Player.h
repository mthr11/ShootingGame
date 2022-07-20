// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include "SDL.h"

#define STATE_IDLE 1 << 0
#define STATE_LEFT 1 << 1
#define STATE_RIGHT 1 << 2
#define MAX_PLAYER_HEALTH 5

class Player : public Actor
{
public:
	Player(class Game* game);
	~Player();

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	class CollisionComponent* GetCircle() { return mCircle; }
	int GetHealth() { return mHealth; }
	void SetHealth(int health) { mHealth = health; }
private:
	class AnimSpriteComponent* asc;
	class InputComponent* ic;
	class CollisionComponent* mCircle;
	
	std::vector<std::vector<SDL_Texture*>> anims;

	unsigned int pState;	// キャラクターの状態を管理するビット列
	float mLaserCooldown;
	int mHealth;
};

