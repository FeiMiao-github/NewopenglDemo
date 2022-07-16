#include "demo/context.h"
#include "demo/coordination.h"
#include "demo/object.h"
#include "demo/shader.h"
#include "demo/shape.h"
#include "demo/colordef.h"

using namespace demo;

RenderTarget::RenderTarget() {}
RenderTarget::~RenderTarget() {}

CubeRender::CubeRender()
    : m_Cube(new Cube),
      m_Model(new LocalCoordination),
      m_ShaderProgram(nullptr)
{
    m_ShaderProgram = new ShaderProgram("cube.vs", "cube.fs");
    m_Model->Move(glm::vec3(0.0f, -1.0f,-0.0f));
    // m_Model->Rotate(glm::radians(-30.0f), glm::vec3(0, 0, 1.0f));
    // m_Model->Rotate(glm::radians(-30.0f), glm::vec3(0, 1.0f, 0.0f));
    // m_Model->Rotate(glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    auto &ctx = Context::Inst();
    m_ShaderProgram->SetProgramMat4("model", m_Model->Value());
    m_ShaderProgram->SetProgramMat4("projection", ctx->Proj()->Value());
    m_ShaderProgram->SetProgramMat4("view", ctx->View()->Value());
    m_ShaderProgram->SetProgramFloat4("vColor", Color::Coral);
    m_ShaderProgram->SetProgramFloat4("vLightingColor", ctx->LightColor());
    m_ShaderProgram->SetProgramFloat3("vLightPos", ctx->LightPos());
    m_ShaderProgram->SetProgramFloat3("vViewPos", ctx->ViewPos());
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
    auto &ctx = Context::Inst();
    m_ShaderProgram->SetProgramFloat4("vLightingColor", ctx->LightColor());
    m_ShaderProgram->SetProgramFloat3("vLightPos", ctx->LightPos());
    m_ShaderProgram->Use();
    m_Cube->Draw();
}