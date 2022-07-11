#include <cassert>

#include "demo/shader.h"
#include "demo/imgui.h"
#include "demo/triangle.h"

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

void DrawBuffer(GLuint program, GLuint triangle)
{
    glUseProgram(program);
    glBindVertexArray(triangle);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
}

struct Mat4Wrapper
{
public:
    Mat4Wrapper(const float e = 1.0f, const char* label = "")
        : m_Mat4(e), 
          m_Mat4Gui(m_Mat4, label)
    {
        ImGuiCtx::Inst()->Add(&m_Mat4Gui);
    }

    ~Mat4Wrapper()
    {
        ImGuiCtx::Inst()->Del(&m_Mat4Gui);
    }

    glm::mat4& Mat4()
    {
        return m_Mat4;
    }

private:
    glm::mat4 m_Mat4;
    Mat4Gui m_Mat4Gui;
};

class FloatWrapper
{
public:
    FloatWrapper(const float v, const char* label)
        : m_V(v),
          m_FloatSlider(m_V, label)
    {
        ImGuiCtx::Inst()->Add(&m_FloatSlider);
    }

    ~FloatWrapper()
    {
        ImGuiCtx::Inst()->Del(&m_FloatSlider);
    }

    float& Float()
    {
        return m_V;
    }

private:
    float m_V;
    FloatSlider m_FloatSlider;
};

int main()
{
    const int WINDOW_X = 0;
    const int WINDOW_Y = 0;
    const int WINDOW_H = 800;
    const int WINDOW_W = 800;
    const char* GLSL_VERSION = "#version 410";

    Mat4Wrapper model(1.0, "model");
    Mat4Wrapper view(1.0, "view");
    Mat4Wrapper projection(1.0, "projection");

    FloatWrapper model_rotation_x(0.0f, "model_rotation_x");
    FloatWrapper model_rotation_y(0.0f, "model_rotation_y");
    FloatWrapper model_rotation_z(0.0f, "model_rotation_z");

    ConfigGlfw();
    GLFWwindow* window = ConfigWindow(WINDOW_W, WINDOW_H, "Hello GL");
    glViewport(WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H);

    GLuint program = InitProgram();
    glUseProgram(program);
    
    SetProgramMat4(program, "view", view.Mat4());
    SetProgramMat4(program, "projection", projection.Mat4());

    GLuint triangle = MakeTriangleE();
    glfwSwapInterval(2);

    InitImgGui(window, GLSL_VERSION);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        DrawImGui();
        DrawBuffer(program, triangle);

        model.Mat4() = glm::mat4(1.0f);
        model.Mat4() = glm::rotate(model.Mat4(), glm::radians(model_rotation_x.Float()), glm::vec3(1.0f, 0.0f, 0.0f));
        model.Mat4() = glm::rotate(model.Mat4(), glm::radians(model_rotation_y.Float()), glm::vec3(0.0f, 1.0f, 0.0f));
        model.Mat4() = glm::rotate(model.Mat4(), glm::radians(model_rotation_z.Float()), glm::vec3(0.0f, 0.0f, 1.0f));
        SetProgramMat4(program, "model", model.Mat4());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    DestroyImGui();
    glDeleteBuffers(1, &triangle);
    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}