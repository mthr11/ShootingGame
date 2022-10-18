// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Owl.h"
#include "Game.h"
#include "AnimSpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "ELaser.h"
#include "Explosion.h"
#include "Texture.h"

Owl::Owl(Game* game, Vector2 pos)
	:Enemy(game, pos)
{
	SetSpeed(100.0f);
	SetHealth(MAX_OWL_HEALTH);

	/* SpriteComponentを生成 */
	asc = new AnimSpriteComponent(this, 140);
	std::vector<Texture*> anim = {
		game->GetTexture("Assets/Owl/OwlHovering01.png"),
		game->GetTexture("Assets/Owl/OwlHovering02.png"),
		game->GetTexture("Assets/Owl/OwlHovering03.png"),
		game->GetTexture("Assets/Owl/OwlHovering04.png"),
	};
	asc->SetAnimTextures(anim, true);
	asc->SetAnimFPS(12.0f);

	/* MoveComponentを生成し、撃力を加える */
	mc = new MoveComponent(this);
	mc->SetVelocity(GetForward() * -mSpeed);

	mCircle = new CollisionComponent(this);
	mCircle->SetRadius(20.0f);

	/* GameのmWaveEnemys[1]に追加 */
	game->AddWaveEnemy(this, 1);
	game->SetBossEnemy(this);
}

Owl::~Owl() {
	/* 爆発エフェクト */
	Explosion* ex = new Explosion(GetGame());
	ex->SetPosition(GetPosition());
	ex->SetScale(5.0f);

	GetGame()->RemoveWaveEnemy(this, 1);
}

void Owl::UpdateActor(float deltaTime) {
	Vector2 pos = GetPosition();
	float texWidth = asc->GetTexWidth() * GetScale();

	if (GetState() == ESpawn) {
		if (pos.y >= 100.0f) {
			mc->SetVelocity(GetRight() * mSpeed);
			//mc->SetVelocity(Vector2::Zero);	// デバッグ用
			SetState(EActive);
		}
	}
	else if (GetState() == EActive) {
		/* 画面端に到達すると跳ね返る処理 */
		if (pos.x <= texWidth / 2.0f) {
			mc->SetVelocity(GetRight() * mSpeed);
		}
		else if (pos.x >= WINDOW_WIDTH - texWidth / 2.0f) {
			mc->SetVelocity(GetRight() * -mSpeed);
		}

		mLaserCooldown -= deltaTime;
		
		if (mLaserCooldown <= 0.0f) {
			/* レーザーを生成 */
			int numLaser = 10;
			for (int i = 0; i < numLaser; i++) {
				ELaser* laser = new ELaser(GetGame(), Math::ToRadians(-30.0f - 120.0f / (numLaser - 1) * i));
				laser->SetPosition(GetPosition());
				laser->SetScale(0.75f);
			}

			mLaserCooldown = 1.0f;	// レーザーのクールタイムをリセット
		}
	}
}
