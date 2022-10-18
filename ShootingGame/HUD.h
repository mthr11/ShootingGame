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

	class Texture* mHealthOn;
	class Texture* mHealthOff;
	class Texture* mBossHealth;
	class Texture* mGameClear;
	class Texture* mGameOver;
};
