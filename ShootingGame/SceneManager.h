#pragma once
#include <unordered_map>
#include <stack>
#include <string>

class Game;
class Scene;

class SceneManager
{
public:
	SceneManager(Game* game);
	~SceneManager();

	void ProcessInput(const uint8_t* keyState);
	void Update(float deltaTime);
	void Draw();
	void ChangeScene(const std::string& name);
	
	// Add a scene to the scene map
	void Register(Scene* scene);

	Game* GetGame() { return mGame; }
	Scene* GetScene();

	bool IsStackEmpty() { return mSceneStack.empty(); }
	void ClearStack();
private:
	Game* mGame;
	//Scene* mCurrentScene;
	
	std::unordered_map<std::string, Scene*> mSceneMap;
	std::stack<Scene*> mSceneStack;
};

