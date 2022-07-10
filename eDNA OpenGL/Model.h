#pragma once
#include "Game.h"
#include "Mesh.h"

class Model
{

public:
	Model();
	~Model();
	std::vector<class Mesh> Meshes;
	
	void SetPosition(glm::dvec3 position);
	void SetOrigin(glm::dvec3 origin);
	void SetScale(glm::vec3 scale);
	void SetRotation(glm::vec3 rotation);
	void SetCamera(Camera &camera);


	glm::dvec3 GetPosition();
	glm::dvec3 GetOrigin();
	glm::vec3 GetScale();
	glm::vec3 GetRotation();
	Camera* GetCamera();

	void Move(glm::vec3 direction, float velocity, float& dt);
	void Rotate(glm::vec3 rotation, float velocity, float& dt);
	void Scale(glm::vec3 scale, float velocity, float& dt);

	void Draw(Shader& shader);


	void UpdateTransform();
	glm::mat4 GetTransform();

private:
	glm::dvec3 position;
	glm::dvec3 origin;
	glm::vec3 scale;
	glm::vec3 rotation;
	glm::mat4 transform;

	Camera* camera;

	

};

