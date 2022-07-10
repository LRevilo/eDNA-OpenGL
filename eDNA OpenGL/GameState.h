#pragma once
#include "Game.h"
#include "entt/entt.hpp"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "TagComponent.h"
#include <string>

class Entity;

class GameState
{

private:

	friend class Entity;
	



protected:
	std::stack<GameState*>* GameStates;

	GLFWwindow* window;

	bool quit;

public:

	entt::registry Registry;

	GameState(GLFWwindow* window, std::stack<GameState*>* GameStates);
	virtual ~GameState();

	Entity CreateEntity(const std::string& name = std::string());


	const bool& GetQuit() const;
	void EndState();
	entt::registry* GetRegistry();

	virtual void KeyCallback(int key, int scancode, int action, int mode);

	virtual void MouseCallback(double xposIn, double yposIn);
	virtual void MouseButtonCallback(int button, int action, int mods);
	virtual void ScrollCallback(double xoffset, double yoffset);
	
	virtual void ProcessInputs(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Render(GLFWwindow* window = nullptr) = 0;
};

