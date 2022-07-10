#include "Entity.h"

Entity::Entity(entt::entity handle, GameState* gameStatePointer)
	: EntityHandle(handle), GameStatePointer(gameStatePointer)
{

}

Entity::~Entity()
{
}

