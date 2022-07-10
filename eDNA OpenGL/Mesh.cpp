#include "Mesh.h"


Mesh::Mesh()
{
}
// constructor
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->position = glm::dvec3(0.0);
    this->scale = glm::vec3(1.0f);
    this->rotation = glm::vec3(0.f);
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    
    // now that we have all the required data, set the vertex buffers and its attribute pointers.
    SetupMesh();
}

Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<unsigned int> indices)
{
    this->position = glm::dvec3(0.0,0.0,0.0);
    this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    this->rotation = glm::vec3(0.f);
    this->indices = indices;
    Vertex temp;
    temp.Normal = glm::vec3(0.f, 0.f, 0.f);
    temp.UV = glm::vec2(0.f, 0.f);
    temp.Tangent = glm::vec3(0.f, 0.f, 0.f);
    temp.Bitangent = glm::vec3(0.f, 0.f, 0.f);
    for (auto pos : positions)
    {
        temp.Position = pos;
        
        this->vertices.push_back(temp);
    }
    SetupMesh();
}

Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals)
{
    this->position = glm::dvec3(0.0, 0.0, 0.0);
    this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    this->rotation = glm::vec3(0.f);

    Vertex temp;
    temp.Normal = glm::vec3(0.f, 0.f, 0.f);
    temp.UV = glm::vec2(0.f, 0.f);
    temp.Tangent = glm::vec3(0.f, 0.f, 0.f);
    temp.Bitangent = glm::vec3(0.f, 0.f, 0.f);
    for (int i =0; i < positions.size(); i++)
    {
        temp.Position = positions[i];
        temp.Normal = normals[i];

        this->vertices.push_back(temp);
        this->indices.push_back(i);

    }
    SetupMesh();
}

Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> uv)
{
    this->position = glm::dvec3(0.0, 0.0, 0.0);
    this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    this->rotation = glm::vec3(0.f);

    Vertex temp;
    temp.Normal = glm::vec3(0.f, 0.f, 0.f);
    temp.UV = glm::vec2(0.f, 0.f);
    temp.Tangent = glm::vec3(0.f, 0.f, 0.f);
    temp.Bitangent = glm::vec3(0.f, 0.f, 0.f);
    for (int i = 0; i < positions.size(); i++)
    {
        temp.Position = positions[i];
        temp.Normal = normals[i];
        temp.UV = uv[i];

        this->vertices.push_back(temp);
        this->indices.push_back(i);


    }
    SetupMesh();
}
// render the mesh
void Mesh::Draw(Shader& shader, Camera &camera)
{
    shader.use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)camera.width / (float)camera.height, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);

    glm::dvec3 relativeTransform = this->position - camera.Position;

    model = glm::translate(model, (glm::vec3)relativeTransform); // translation matrix
    model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
    model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
    model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
    model = glm::scale(model, scale);	// scaling matrix
    shader.setMat4("model", model);

    glm::mat3 normal = glm::transpose(glm::inverse((glm::mat3)model));
    shader.setMat3("normal", normal);

    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}
// render mesh as part of a model
void Mesh::Draw(Shader& shader, Camera& camera, Model& model)
{
    shader.use();

    // view/projection transformations
    glm::mat4 m_projection = glm::perspective(glm::radians(camera.Zoom), (float)camera.width / (float)camera.height, 0.1f, 100.0f);
    glm::mat4 m_view = camera.GetViewMatrix();
    shader.setMat4("projection", m_projection);
    shader.setMat4("view", m_view);

    // render the loaded model

    // meshes matrix
    glm::mat4 m_mesh = glm::mat4(1.0f);
    glm::dvec3 relativeTransform = this->position - model.GetOrigin();

    m_mesh = glm::translate(m_mesh, (glm::vec3)relativeTransform); // translation matrix
    m_mesh = glm::rotate(m_mesh, rotation.z, glm::vec3(0, 0, 1));
    m_mesh = glm::rotate(m_mesh, rotation.y, glm::vec3(0, 1, 0));
    m_mesh = glm::rotate(m_mesh, rotation.x, glm::vec3(1, 0, 0));
    m_mesh = glm::scale(m_mesh, scale);	// scaling matrix

    //model matrix
    glm::mat4 m_model = glm::mat4(1.0f);
    glm::dvec3 relativeGlobalTransform = model.GetPosition() - camera.Position;

    m_model = glm::translate(m_model, (glm::vec3)relativeGlobalTransform);
    m_model = glm::rotate(m_model, model.GetRotation().z, glm::vec3(0, 0, 1));
    m_model = glm::rotate(m_model, model.GetRotation().y, glm::vec3(0, 1, 0));
    m_model = glm::rotate(m_model, model.GetRotation().x, glm::vec3(1, 0, 0));
    m_model = glm::scale(m_model, model.GetScale());


    shader.setMat4("model", m_model*m_mesh);

    glm::mat3 m_normal = glm::transpose(glm::inverse((glm::mat3)m_model));
    shader.setMat3("normal", m_normal);

    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::DrawAsModelSection(Shader& shader, Camera& camera, Model& model)
{
    shader.use();
    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)camera.width / (float)camera.height, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    UpdateTransform(model.GetOrigin());

    glm::mat4 modelmesh = model.GetTransform()*transform;
    shader.setMat4("model", modelmesh);

    glm::mat3 normal = glm::transpose(glm::inverse((glm::mat3)(modelmesh)));
    shader.setMat3("normal", normal);
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);

}

void Mesh::UpdateTransform(glm::dvec3 modelOrigin)
{
    glm::dvec3 relativePosition = position - modelOrigin;
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, (glm::vec3)relativePosition); // translation matrix
    matrix = glm::rotate(matrix, rotation.z, glm::vec3(0, 0, 1));
    matrix = glm::rotate(matrix, rotation.y, glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, rotation.x, glm::vec3(1, 0, 0));
    matrix = glm::scale(matrix, scale);

    transform = matrix;
}

glm::mat4 Mesh::GetTransform()
{
    return transform;
}
    // initializes all the buffer objects/arrays
void Mesh::SetupMesh()
{
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