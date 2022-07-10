#include "SceneRenderer.h"
#include "Camera.h"
#include "Shader.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "AmbientLightComponent.h"
#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "Camera.h"



SceneRenderer::SceneRenderer()
{
    wireframe = false;
}

SceneRenderer::~SceneRenderer()
{


}

void SceneRenderer::RenderScene()
{

    //Render all meshes with transforms
	auto meshGroup = Registry->group<TransformComponent, MeshComponent>();
    for (auto entity : meshGroup)
    {
        auto& mesh = meshGroup.get<MeshComponent>(entity);
        auto& transform = meshGroup.get<TransformComponent>(entity);
        SetupMesh(mesh);
        DrawMesh(mesh, transform);
    }

}

void SceneRenderer::SetupMesh(MeshComponent &meshComponent)
{
    auto vertices = meshComponent.Vertices;
    auto indices = meshComponent.Indices;

    // Turn on wireframe mode

    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers

    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));

    glBindVertexArray(0);


}




void SceneRenderer::DrawMesh(MeshComponent& meshComponent,
                                TransformComponent& transformComponent)
{


    unsigned int material = meshComponent.Material;
    auto & shader = (*shaders)[material];

    shader.use();
    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)camera->width / (float)camera->height, 0.1f, 100.0f);
    glm::mat4 view = camera->GetViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    glm::mat4 modelmesh = transformComponent.GetTransform(camera->Position) * meshComponent.GetTransform();
    shader.setMat4("model", modelmesh);

    glm::mat3 normal = glm::transpose(glm::inverse((glm::mat3)(modelmesh)));
    shader.setMat3("normal", normal);

    // set ambient and direcitonal light


    shader.setVec4("ambientColor", *ambientColor);
    shader.setVec4("directionalColor", *directionalColor);



    shader.setVec3("directionalDir", *directionalDir);


    // Turn on wireframe mode
    if (wireframe){ glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(meshComponent.Indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);


    // Turn off wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    // stops memory leak (wtf)
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    //------------------------
}