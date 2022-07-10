#pragma once
#include "GameState.h"
#include <entt/entt.hpp>


class Entity
{
public:
	
	Entity() = default;
	Entity(entt::entity handle, GameState* gameState);
	Entity(const Entity& other) = default;
	~Entity();

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		return GameStatePointer->GetRegistry()->emplace<T>(EntityHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& GetComponent()
	{
		return GameStatePointer->GetRegistry()->get<T>(EntityHandle);
	}

	template<typename T>
	bool HasComponent()
	{
		return GameStatePointer->GetRegistry().all_of<T>(EntityHandle);
	}

	template<typename T>
	void RemoveComponent()
	{
		GameStatePointer->GetRegistry().remove<T>(EntityHandle);
	}

	operator bool() const { return EntityHandle != entt::null; }


private:

	entt::entity EntityHandle{ entt::null };
	GameState* GameStatePointer = nullptr;

};

