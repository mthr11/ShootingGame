#include "SceneManager.h"
#include "Scene.h"
#include <SDL_log.h>

SceneManager::SceneManager(Game* game)
	:mGame(game)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::ProcessInput(const uint8_t* keyState)
{
	if (!mSceneStack.empty())
	{
		mSceneStack.top()->ProcessInput(keyState);
	}
}

void SceneManager::Update(float deltaTime)
{
	if (!mSceneStack.empty())
	{
		mSceneStack.top()->Update(deltaTime);
	}
}

void SceneManager::Draw()
{
	if (!mSceneStack.empty())
	{
		mSceneStack.top()->Draw();
	}
}

void SceneManager::ChangeScene(const std::string& name)
{
	Scene* current;

	// Try to find the new scene from the map
	auto iter = mSceneMap.find(name);
	if (iter != mSceneMap.end())
	{
		current = iter->second;
		current->OnEnter();
		mSceneStack.push(current);
	}
	else
	{
		SDL_Log("Could not find Scene %s in scene map", name.c_str());
	}
}

void SceneManager::Register(Scene* scene)
{
	mSceneMap.emplace(scene->GetName(), scene);
}

Scene* SceneManager::GetScene()
{
	if (mSceneStack.empty()) {
		return nullptr;
	}
	else {
		return mSceneStack.top();
	}
}

void SceneManager::ClearStack()
{
	while (!mSceneStack.empty()) {
		mSceneStack.pop();
	}
}
