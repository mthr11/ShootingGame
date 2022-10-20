#pragma once

class SceneManager;

/* Base class of Scene */
class Scene
{
public:
	Scene(SceneManager* manager)
		:sm(manager)
	{ }

	// Scene-specific behavior
	virtual void ProcessInput(const uint8_t* keyState) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void LoadData();

	// Getter for string name of scene
	virtual const char* GetName() const = 0;
protected:
	SceneManager* sm;
};

/* Title Scene */
class STitle : public Scene
{
public:
	STitle(SceneManager* manager)
		:Scene(manager)
	{ }

	// Override with behaviors for this scene
	void ProcessInput(const uint8_t* keyState) override;
	void Update(float deltaTime) override;
	void Draw() override;
	
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{ return "Title"; }
};

/* Game play Scene */
class SGameplay : public Scene
{
public:
	SGameplay(SceneManager* manager)
		:Scene(manager)
	{ }

	// Override with behaviors for this scene
	void ProcessInput(const uint8_t* keyState) override;
	void Update(float deltaTime) override;
	void Draw() override;

	void OnEnter() override;
	void OnExit() override;
	void LoadData() override;

	const char* GetName() const override
	{
		return "Gameplay";
	}
};

/* Game clear Scene */
class SGameclear : public Scene
{
public:
	SGameclear(SceneManager* manager)
		:Scene(manager)
	{ }

	// Override with behaviors for this scene
	void ProcessInput(const uint8_t* keyState) override;
	void Update(float deltaTime) override {};
	void Draw() override {};

	void OnEnter() override;
	void OnExit() override {};

	const char* GetName() const override
	{
		return "Gameclear";
	}
};

/* Game over Scene */
class SGameover : public Scene
{
public:
	SGameover(SceneManager* manager)
		:Scene(manager)
	{ }

	// Override with behaviors for this scene
	void ProcessInput(const uint8_t* keyState) override;
	void Update(float deltaTime) override {};
	void Draw() override {};

	void OnEnter() override;
	void OnExit() override {};

	const char* GetName() const override
	{
		return "Gameover";
	}
};

/* Result Scene */
class SResult : public Scene
{
public:
	SResult(SceneManager* manager)
		:Scene(manager)
	{ }

	// Override with behaviors for this scene
	void ProcessInput(const uint8_t* keyState) override;
	void Update(float deltaTime) override;
	void Draw() override;

	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Result";
	}
};

/* How to play Scene */
class SHowto : public Scene
{
public:
	SHowto(SceneManager* manager)
		:Scene(manager)
	{ }

	// Override with behaviors for this scene
	void ProcessInput(const uint8_t* keyState) override;
	void Update(float deltaTime) override;
	void Draw() override;

	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Howto";
	}
};
