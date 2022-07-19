#include "demo/context.h"
#include "demo/imgui.h"
#include "demo/lighting.h"
#include "demo/shader.h"
#include "demo/colordef.h"
#include "demo/log.h"
#include "glm/ext/vector_float3.hpp"

using namespace demo;

Lighting::Lighting()
    : m_Cube(new Cube),
      m_ShaderProgram(new ShaderProgram("lighting.vs", "lighting.fs")),
      m_Transform(new Transform {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.1f, 0.1f, 0.1f}
      }),
      m_Color(1.0f, 1.0f, 1.0f),
      m_LightingUI(new imgui::LightingUI(*this))
{
    SetAmbient({0.1f, 0.1f, 0.1f});
    SetDiffuse({0.5f, 0.5f, 0.5f});
    SetSpecular({1.0f, 1.0f, 1.0f});

    auto &ctx = Context::Inst();
    m_ShaderProgram->SetProgram("model", m_Transform->Mat4());
    m_ShaderProgram->SetProgram("projection", ctx->Proj()->Value());
    m_ShaderProgram->SetProgram("view", ctx->View()->Value());
    m_ShaderProgram->SetProgram("vLightingColor", m_Color);

    ctx->SetLight(this);
}

Lighting::~Lighting()
{

    auto &ctx = Context::Inst();
    ctx->SetLight(nullptr);

    delete m_Cube;
    m_Cube = nullptr;

    delete m_ShaderProgram;
    m_ShaderProgram = nullptr;

    delete m_Transform;
    m_Transform = nullptr;

    delete m_LightingUI;
    m_LightingUI = nullptr;
}

void Lighting::Draw()
{
    m_ShaderProgram->SetProgram("model", m_Transform->Mat4());
    m_ShaderProgram->Use();
    m_Cube->Draw();
}

const glm::vec3 Lighting::Color() const
{
    return m_Color;
}

void Lighting::SetColor(const glm::vec3& color)
{
    m_Color = color;
}

const glm::vec3 Lighting::AmbientColor() const
{
    return m_AmbientColor;
}

void Lighting::SetAmbient(const glm::vec3 &ambient)
{
    m_Ambient = ambient;
    m_AmbientColor = ambient * m_Color;
}

const glm::vec3 Lighting::DiffuseColor() const
{
    return m_DiffuseColor;
}

void Lighting::SetDiffuse(const glm::vec3 &diffuse)
{
    m_Diffuse = diffuse;
    m_DiffuseColor = diffuse * m_Color;
}

const glm::vec3 Lighting::SpecularColor() const
{
    return m_SpecularColor;
}

void Lighting::SetSpecular(const glm::vec3 &specular)
{
    m_Specular = specular;
    m_SpecularColor = specular * m_Color;
}

const glm::vec3 Lighting::Pos() const
{
    return m_Transform->Pos();
}

void Lighting::SetPos(const glm::vec3& pos)
{
    m_Transform->SetPos(pos);
}

const glm::vec3 Lighting::Rotation() const
{
    return m_Transform->Rotation();
}

void Lighting::SetRotation(const glm::vec3& rotation)
{
    m_Transform->SetRotation(rotation);
}

const glm::vec3 Lighting::Scale() const
{
    return m_Transform->Scale();
}

void Lighting::SetScale(const glm::vec3& scale)
{
    m_Transform->SetScale(scale);
}

imgui::LightingUI::LightingUI(Lighting& lighting)
    : m_Lighting(lighting),
      m_TransformUI(new TransformUI(*lighting.m_Transform))
{
    ImGuiCtx::Inst()->Add(this);
}

imgui::LightingUI::~LightingUI()
{
    ImGuiCtx::Inst()->Del(this);
    delete m_TransformUI;
    m_TransformUI = nullptr;
}

void imgui::LightingUI::Draw()
{
    if (ImGui::TreeNode("Lighting"))
    {
        m_TransformUI->Draw();
        ImGui::TreePop();
    }
}
