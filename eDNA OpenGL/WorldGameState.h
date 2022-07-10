#pragma once
#include "GameState.h"
#include "CubeModel.h"
#include "SceneRenderer.h"
#include "MeshGenerator.h"

class WorldGameState :
    public GameState
{

private:

    bool firstMouse;
    bool enableMouse;
    float lastX;
    float lastY;
    float my_color[4];



public:

    glm::vec4 ambientColor;
    glm::vec4 directionalColor;
    glm::vec2 directionalAngle;
    glm::vec3 directionalDir;


    CubeModel cube;
    Camera worldCamera;
    SceneRenderer sceneRenderer;
    std::vector<class Shader> shaders;

    class MeshGenerator MG;

	WorldGameState(GLFWwindow* window, std::stack<GameState*>* GameStates);
	virtual ~WorldGameState();


    void MouseCallback(double xposIn, double yposIn) override;
    void KeyCallback(int key, int scancode, int action, int mode) override;



	void ProcessInputs(const float& dt);
	void Update(const float& dt);

	void Render(GLFWwindow* window);

	void RenderImgui();





};

