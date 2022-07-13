#include "demo/coordination.h"
#include "demo/object.h"
#include "demo/shader.h"
#include "demo/shape.h"
#include "demo/colordef.h"

using namespace demo;

RenderTarget::RenderTarget(Context& ctx)
    : m_Context(ctx)
{
}

RenderTarget::~RenderTarget()
{
}

// Cube* RenderTarget::GetCube()
// {
//     return m_Cube;
// }

// void RenderTarget::SetCube(Cube *cube)
// {
//     if (cube == nullptr)
//     {
//         return;
//     }

//     if (m_Cube != nullptr)
//     {
//         delete m_Cube;
//     }

//     m_Cube = new Cube(*cube);
// }

// ShaderProgram* RenderTarget::GetShaderProgram()
// {
//     return m_ShaderProgram;
// }

// void RenderTarget::SetShaderProgram(ShaderProgram* shaderProgram)
// {
//     if (shaderProgram == nullptr)
//     {
//         return;
//     }

//     if (m_ShaderProgram != nullptr)
//     {
//         delete m_ShaderProgram;
//     }

//     m_ShaderProgram = new ShaderProgram(*shaderProgram);
// }

CubeRender::CubeRender(Context& ctx)
    : RenderTarget(ctx),
      m_Cube(new Cube),
      m_Model(new LocalCoordination),
      m_ShaderProgram(nullptr)
{
    Shader* vertexShader = new VertexShader("cube.vs");
    Shader* fragmentShader = new FragmentShader("cube.fs");
    m_ShaderProgram = new ShaderProgram({vertexShader, fragmentShader});
    delete fragmentShader;
    delete vertexShader;

    m_ShaderProgram->SetProgramFloat3("vColor", Color::Coral);
}

CubeRender::~CubeRender()
{
    delete m_Cube;
    m_Cube = nullptr;
    delete m_Model;
    m_Model = nullptr;
    delete m_ShaderProgram;
    m_ShaderProgram = nullptr;
}

void CubeRender::Draw()
{
    m_Model->Rotate(glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_ShaderProgram->SetProgramMat4("model", m_Model->Value());

    m_ShaderProgram->SetProgramMat4("view", m_Context.View()->Value());
    m_ShaderProgram->SetProgramMat4("projection", m_Context.Proj()->Value());
    m_ShaderProgram->SetProgramFloat3("vLightingColor", m_Context.LightColor());

    m_ShaderProgram->Use();
    m_Cube->Draw();
}