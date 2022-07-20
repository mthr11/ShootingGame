// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Player.h"
#include "Game.h"
#include "AnimSpriteComponent.h"
#include "InputComponent.h"
#include "CollisionComponent.h"
#include "SLaser.h"
#include "Explosion.h"

Player::Player(Game* game)
	:Actor(game)
	, pState(STATE_IDLE)
	, mLaserCooldown(0.0f)
	, mHealth(MAX_PLAYER_HEALTH)
{
	/* AnimSpriteComponentを生成 */
	asc = new AnimSpriteComponent(this, 150);
	anims = {
		{
			game->GetTexture("Assets/Cat/Cat04.png"),
			game->GetTexture("Assets/Cat/Cat05.png"),
			game->GetTexture("Assets/Cat/Cat06.png")
		},
		{
			game->GetTexture("Assets/Cat/Cat07.png"),
			game->GetTexture("Assets/Cat/Cat08.png"),
			game->GetTexture("Assets/Cat/Cat09.png"),
		},
		{
			game->GetTexture("Assets/Cat/Cat10.png"),
			game->GetTexture("Assets/Cat/Cat11.png"),
			game->GetTexture("Assets/Cat/Cat12.png")
		}
	};
	asc->SetAnimTextures(anims.at(2), true);
	asc->SetAnimFPS(12.0f);

	/* InputComponentを生成し、キーやスピードを設定 */
	ic = new InputComponent(this);
	//ic->SetForwardKey(SDL_SCANCODE_UP);
	//ic->SetBackKey(SDL_SCANCODE_DOWN);
	ic->SetRightKey(SDL_SCANCODE_RIGHT);
	ic->SetLeftKey(SDL_SCANCODE_LEFT);
	ic->SetMaxSpeed(50.0f);

	mCircle = new CollisionComponent(this);
	mCircle->SetRadius(12.0f);
}

Player::~Player() {
	/* 爆発エフェクト */
	Explosion* ex = new Explosion(GetGame());
	ex->SetPosition(GetPosition());
	ex->SetScale(3.0f);
}

void Player::UpdateActor(float deltaTime) {
	if (GetGame()->GetState() == Game::EGameplay) {
		if (mHealth <= 0) {
			SetState(EDead);
			GetGame()->SetState(Game::EGameOver);
		}
	}

	mLaserCooldown -= deltaTime;

	Vector2 pos = GetPosition();
	float texWidth = asc->GetTexWidth() * GetScale() / 2;

	/* 画面外に行かないようにする処理 */
	if (pos.x <= texWidth) {
		SetPosition(Vector2(texWidth, WINDOW_HEIGHT - 40.0f));
		ic->SetVelocity(Vector2::Zero);
	}
	else if (pos.x >= WINDOW_WIDTH - texWidth) {
		SetPosition(Vector2(WINDOW_WIDTH - texWidth, WINDOW_HEIGHT - 40.0f));
		ic->SetVelocity(Vector2::Zero);
	}
}

void Player::ActorInput(const uint8_t* keyState) {

	/* アニメーション切り替え */
	if (keyState[SDL_SCANCODE_LEFT]) {
		if (!(pState & STATE_LEFT)) {
			pState = STATE_LEFT;
			asc->SetAnimTextures(anims.at(0), true);
		}
	}
	else if (keyState[SDL_SCANCODE_RIGHT]) {
		if (!(pState & STATE_RIGHT)) {
			pState = STATE_RIGHT;
			asc->SetAnimTextures(anims.at(1), true);
		}
	}
	else {
		if (!(pState & STATE_IDLE)) {
			pState = STATE_IDLE;
			asc->SetAnimTextures(anims.at(2), true);
		}
	}
	
	/* レーザーを生成し、初期位置を設定 */
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f) {
		SLaser* laser = new SLaser(GetGame(), GetRotation());
		laser->SetPosition(GetPosition());
		laser->SetScale(0.75f);

		mLaserCooldown = 0.1f;	// レーザーのクールタイムをリセット
	}
}
