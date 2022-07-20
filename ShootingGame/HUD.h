// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "UIScreen.h"
#include <vector>

class HUD : public UIScreen
{
public:
	// (Lower draw order corresponds with further back)
	HUD(class Game* game);
	~HUD();

	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
protected:
	//void UpdateHealth(float deltaTime);

	struct SDL_Texture* mHealthOn;
	struct SDL_Texture* mHealthOff;
	struct SDL_Texture* mBossHealth;
	struct SDL_Texture* mGameClear;
	struct SDL_Texture* mGameOver;

	/* width/height of BossHealth texture */
	int mBHTexWidth;
	int mBHTexHeight;
};
