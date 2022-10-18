// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "UIScreen.h"
#include "Game.h"
#include "Texture.h"

UIScreen::UIScreen(Game* game)
	:mGame(game)
	//, mTitle(nullptr)
	//, mBackground(nullptr)
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
	//// Draw background (if exists)
	//if (mBackground)
	//{
	//	DrawTexture(renderer, mBackground, mBGPos);
	//}
	//// Draw title (if exists)
	//if (mTitle)
	//{
	//	DrawTexture(renderer, mTitle, mTitlePos);
	//}
	// Override in subclasses to draw any textures
}

void UIScreen::ProcessInput(const uint8_t* keys)
{

}

void UIScreen::Close()
{
	mState = EClosing;
}

void UIScreen::DrawTexture(SDL_Renderer* renderer, Texture* texture,
	const Vector2& offset, float scale)
{
	SDL_Rect dst;
	dst.w = static_cast<int>(texture->GetWidth() * scale);
	dst.h = static_cast<int>(texture->GetHeight() * scale);
	dst.x = static_cast<int>(offset.x);
	dst.y = static_cast<int>(offset.y);

	// Draw (have to convert angle from radians to degrees, and clockwise to counter)
	SDL_RenderCopyEx(renderer,
		texture->GetTexture(),
		nullptr,
		&dst,
		0.0f,
		nullptr,
		SDL_FLIP_NONE);
}

void UIScreen::DrawTextureEx(struct SDL_Renderer* renderer, Texture* texture, SDL_FRect* srcrect,
	const Vector2& offset, float scale)
{
	SDL_Rect src, dst;
	src.w = static_cast<int>(texture->GetWidth() * srcrect->w);
	src.h = static_cast<int>(texture->GetHeight() * srcrect->h);
	src.x = static_cast<int>(texture->GetWidth() * srcrect->x);
	src.y = static_cast<int>(texture->GetHeight() * srcrect->y);

	dst.w = static_cast<int>(texture->GetWidth() * srcrect->w * scale);
	dst.h = static_cast<int>(texture->GetHeight() * srcrect->h * scale);
	dst.x = static_cast<int>(offset.x);
	dst.y = static_cast<int>(offset.y);

	// Draw (have to convert angle from radians to degrees, and clockwise to counter)
	SDL_RenderCopyEx(renderer,
		texture->GetTexture(),
		&src,
		&dst,
		0.0f,
		nullptr,
		SDL_FLIP_NONE);
}
