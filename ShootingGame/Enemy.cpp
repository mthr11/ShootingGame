// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* game, Vector2 pos)
	:Actor(game)
	, asc(nullptr)
	, mc(nullptr)
	, mCircle(nullptr)
	, mSpeed(0.0f)
	, mLaserCooldown(0.0f)
	, mHealth(1)
{
	/* ‰ŠúˆÊ’u‚ðÝ’è */
	SetPosition(pos);
	SetRotation(Math::PiOver2);

	/* Game‚ÌmEnemys‚É’Ç‰Á */
	game->AddEnemy(this);
}

Enemy::~Enemy() {
	GetGame()->RemoveEnemy(this);
}
