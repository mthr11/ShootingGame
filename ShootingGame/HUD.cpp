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

HUD::HUD(Game* game)
	:UIScreen(game)
{
	mHealthOn = mGame->GetTexture("Assets/Health/HealthOn.png");
	mHealthOff = mGame->GetTexture("Assets/Health/HealthOff.png");
	mBossHealth = mGame->GetTexture("Assets/Health/BossHealthGauge.png");
	mGameClear = mGame->GetTexture("Assets/GAMECLEAR_8x7.png");
	mGameOver = mGame->GetTexture("Assets/GAMEOVER_8x7.png");
	SDL_QueryTexture(mBossHealth, nullptr, nullptr, &mBHTexWidth, &mBHTexHeight);
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
	/* プレイヤーのヘルス表示 */
	int h = 0;
	if (mGame->GetState() == Game::EGameplay || mGame->GetState() == Game::EGameClear)
		h = mGame->GetPlayer()->GetHealth();
	for (int i = 0; i < MAX_PLAYER_HEALTH; i++) {
		SDL_Texture* healthTex = h ? mHealthOn : mHealthOff;
		DrawTexture(renderer, healthTex, Vector2(5.0f, WINDOW_HEIGHT - 53.0f - 48.0f * i), 2.0f);
		if (h > 0) h--;
	}

	/* Owlのヘルス表示 */
	if (GetGame()->GetWaveState() == Game::EWave2) {
		Enemy* boss = GetGame()->GetBossEnemy();
		float bossHealth = (float)(boss->GetHealth());

		SDL_FRect r;
		r.w = bossHealth / (float)MAX_OWL_HEALTH;
		r.h = 1.0f;
		r.x = 1.0f - bossHealth / (float)MAX_OWL_HEALTH;
		r.y = 0.0f;

		DrawTextureEx(renderer, mBossHealth, &r, Vector2(WINDOW_WIDTH / 2 - mBHTexWidth / 2, 5.0f), 1.0f);
	}

	/* メッセージ表示 */
	if (GetGame()->GetState() == Game::EGameClear) {
		DrawTexture(renderer, mGameClear, Vector2(WINDOW_WIDTH / 2 - 78.0f, WINDOW_HEIGHT / 2 - 38.0f), 4.0f);
	}
	else if (GetGame()->GetState() == Game::EGameOver) {
		DrawTexture(renderer, mGameOver, Vector2(WINDOW_WIDTH / 2 - 64.0f, WINDOW_HEIGHT / 2 - 38.0f), 4.0f);
	}
}

