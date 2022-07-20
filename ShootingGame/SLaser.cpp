// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SLaser.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "Enemy.h"

SLaser::SLaser(Game* game, float rotation)
	:Actor(game)
{
	SetRotation(rotation);

	/* SpriteComponent‚ğ¶¬ */
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/SLaser.png"));

	/* MovetComponent‚ğ¶¬‚µAŒ‚—Í‚ğ‰Á‚¦‚é */
	MoveComponent* mc = new MoveComponent(this);
	mc->AddForce(GetForward() * 3000.0f);

	mCircle = new CollisionComponent(this);
	mCircle->SetRadius(11.0f);
}

void SLaser::UpdateActor(float deltaTime) {
	/* ‰æ–ÊŠO‚Éo‚½‚Ìˆ— */
	if (GetPosition().y < 0.0f) {
		SetState(EDead);
	}

	/* “G‚ÆÕ“Ë‚µ‚½‚©‚Ç‚¤‚© */
	for (auto en : GetGame()->GetEnemys()) {
		if (Intersect(*mCircle, *(en->GetCircle()))) {
			int health = en->GetHealth();
			if (en->GetState() == EActive)
				en->SetHealth(health - 1);
			if (en->GetHealth() <= 0)
				en->SetState(EDead);

			SetState(EDead);
			break;
		}
	}
}
