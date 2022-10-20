// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "ELaser.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "Player.h"
#include "SceneManager.h"
#include "Scene.h"

ELaser::ELaser(Game* game, float rotation)
	:Actor(game)
{
	SetRotation(rotation);

	/* SpriteComponent‚ð¶¬ */
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/ELaser.png"));

	/* MovetComponent‚ð¶¬‚µAŒ‚—Í‚ð‰Á‚¦‚é */
	MoveComponent* mc = new MoveComponent(this);
	mc->AddForce(GetForward() * 1000.0f);

	mCircle = new CollisionComponent(this);
	mCircle->SetRadius(11.0f);
}

void ELaser::UpdateActor(float deltaTime) {
	/* ‰æ–ÊŠO‚Éo‚½Žž‚Ìˆ— */
	if (GetPosition().y > WINDOW_HEIGHT || GetPosition().x < 0.0f || WINDOW_WIDTH < GetPosition().x) {
		SetState(EDead);
	}

	/* Player‚ÆÕ“Ë‚µ‚½‚©‚Ç‚¤‚© */
	if (GetGame()->GetSceneManager()->GetScene()->GetName() == "Gameplay") {
		Player* p = GetGame()->GetPlayer();
		if (Intersect(*mCircle, *(p->GetCircle()))) {
			int health = p->GetHealth();
			if (health > 0)
				p->SetHealth(health - 1);
			SetState(EDead);
		}
	}
}
