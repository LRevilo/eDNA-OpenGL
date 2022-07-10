#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm.h"
#include "stb.h"
#include <iostream>
#include <vector>
#include <stack>



class Game
{


private:

	GLFWwindow* window;
    // window settings
    std::string window_title;
    unsigned int window_width;
    unsigned int window_height;
    bool fullscreen;
    unsigned framerate_limit;
    bool vertical_sync_enabled;
    unsigned antialiasing_level;


    bool running;

    float currentFrame;
    float previousFrame;
    float dt;
   
    std::stack<class GameState*> GameStates;

    // Initialiation
    void initOpenGL();
    void initImGui();
	void initWindow();
    void initInputs();
    void initDeltaTime();
    void initGameStates();

    // Functions
    void UpdateDeltaTime();


public:

	Game();
	virtual ~Game();

    bool Running();
	GLFWwindow* GetWindow();


    // Main loop
    void ProcessInputs();
    void Update();
    void Render();
    void RenderImgui();

    void Exit();

    // Callbacks
    void FrameBufferSizeCallback(int width, int height);
    void ScrollCallback(double xoffset, double yoffset);
    void MouseCallback(double xpos, double ypos);
    void MouseButtonCallback(int button, int action, int mods);
    void KeyCallback(int key, int scancode, int action, int mode);
};

//Callback pointers declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

static void glfw_error_callback(int error, const char* description);

