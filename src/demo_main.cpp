#include <cassert>

#include "demo/shader.h"
#include "demo/imgui.h"
#include "demo/shape.h"
#include "demo/texture.h"
#include "demo/coordination.h"

auto framebufferSizeCB = [](GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
};

auto keyCB = [](GLFWwindow* window, int key, int, int action, int)
{
    if (action != GLFW_PRESS)
    {
        return;
    }

    if (key == GLFW_KEY_Q)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
};

void ConfigGlfw()
{
    int ret = glfwInit();
    assert(ret == GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
    glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
}

GLFWwindow* ConfigWindow(int width, int height, const char* title)
{
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);
    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) != GLFW_FALSE);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCB);
    glfwSetKeyCallback(window, keyCB);
    return window;
}

int main()
{
    const int WINDOW_X = 0;
    const int WINDOW_Y = 0;
    const int WINDOW_H = 800;
    const int WINDOW_W = 800;
    const char* GLSL_VERSION = "#version 410";

    glm::mat4 view(1.0);
    glm::mat4 projection(1.0);

    ConfigGlfw();
    GLFWwindow* window = ConfigWindow(WINDOW_W, WINDOW_H, "Hello GL");
    glViewport(WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H);

    GLuint program = InitProgram();
    glUseProgram(program);
    
    demo::LocalCoordination model;
    model.Rotate(glm::radians(30.0f), glm::vec3(1, 0, 0));
    model.Rotate(glm::radians(30.0f), glm::vec3(0, 1, 0));
    model.Rotate(glm::radians(30.0f), glm::vec3(0, 0, 1));

    SetProgramMat4(program, "model", model.Value());
    SetProgramMat4(program, "view", view);
    SetProgramMat4(program, "projection", projection);

    Cube *cube = new Cube;
    glfwSwapInterval(2);

    InitImgGui(window, GLSL_VERSION);
    Texture *texture = new Texture("texture.jpeg");

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture->Use();

        glUseProgram(program);
        cube->DrawBuffer();
        DrawImGui();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete texture;
    DestroyImGui();
    delete cube;
    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}