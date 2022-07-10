#include "GameState.h"
#include "Entity.h"

GameState::GameState(GLFWwindow* window, std::stack<GameState*>* GameStates)
{
	this->window = window;
	this->GameStates = GameStates;
	this->quit = false;



	//// create entity
	//entt::entity entity = Registry.create();

	//// add component to entity, also returns the component 
	//auto& transform = Registry.emplace<TransformComponent>(entity);

	//// can edit returned component
	////transform = glm::mat4(0.0f);

	////Registry.remove<TransformComponent>(entity);


	//// can get the component if reference isn't stored

	//TransformComponent& transform_ = Registry.get<TransformComponent>(entity);


	//// list all entities with transform component
	//// and iterate over them

	//auto view = Registry.view<TransformComponent>();
	//for (auto test_entity : view)
	//{
	//	// probably slower 
	//	TransformComponent& test_transform = Registry.get<TransformComponent>(test_entity);

	//	// probably faster
	//	TransformComponent& test2_transform = view.get<TransformComponent>(test_entity);

	//	//test_transform.Move(glm::dvec3(7.0, 7.0, 7.0), 420.f, 1.f / 69);
	//}


	//// get enities with 2 components
	//auto group = Registry.group<TransformComponent, MeshComponent>();
	//for (auto test_entity : group)
	//{
	//	// probably slower 
	//	TransformComponent& test_transform = Registry.get<TransformComponent>(test_entity);

	//	// probably faster
	//	auto[transformx, mesh] = group.get<TransformComponent, MeshComponent>(test_entity);

	//	//mesh.MoveMesh(glm::dvec3(7.0, 7.0, 7.0), 420.f, 1.f / 69);
	//	//transformx.Move(glm::dvec3(7.0, 7.0, 7.0), 420.f, 1.f / 69);
	//}


	////call functions on construction etc
	//// 
	//// static void SomeFunction(entt::registry& registry, entt::entity entity)
	//// 	   {
	//// 	   }
	//// 
	////Registry.on_construct<TransformComponent>().connect<&SomeFunction>();


}
GameState::~GameState()
{
	Registry.clear();
}

Entity GameState::CreateEntity(const std::string& name)
{
	Entity entity = { Registry.create(),this };
	//entity.AddComponent<TransformComponent>();
	auto& tag = entity.AddComponent<TagComponent>();
	tag.Tag = name.empty() ? "Entity" : name;
	return entity;
}

const bool& GameState::GetQuit() const
{
	return this->quit;
}

void GameState::EndState()
{
	this->quit = true;
}

entt::registry* GameState::GetRegistry()
{
	return &Registry;
}


void GameState::KeyCallback(int key, int scancode, int action, int mode)
{
}

void GameState::MouseCallback(double xposIn, double yposIn)
{
}

void GameState::MouseButtonCallback(int button, int action, int mods)
{
}

void GameState::ScrollCallback(double xoffset, double yoffset)
{
}


