#pragma once
#include "WorldGameState.h"
#include "Entity.h"
#include "Shader.h"
//#include "MeshComponent.h"
#include "MeshGenerator.h"

WorldGameState::WorldGameState(GLFWwindow* window, std::stack<GameState*>* GameStates)
	: GameState(window, GameStates)
{
    
    firstMouse = true;
    enableMouse = true;
    lastX = 0.f;
    lastY = 0.f;



    shaders.push_back(Shader("shader.vert", "shader.frag"));


    sceneRenderer.shaders = &shaders;
    sceneRenderer.Registry = &Registry;
    sceneRenderer.camera = &worldCamera;
    sceneRenderer.ambientColor = &ambientColor;
    sceneRenderer.directionalColor = &directionalColor;
    sceneRenderer.directionalAngle = &directionalAngle;
    sceneRenderer.directionalDir = &directionalDir;

    

    Entity box = CreateEntity("Box");
    Entity box2 = CreateEntity("Box2");
    Entity box3 = CreateEntity("custom box tm");


    auto& trans1 = box.AddComponent<TransformComponent>();
    trans1.Translation = glm::dvec3(5, 0, 0);
    MG.Cylinder(box.AddComponent<MeshComponent>(),22,4);



    auto& trans2 = box2.AddComponent<TransformComponent>();
    trans2.Translation = glm::dvec3(0, 5,0);
    trans2.Rotation = glm::dvec3(1, 1, 0);
    MG.Cube(box2.AddComponent<MeshComponent>());

    auto& trans3 = box3.AddComponent<TransformComponent>();
    trans3.Translation = glm::dvec3(-0.5, -0.5, 0);
    trans3.Rotation = glm::dvec3(1.57, 1.57, 0);
    MG.Plane(box3.AddComponent<MeshComponent>(), 3);



    worldCamera.Position.z = 2.f;



    std::cout << "WorldGameState Constructor" << std::endl;
}

WorldGameState::~WorldGameState()
{
}

void WorldGameState::ProcessInputs(const float& dt)
{
    glfwPollEvents();
    if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) || glfwWindowShouldClose(window))
    {
        EndState();
    }

}

void WorldGameState::MouseCallback(double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    if (!enableMouse)
    {
        worldCamera.ProcessMouseMovement(xoffset, yoffset, true);
    }
}

void WorldGameState::KeyCallback(int key, int scancode, int action, int mode)
{

    if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
    {
        if (!enableMouse)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            enableMouse = true;
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            enableMouse = false;
        }
    }

    if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
    {
        if (!sceneRenderer.wireframe)
        {
            sceneRenderer.wireframe = true;
        }
        else
        {
            sceneRenderer.wireframe = false;
        }

    }
}
void WorldGameState::Update(const float& dt)
{
    


    //camera.Pitch = 30.f;
    //camera.Yaw = -90.f;

    //camera.Position.x = cube.GetPosition().x;
    //camera.Position.y = cube.GetPosition().y - 25.f * cos(1.0471975512f);
    //worldCamera.Position.z += 0.1*dt;//cube.GetPosition().z + 25.f * sin(1.0471975512f);

    //worldCamera.UpdateCameraVectors();
    //worldCamera.UpdateViewMatrix();




    auto entityList = Registry.view<TransformComponent>();
    for (auto entity : entityList)
    {
        auto& transform = entityList.get<TransformComponent>(entity);

        transform.Translation += glm::dvec3(0, 0, 0);
    }

}
void WorldGameState::Render(GLFWwindow* window)
{
 

    //std::cout << "Render" << std::endl;
    //glfwSwapBuffers(this->window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    worldCamera.width = width;
    worldCamera.height = height;

    glm::vec4 incolor = { my_color[0],my_color[1],my_color[2],my_color[3] };
    shaders[0].setVec4("color", incolor);
 

    float cosA = std::cos(glm::pi<float>() * directionalAngle[0]);
    float cosB = std::cos(glm::pi<float>() * directionalAngle[1]);
    float sinA = std::sin(glm::pi<float>() * directionalAngle[0]);
    float sinB = std::sin(glm::pi<float>() * directionalAngle[1]);

    directionalDir = { cosA * sinB, sinA * sinB, cosB };



    //shader2.use();
    //shader2.setVec3("lightPos", cube.GetPosition() - worldCamera.Position);
    //cube.Draw(shader1);

    sceneRenderer.RenderScene();

    RenderImgui();

    glfwSwapBuffers(window);
}
void WorldGameState::RenderImgui()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImGui::Begin("eDNA");

    ImGui::Text("%.1f FPS ----- (%.3f ms)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Separator();

    ImGui::Text("%.3f , %.3f, %.3f", worldCamera.Position.x, worldCamera.Position.y, worldCamera.Position.z);
    ImGui::Separator();

    ImGui::Checkbox("(F1) Wireframe", &sceneRenderer.wireframe);
    ImGui::Separator();



    if (ImGui::CollapsingHeader("Shader Params", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::ColorEdit4("Shader Color", my_color);
        ImGui::Separator();

        float* ambientColorFloat[4] = { &ambientColor.r, &ambientColor.g, &ambientColor.b, &ambientColor.a };
        ImGui::ColorEdit4("Ambient Color", *ambientColorFloat);
        ImGui::Separator();

        float* directionalColorFloat[4] = { &directionalColor.r, &directionalColor.g, &directionalColor.b, &directionalColor.a };
        ImGui::ColorEdit4("Sun Color", *directionalColorFloat);
        ImGui::Separator();

        float* directionalAngleFloat[2] = { &directionalAngle.x, &directionalAngle.y };
        ImGui::SliderFloat2("Sun Direction", *directionalAngleFloat, -1.f, 1.f);
        ImGui::Separator();
    }

    if (ImGui::CollapsingHeader("Entity List", ImGuiTreeNodeFlags_DefaultOpen))
    {
        auto entityList = Registry.view<TagComponent>();
        for (auto entity : entityList)
        {
            auto tag = entityList.get<TagComponent>(entity);
            int i = (int)entity;
            std::string displayName = "[" + std::to_string(i) + "] " + tag.Tag;
            ImGui::Text(displayName.c_str());

        }
    }


    ImGui::End();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}