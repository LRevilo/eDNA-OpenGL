#include "Game.h"
#include "GameState.h"
#include "WorldGameState.h"


Game::Game()
{
    running = true;
	initWindow();
    initInputs();
    initOpenGL();
    initImGui();
    initDeltaTime();
    initGameStates();
}

Game::~Game()
{

}

bool Game::Running()
{
    return running;
}
void Game::Exit()
{
    std::cout << "Terminating" << std::endl;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

GLFWwindow* Game::GetWindow()
{
    return window;
}

// Initilisations ----------------------------
void Game::initWindow()
{
    //std::cout << "initWindow" << std::endl;
    //open window.ini
    std::fstream ifs("config/window.ini");

    // default settings incase no config file
    window_title = "eDNA - (No config)";

    window_width = 800;
    window_height = 600;
    fullscreen = false;
    framerate_limit = 120;
    vertical_sync_enabled = false;
    antialiasing_level = 0;

    if (ifs.is_open())
    {
        std::getline(ifs, window_title);
        ifs >> window_width >> window_height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }

    ifs.close();

    // glfw: initialize and configure
// ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(window_width, window_height, window_title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //can't set callback to member function
}
void Game::initOpenGL()
{
    //std::cout << "initOpenGL" << std::endl;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glEnable(GL_DEPTH_TEST);
}
void Game::initImGui()
{
    glfwSetErrorCallback(glfw_error_callback);

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}
void Game::initInputs()
{
    //std::cout << "initInputs" << std::endl;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
}
void Game::initDeltaTime()
{
    //std::cout << "initDeltaTime" << std::endl;
    currentFrame = 0.f;
    previousFrame = 0.f;
    dt = 0.f;
}
void Game::initGameStates()
{
    GameStates.push(new WorldGameState(window,  &this->GameStates));
    //GameStates.push(new MainMenuGameState(window,  &this->GameStates));
}



// Game loop ----------------------------------
void Game::ProcessInputs()
{
    //std::cout << "ProcessInputs" << std::endl;
    if (!this->GameStates.empty())
    {
        this->GameStates.top()->ProcessInputs(dt);
    }
}
void Game::Update()
{
    this->UpdateDeltaTime();
    if (!GameStates.empty())
    {
        GameStates.top()->Update(dt);
        if (GameStates.top()->GetQuit())
        {
            // Add save function
            delete GameStates.top();
            GameStates.pop();
        }
    }
    else
    {
        running = false;
    }
}
void Game::Render()
{
    if (!GameStates.empty())
    {
        GameStates.top()->Render(window);
    }
}


// Functions ----------------------------------
void Game::UpdateDeltaTime()
{
    currentFrame = static_cast<float>(glfwGetTime());
    dt = currentFrame - previousFrame;
    previousFrame = currentFrame;
}


// Callbacks
void Game::FrameBufferSizeCallback(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Game::ScrollCallback(double xoffset, double yoffset)
{
    //fov -= (float)yoffset;
    //if (fov < 1.0f)
    //    fov = 1.0f;
    //if (fov > 45.0f)
    //    fov = 45.0f;

    if (!GameStates.empty())
    {
        GameStates.top()->ScrollCallback(xoffset, yoffset);
    }
}

void Game::MouseCallback(double xposIn, double yposIn)
{
    if (!GameStates.empty())
    {
        GameStates.top()->MouseCallback(xposIn, yposIn);
    }
}

void Game::MouseButtonCallback(int button, int action, int mods)
{
    if (!GameStates.empty())
    {
        GameStates.top()->MouseButtonCallback(button, action, mods);
    }
}

void Game::KeyCallback(int key, int scancode, int action, int mode)
{
    if (!GameStates.empty())
    {
        GameStates.top()->KeyCallback(key, scancode, action, mode);
    }

}



// Callback pointers
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Game* game_callback = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
    game_callback->FrameBufferSizeCallback(width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Game* game_callback = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
    game_callback->ScrollCallback(xoffset, yoffset);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Game* game_callback = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
    game_callback->MouseCallback(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Game* game_callback = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
    game_callback->MouseButtonCallback(button, action, mods);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    Game* game_callback = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
    game_callback->KeyCallback(key, scancode, action, mode);
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}