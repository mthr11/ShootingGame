// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT 600.0f

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	struct SDL_Renderer* GetRenderer() { return mRenderer; }
	class HUD* GetHUD() { return mHUD; }
	class Texture* GetTexture(const std::string& fileName);

	// Manage UI stack
	const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	void PushUI(class UIScreen* screen);

	/* セッターとゲッター */
	class Player* GetPlayer() { return mPlayer; }
	void AddEnemy(class Enemy* en);
	void RemoveEnemy(class Enemy* en);
	std::vector<class Enemy*>& GetEnemys() { return mEnemys; }
	void AddWaveEnemy(class Enemy* en, int index);
	void RemoveWaveEnemy(class Enemy* en, int index);
	std::vector<class Enemy*>& GetWaveEnemys(int index) { return mWaveEnemys.at(index); }
	void SetBossEnemy(class Enemy* boss) { mBossEnemy = boss; }
	class Enemy* GetBossEnemy() { return mBossEnemy; }

	enum GameState
	{
		EMainMenu,
		EGameplay,
		EGameClear,
		EGameOver,
		EPaused,
		EQuit
	};

	GameState GetState() const { return mGameState; }
	void SetState(GameState state) { mGameState = state; }

	enum WaveState
	{
		EWave1,
		EWave2
	};

	WaveState GetWaveState() const { return mWaveState; }
	void SetWaveState(WaveState state) { mWaveState = state; }
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// Map of textures loade
	std::unordered_map<std::string, class Texture*> mTextures;

	// All the actors in the game
	std::vector<class Actor*> mActors;
	std::vector<class UIScreen*> mUIStack;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	class HUD* mHUD;

	Uint32 mTicksCount;
	GameState mGameState;
	WaveState mWaveState;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	// Game-specific
	class Player* mPlayer;
	std::vector<class Enemy*> mEnemys;
	std::vector<std::vector<class Enemy*>> mWaveEnemys;
	class Enemy* mBossEnemy;
};
