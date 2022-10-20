#include "Game.h"
#include "Player.h"
#include "Crow.h"
#include "Owl.h"
#include "Scene.h"
#include "SceneManager.h"
#include <SDL_log.h>
#include <iostream>

void Scene::LoadData()
{
}


/* Title Scene */
void STitle::ProcessInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_RETURN]) {
		sm->ChangeScene("Gameplay");
	}
}

void STitle::Update(float deltaTime)
{

}

void STitle::Draw()
{

}

void STitle::OnEnter()
{
	sm->GetGame()->UnloadData();
	std::cout << GetName() << std::endl;
}

void STitle::OnExit()
{
}

/* Game play Scene */
void SGameplay::ProcessInput(const uint8_t* keyState)
{
}

void SGameplay::Update(float deltaTime)
{
	Game* mGame = sm->GetGame();
	if (mGame->GetWaveState() == Game::EWave1) {
		if (mGame->GetWaveEnemys(0).empty()) {
			mGame->SetWaveState(Game::EWave2);
			for (auto en : mGame->GetWaveEnemys(1)) {
				en->SetState(Actor::ESpawn);
			}
		}
	}
	else if (mGame->GetWaveState() == Game::EWave2) {
		if (mGame->GetWaveEnemys(1).empty())
			//mGame->SetState(Game::EGameClear);
			sm->ChangeScene("Gameclear");
	}

	if (mGame->GetPlayer()->GetHealth() <= 0) {
		mGame->GetPlayer()->SetState(Actor::EDead);
		sm->ChangeScene("Gameover");
	}
}

void SGameplay::Draw()
{
}

void SGameplay::OnEnter()
{
	std::cout << GetName() << std::endl;
	if (!sm->IsStackEmpty()) {
		sm->ClearStack();
		//delete
	}
	
	LoadData();
}

void SGameplay::OnExit()
{
}

void SGameplay::LoadData()
{
	Game* mGame = sm->GetGame();

	/* Set wave */
	mGame->SetWaveState(Game::EWave1);

	/* UI elements */
	mGame->CreateHUD();
	
	/* Create the player */
	mGame->CreatePlayer();
	mGame->GetPlayer()->SetPosition(Vector2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 40.0f));
	mGame->GetPlayer()->SetRotation(Math::PiOver2);
	mGame->GetPlayer()->SetScale(2.0f);

	/* Create enemys */
	Crow* mCrow;
	const int numCrow = 5;
	for (int i = 0; i < numCrow; i++) {
		mCrow = new Crow(mGame,
			Vector2(WINDOW_WIDTH / 2 + (WINDOW_WIDTH / 2 + (WINDOW_WIDTH - 200.0f) / 5.0f * (i + 1)) * powf(-1.0f, (float)(i % 2)), 50.0f + i * 40.0f));
		mCrow->SetScale(2.0f);
		//mCrow->SetState(Actor::EPaused);	// debug
	}

	Owl* mOwl;
	mOwl = new Owl(mGame, Vector2(WINDOW_WIDTH / 2, -150.0f));
	mOwl->SetScale(3.0f);
	mOwl->SetState(Actor::EPaused);
	//mOwl->SetState(Actor::ESpawn);	// debug
}

/* Game clear Scene */
void SGameclear::ProcessInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_RETURN]) {
		sm->ChangeScene("Result");
	}
}

void SGameclear::OnEnter()
{
	std::cout << GetName() << std::endl;
}

/* Game over Scene */
void SGameover::ProcessInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_RETURN]) {
		sm->ChangeScene("Result");
	}
}

void SGameover::OnEnter()
{
	std::cout << GetName() << std::endl;
}

/* Result Scene */
void SResult::ProcessInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_R]) {
		sm->ChangeScene("Title");
	}
}

void SResult::Update(float deltaTime)
{
}

void SResult::Draw()
{
}

void SResult::OnEnter()
{
	std::cout << GetName() << std::endl;
}

void SResult::OnExit()
{
}

/* How to play Scene */
void SHowto::ProcessInput(const uint8_t* keyState)
{
}

void SHowto::Update(float deltaTime)
{
}

void SHowto::Draw()
{
}

void SHowto::OnEnter()
{
}

void SHowto::OnExit()
{
}
