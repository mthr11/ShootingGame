// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Math.h"
#include <cstdint>
#include <string>

class UIScreen
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();

	// UIScreen subclasses can override these
	virtual void Update(float deltaTime);
	virtual void Draw(struct SDL_Renderer* renderer);
	virtual void ProcessInput(const uint8_t* keys);

	// Tracks if the UI is active or closing
	enum UIState
	{
		EActive,
		EClosing
	};

	// Set state to closing
	void Close();

	// Get state of UI screen
	UIState GetState() const { return mState; }

	class Game* GetGame() { return mGame; }
protected:
	// Helper to draw a texture
	void DrawTexture(struct SDL_Renderer* renderer, struct SDL_Texture* texture,
		const Vector2& offset = Vector2::Zero,
		float scale = 1.0f
	);
	void DrawTextureEx(struct SDL_Renderer* renderer, struct SDL_Texture* texture, struct SDL_FRect* srcrect,
		const Vector2& offset = Vector2::Zero,
		float scale = 1.0f
	);

	class Game* mGame;

	///* UI画面のタイトル文字列用 */
	//class Font* mFont;
	struct SDL_Texture* mTitle;
	struct SDL_Texture* mBackground;
	int mTexWidth;
	int mTexHeight;

	// Configure positions
	Vector2 mTitlePos;
	Vector2 mBGPos;

	// State
	UIState mState;
};
