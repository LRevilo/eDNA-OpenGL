#pragma once
#include "entt/entt.hpp"
#include <vector>
#include "glm.h"

class SceneRenderer
{
public:
	SceneRenderer();
	~SceneRenderer();



	class Camera* camera;
	entt::registry* Registry;
	std::vector<class Shader>* shaders;

	bool wireframe;


	glm::vec4 *ambientColor;
	glm::vec4 *directionalColor;
	glm::vec2 *directionalAngle;
	glm::vec3 *directionalDir;

	void RenderScene();

	unsigned int VAO;
private:
	

	// render data 
	unsigned int VBO, EBO;

	// initializes all the buffer objects/arrays
	void SetupMesh(struct MeshComponent& meshComponent);


	void DrawMesh(struct MeshComponent& meshComponent,
					struct TransformComponent& transformComponent);
};