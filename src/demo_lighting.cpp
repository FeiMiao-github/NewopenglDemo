#include "demo/context.h"
#include "demo/imgui.h"
#include "demo/lighting.h"
#include "demo/shader.h"
#include "demo/colordef.h"
#include "demo/log.h"

using namespace demo;

Lighting::Lighting()
    : m_Cube(new Cube),
      m_ShaderProgram(new ShaderProgram("lighting.vs", "lighting.fs")),
      m_Model(new LocalCoordination),
      m_Color(Color::White),
      m_Pos(0.0f, 4.0f, -10.0f),
      m_PosPublisher(new imgui::PosPublisher("Lighting"))
{
    m_Model->Move(m_Pos);
    m_ShaderProgram->SetProgramMat4("model", m_Model->Value());

    auto &ctx = Context::Inst();
    m_ShaderProgram->SetProgramMat4("projection", ctx->Proj()->Value());
    m_ShaderProgram->SetProgramMat4("view", ctx->View()->Value());
    m_ShaderProgram->SetProgramFloat4("vLightingColor", m_Color);

    ctx->SetLight(this);
    m_PosPublisher->AddSubscriber(this);
}

Lighting::~Lighting()
{
    m_PosPublisher->RemoveSubscriber(this);
    delete m_PosPublisher;
    m_PosPublisher = nullptr;

    auto &ctx = Context::Inst();
    ctx->SetLight(nullptr);

    delete m_Cube;
    m_Cube = nullptr;
    delete m_ShaderProgram;
    m_ShaderProgram = nullptr;
}

void Lighting::Draw()
{
    m_ShaderProgram->SetProgramMat4("model", m_Model->Value());
    m_ShaderProgram->Use();
    m_Cube->Draw();
}

const glm::vec4 Lighting::Color() const
{
    return m_Color;
}

void Lighting::SetColor(const glm::vec4& color)
{
    m_Color = color;
}

const glm::vec3 Lighting::Pos() const
{
    return m_Pos;
}

void Lighting::SetPos(const glm::vec3& pos)
{
    m_Pos = pos;
    m_Model->MoveTo(pos);
}

void Lighting::UpdatePos(const glm::vec3& pos)
{
    Log::debug("update lighting pos: ", pos);
    SetPos(pos);
}