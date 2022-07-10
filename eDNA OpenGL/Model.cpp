#include "Model.h"

Model::Model()
{
	this->position = glm::dvec3(0.0);
	this->origin = glm::dvec3(0.0);
	this->scale = glm::vec3(1.0f);
	this->rotation = glm::vec3(0.f);
	this->transform = glm::mat4(1.0f);
	this->camera = nullptr;
}

Model::~Model()
{
}


void Model::SetPosition(glm::dvec3 position)
{
	this->position = position;
	UpdateTransform();
}
void Model::SetOrigin(glm::dvec3 origin)
{
	this->origin = origin;
	UpdateTransform();
}
void Model::SetScale(glm::vec3 scale)
{
	this->scale = scale;
	UpdateTransform();
}
void Model::SetRotation(glm::vec3 rotation)
{
	this->rotation = rotation;
	UpdateTransform();
}
void Model::SetCamera(Camera &camera)
{
	this->camera = &camera;
	UpdateTransform();
}

glm::dvec3 Model::GetPosition()
{
	return position;
}
glm::dvec3 Model::GetOrigin()
{
	return origin;
}
glm::vec3 Model::GetScale()
{
	return scale;
}
glm::vec3 Model::GetRotation()
{
	return rotation;
}
Camera* Model::GetCamera()
{
	return camera;
}

void Model::Move(glm::vec3 direction, float velocity, float& dt)
{
	this->position += (direction * velocity * dt);
	UpdateTransform();
}

void Model::Rotate(glm::vec3 rotation, float velocity, float& dt)
{
	this->rotation += (rotation * velocity * dt);
	UpdateTransform();
}

void Model::Scale(glm::vec3 scale, float velocity, float& dt)
{
	this->scale += (scale * velocity * dt);
	UpdateTransform();
}

void Model::Draw(Shader &shader)
{
	UpdateTransform();
	for (unsigned int i = 0; i < Meshes.size(); i++)
	{
		Meshes[i].DrawAsModelSection(shader, *camera, *this);
	}
}

void Model::UpdateTransform()
{
	if (camera != nullptr)
	{
		glm::dvec3 relativePosition = position - camera->Position;

		glm::mat4 matrix = glm::mat4(1.0f);
		matrix = glm::translate(matrix, (glm::vec3)relativePosition);
		matrix = glm::rotate(matrix, rotation.z, glm::vec3(0, 0, 1));
		matrix = glm::rotate(matrix, rotation.y, glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, rotation.x, glm::vec3(1, 0, 0));
		matrix = glm::scale(matrix, scale);

		transform = matrix;
	}
}

glm::mat4 Model::GetTransform()
{
	return transform;
}


