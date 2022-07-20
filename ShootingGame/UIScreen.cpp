// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "UIScreen.h"
#include "Game.h"

UIScreen::UIScreen(Game* game)
	:mGame(game)
	, mTitle(nullptr)
	, mBackground(nullptr)
	, mTexWidth(0)
	, mTexHeight(0)
	, mTitlePos(0.0f, 300.0f)
	, mBGPos(0.0f, 250.0f)
	, mState(EActive)
{
	// Add to UI Stack
	mGame->PushUI(this);
}

UIScreen::~UIScreen()
{

}

void UIScreen::Update(float deltaTime)
{

}

void UIScreen::Draw(SDL_Renderer* renderer)
{
	// Draw background (if exists)
	if (mBackground)
	{
		DrawTexture(renderer, mBackground, mBGPos);
	}
	// Draw title (if exists)
	if (mTitle)
	{
		DrawTexture(renderer, mTitle, mTitlePos);
	}
	// Override in subclasses to draw any textures
}

void UIScreen::ProcessInput(const uint8_t* keys)
{

}

void UIScreen::Close()
{
	mState = EClosing;
}

void UIScreen::DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture,
	const Vector2& offset, float scale)
{
	// Set width/height
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);

	SDL_Rect r;
	r.w = static_cast<int>(mTexWidth * scale);
	r.h = static_cast<int>(mTexHeight * scale);
	r.x = static_cast<int>(offset.x);
	r.y = static_cast<int>(offset.y);

	// Draw (have to convert angle from radians to degrees, and clockwise to counter)
	SDL_RenderCopyEx(renderer,
		texture,
		nullptr,
		&r,
		0.0f,
		nullptr,
		SDL_FLIP_NONE);
}

void UIScreen::DrawTextureEx(struct SDL_Renderer* renderer, SDL_Texture* texture, SDL_FRect* srcrect,
	const Vector2& offset, float scale)
{
	// Set width/height
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);

	SDL_Rect r1, r2;
	r1.w = static_cast<int>(mTexWidth * srcrect->w);
	r1.h = static_cast<int>(mTexHeight * srcrect->h);
	r1.x = static_cast<int>(mTexWidth * srcrect->x);
	r1.y = static_cast<int>(mTexHeight * srcrect->y);

	r2.w = static_cast<int>(mTexWidth * srcrect->w * scale);
	r2.h = static_cast<int>(mTexHeight * srcrect->h * scale);
	r2.x = static_cast<int>(offset.x);
	r2.y = static_cast<int>(offset.y);

	// Draw (have to convert angle from radians to degrees, and clockwise to counter)
	SDL_RenderCopyEx(renderer,
		texture,
		&r1,
		&r2,
		0.0f,
		nullptr,
		SDL_FLIP_NONE);
}
