// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "HUD.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "Player.h"
#include "Owl.h"
#include "Texture.h"

HUD::HUD(Game* game)
	:UIScreen(game)
{
	mHealthOn = mGame->GetTexture("Assets/Health/HealthOn.png");
	mHealthOff = mGame->GetTexture("Assets/Health/HealthOff.png");
	mBossHealth = mGame->GetTexture("Assets/Health/BossHealthGauge.png");
	mGameClear = mGame->GetTexture("Assets/GAMECLEAR_8x7.png");
	mGameOver = mGame->GetTexture("Assets/GAMEOVER_8x7.png");
}

HUD::~HUD()
{
}

void HUD::Update(float deltaTime)
{
	UIScreen::Update(deltaTime);
}

void HUD::Draw(SDL_Renderer* renderer)
{
	float scale = 0.f;

	/* プレイヤーのヘルス表示 */
	int h = 0;
	if (mGame->GetState() == Game::EGameplay || mGame->GetState() == Game::EGameClear) {
		h = mGame->GetPlayer()->GetHealth();
	}
	for (int i = 0; i < MAX_PLAYER_HEALTH; i++) {
		Texture* healthTex = h ? mHealthOn : mHealthOff;
		scale = 2.f;
		DrawTexture(renderer, healthTex, Vector2(5.f, WINDOW_HEIGHT - 5.f - healthTex->GetHeight() * scale * (1 + i)), scale);
		if (h > 0) h--;
	}

	/* Owlのヘルス表示 */
	if (GetGame()->GetWaveState() == Game::EWave2) {
		Enemy* boss = GetGame()->GetBossEnemy();
		float bossHealth = (float)(boss->GetHealth());
		scale = 1.f;

		SDL_FRect r;
		r.w = bossHealth / (float)MAX_OWL_HEALTH;
		r.h = 1.0f;
		r.x = 1.0f - bossHealth / (float)MAX_OWL_HEALTH;
		r.y = 0.0f;

		DrawTextureEx(renderer, mBossHealth, &r, Vector2((WINDOW_WIDTH - mBossHealth->GetWidth() * scale) / 2.f, 5.f), scale);
	}

	/* メッセージ表示 */
	if (GetGame()->GetState() == Game::EGameClear) {
		scale = 4.f;
		DrawTexture(renderer, mGameClear, Vector2((WINDOW_WIDTH - mGameClear->GetWidth() * scale) / 2.f, (WINDOW_HEIGHT - mGameClear->GetHeight() * scale) / 2.f), scale);
	}
	else if (GetGame()->GetState() == Game::EGameOver) {
		scale = 4.f;
		DrawTexture(renderer, mGameOver, Vector2((WINDOW_WIDTH - mGameOver->GetWidth() * scale) / 2.f, (WINDOW_HEIGHT - mGameOver->GetHeight() * scale) / 2.f), scale);
	}
}

