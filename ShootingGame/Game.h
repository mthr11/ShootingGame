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

class Actor;
class Player;
class Enemy;
class SpriteComponent;
class Texture;
class SceneManager;
class UIScreen;
class HUD;

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	void AddSprite(SpriteComponent* sprite);
	void RemoveSprite( SpriteComponent* sprite);

	void CreatePlayer();
	void CreateHUD();

	SDL_Renderer* GetRenderer() { return mRenderer; }
	SceneManager* GetSceneManager() { return sm; }
	HUD* GetHUD() { return mHUD; }
	Texture* GetTexture(const std::string& fileName);

	// Manage UI stack
	const std::vector<UIScreen*>& GetUIStack() { return mUIStack; }
	void PushUI(UIScreen* screen);

	/* セッターとゲッター */
	Player* GetPlayer() { return mPlayer; }
	void AddEnemy(Enemy* en);
	void RemoveEnemy(Enemy* en);
	std::vector<Enemy*>& GetEnemys() { return mEnemys; }
	void AddWaveEnemy(Enemy* en, int index);
	void RemoveWaveEnemy(Enemy* en, int index);
	std::vector<Enemy*>& GetWaveEnemys(int index) { return mWaveEnemys.at(index); }
	void SetBossEnemy(Enemy* boss) { mBossEnemy = boss; }
	Enemy* GetBossEnemy() { return mBossEnemy; }

	enum GameState
	{
		EGameplay,
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

	void UnloadData();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();

	// Map of textures loade
	std::unordered_map<std::string, Texture*> mTextures;

	// All the actors in the game
	std::vector<Actor*> mActors;
	std::vector<UIScreen*> mUIStack;
	// Any pending actors
	std::vector< Actor*> mPendingActors;

	// All the sprite components drawn
	std::vector<SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SceneManager* sm;
	HUD* mHUD;

	Uint32 mTicksCount;
	GameState mGameState;
	WaveState mWaveState;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	// Game-specific
	Player* mPlayer;
	std::vector<Enemy*> mEnemys;
	std::vector<std::vector<Enemy*>> mWaveEnemys;
	Enemy* mBossEnemy;
};
