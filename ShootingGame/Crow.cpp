// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Crow.h"
#include "Game.h"
#include "AnimSpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "ELaser.h"
#include "Explosion.h"
#include "Texture.h"

Crow::Crow(Game* game, Vector2 pos)
	:Enemy(game, pos)
{
	SetSpeed(100.0f);
	SetHealth(MAX_CROW_HEALTH);

	/* SpriteComponent�𐶐� */
	asc = new AnimSpriteComponent(this, 140);
	std::vector<Texture*> anim = {
		game->GetTexture("Assets/Crow/Crow01.png"),
		game->GetTexture("Assets/Crow/Crow02.png"),
		game->GetTexture("Assets/Crow/Crow03.png")
	};
	asc->SetAnimTextures(anim, true);
	asc->SetAnimFPS(12.0f);

	/* MoveComponent�𐶐����A���͂������� */
	mc = new MoveComponent(this);
	mc->SetVelocity(GetRight() * -mSpeed);

	mCircle = new CollisionComponent(this);
	mCircle->SetRadius(12.0f);

	/* Game��mWaveEnemys[0]�ɒǉ� */
	game->AddWaveEnemy(this, 0);
}

Crow::~Crow() {

	/* �����G�t�F�N�g */
	Explosion* ex = new Explosion(GetGame());
	ex->SetPosition(GetPosition());
	ex->SetScale(3.0f);

	GetGame()->RemoveWaveEnemy(this, 0);
}

void Crow::UpdateActor(float deltaTime) {
	Vector2 pos = GetPosition();
	float texWidth = asc->GetTexWidth() * GetScale() / 2;

	/* ��ʒ[�ɓ��B����ƒ��˕Ԃ鏈�� */
	if (pos.x <= texWidth) {
		mc->SetVelocity(GetRight() * mSpeed);
	}
	else if (pos.x >= WINDOW_WIDTH - texWidth) {
		mc->SetVelocity(GetRight() * -mSpeed);
	}

	mLaserCooldown -= deltaTime;

	if (mLaserCooldown <= 0.0f) {
		/* ���[�U�[�𐶐����A�����ʒu��ݒ� */
		ELaser* laser = new ELaser(GetGame(), -GetRotation());
		laser->SetPosition(GetPosition());
		laser->SetScale(0.75f);

		mLaserCooldown = 0.8f;	// ���[�U�[�̃N�[���^�C�������Z�b�g
	}
}
