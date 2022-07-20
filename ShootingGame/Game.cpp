// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "Crow.h"
#include "Owl.h"
#include "UIScreen.h"
#include "HUD.h"
#include <iostream>

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mGameState(EGameplay)
	, mWaveEnemys(EWave1)
	, mUpdatingActors(false)
{
	mWaveEnemys = std::vector<std::vector<Enemy*>>(2);
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Shooting Game", 100, 100, (int)WINDOW_WIDTH, (int)WINDOW_HEIGHT, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (mGameState != EQuit)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mGameState = EQuit;
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (mGameState == EMainMenu && keyState[SDL_SCANCODE_RETURN]) {
		mGameState = EGameplay;
	}
	else if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mGameState = EQuit;
	}

	if (mGameState == EGameplay || mGameState == EGameClear) {
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->ProcessInput(keyState);
		}
		mUpdatingActors = false;
	}
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 17));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	if (mGameState == EGameplay || mGameState == EGameClear || mGameState == EGameOver) {
		if (mWaveState == EWave1) {
			if (mWaveEnemys.at(0).empty()) {
				mWaveState = EWave2;
				for (auto en : mWaveEnemys.at(1)) {
					en->SetState(Actor::ESpawn);
				}
			}
		}
		else if (mWaveState == EWave2) {
			if (mWaveEnemys.at(1).empty())
				mGameState = EGameClear;
		}

		// Update all actors
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->Update(deltaTime);
		}
		mUpdatingActors = false;

		// Move any pending actors to mActors
		for (auto pending : mPendingActors)
		{
			mActors.emplace_back(pending);
		}
		mPendingActors.clear();

		// Add any dead actors to a temp vector
		std::vector<Actor*> deadActors;
		for (auto actor : mActors)
		{
			if (actor->GetState() == Actor::EDead)
			{
				deadActors.emplace_back(actor);
			}
		}

		// Delete dead actors (which removes them from mActors)
		for (auto actor : deadActors)
		{
			delete actor;
		}
	}

	// Update UI screens
	for (auto ui : mUIStack)
	{
		if (ui->GetState() == UIScreen::EActive)
		{
			ui->Update(deltaTime);
		}
	}
	// Delete any UIScreens that are closed
	auto iter = mUIStack.begin();
	while (iter != mUIStack.end())
	{
		if ((*iter)->GetState() == UIScreen::EClosing)
		{
			delete* iter;
			iter = mUIStack.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 180, 100, 255, 255);
	SDL_RenderClear(mRenderer);

	// Draw all sprite components
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	// Draw any UI screens
	for (auto ui : GetUIStack())
	{
		ui->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	// UI elements
	mHUD = new HUD(this);

	// Create player's ship
	mPlayer = new Player(this);
	mPlayer->SetPosition(Vector2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 40.0f));
	mPlayer->SetRotation(Math::PiOver2);
	mPlayer->SetScale(2.0f);

	/* Enemyを生成 */
	Crow* mCrow;
	const int numCrow = 5;
	for (int i = 0; i < numCrow; i++) {
		mCrow = new Crow(this,
			Vector2(WINDOW_WIDTH / 2 + (WINDOW_WIDTH / 2 + (WINDOW_WIDTH - 200.0f) / 5.0f * (i + 1)) * powf(-1.0f, (float)(i % 2)), 50.0f + i * 40.0f));
		mCrow->SetScale(2.0f);
		//mCrow->SetState(Actor::EPaused);	// デバッグ用
	}

	Owl* mOwl;
	mOwl = new Owl(this, Vector2(WINDOW_WIDTH / 2, -150.0f));
	mOwl->SetScale(3.0f);
	mOwl->SetState(Actor::EPaused);
	//mOwl->SetState(Actor::ESpawn);	// デバッグ用
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Clear the UI stack
	while (!mUIStack.empty())
	{
		delete mUIStack.back();
		mUIStack.pop_back();
	}

	// Destroy textures
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::AddEnemy(Enemy* en)
{
	mEnemys.emplace_back(en);
}

void Game::RemoveEnemy(Enemy* en)
{
	auto iter = std::find(mEnemys.begin(), mEnemys.end(), en);
	if (iter != mEnemys.end()) {
		mEnemys.erase(iter);
	}
}

void Game::AddWaveEnemy(Enemy* en, int index) {
	mWaveEnemys.at(index).emplace_back(en);
}
void Game::RemoveWaveEnemy(Enemy* en, int index) {
	auto iter = std::find(mWaveEnemys.at(index).begin(), mWaveEnemys.at(index).end(), en);
	if (iter != mWaveEnemys.at(index).end()) {
		mWaveEnemys.at(index).erase(iter);
	}
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::PushUI(UIScreen* screen)
{
	mUIStack.emplace_back(screen);
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}
