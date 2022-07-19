#include "demo/log.h"
#include "demo/material.h"
#include "demo/context.h"
#include "demo/texture.h"
#include "demo/object.h"

using namespace demo;

RenderTarget::RenderTarget() {}
RenderTarget::~RenderTarget() {}

CubeRender::CubeRender()
    : m_Cube(new Cube),
      m_Transform(new Transform {
        {0.0f, 0.0f,0.0f},
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
      }),
      m_Material(new Material(Material::test)),
      m_ShaderProgram(new ShaderProgram("cube.vs", "cube.fs")),
      m_Texture(new Texture("texture.jpeg")),
      m_CubeRenderUI(new imgui::CubeRenderUI(*this))
{
    Log::debug("sizeof material", sizeof(*m_Material));

    auto &ctx = Context::Inst();
    auto &lighting = ctx->GetLight();

    m_ShaderProgram->SetProgram("model", m_Transform->Mat4());
    m_ShaderProgram->SetProgram("projection", ctx->Proj()->Value());
    m_ShaderProgram->SetProgram("view", ctx->View()->Value());
    SetLightProp(lighting);
    m_ShaderProgram->SetProgram("vViewPos", ctx->ViewPos());
    SetMaterialProp();
}

CubeRender::~CubeRender()
{
    delete m_CubeRenderUI;
    m_CubeRenderUI = nullptr;

    delete m_Texture;
    m_Texture = nullptr;

    delete m_ShaderProgram;
    m_ShaderProgram = nullptr;

    delete m_Material;
    m_Material = nullptr;
    
    delete m_Transform;
    m_Transform = nullptr;

    delete m_Cube;
    m_Cube = nullptr;
}

void CubeRender::Draw()
{
    std::unique_ptr<Context> &ctx = Context::Inst();
    auto &lighting = ctx->GetLight();
    m_ShaderProgram->SetProgram("model", m_Transform->Mat4());

    SetLightProp(lighting);
    SetMaterialProp();

    m_ShaderProgram->Use();
    m_Texture->Use();
    m_Cube->Draw();
}

void CubeRender::SetLightProp(const Lighting& lighting)
{
    m_ShaderProgram->SetProgram("vLight.position", lighting.Pos());
    m_ShaderProgram->SetProgram("vLight.ambient", lighting.AmbientColor());
    m_ShaderProgram->SetProgram("vLight.diffuse", lighting.DiffuseColor());
    m_ShaderProgram->SetProgram("vLight.specular", lighting.SpecularColor());
}

void CubeRender::SetMaterialProp()
{
    // m_ShaderProgram->SetProgram("vMaterial.ambient", m_Material->ambient);
    // m_ShaderProgram->SetProgram("vMaterial.diffuse", 0);
    m_ShaderProgram->SetProgram("vMaterial.specular", m_Material->specular);
    m_ShaderProgram->SetProgram("vMaterial.shininess", m_Material->shininess);
}

imgui::CubeRenderUI::CubeRenderUI(CubeRender &cubeRender)
    : m_CubeRender(cubeRender),
      m_TransformUI(new TransformUI(*m_CubeRender.m_Transform)),
      m_MaterialUI(new MaterialUI(*m_CubeRender.m_Material))
{
    ImGuiCtx::Inst()->Add(this);
}

imgui::CubeRenderUI::~CubeRenderUI()
{
    ImGuiCtx::Inst()->Del(this);

    delete m_MaterialUI;
    m_MaterialUI = nullptr;

    delete m_TransformUI;
    m_TransformUI = nullptr;
}

void imgui::CubeRenderUI::Draw()
{
    if (ImGui::TreeNode("CubeRender"))
    {
        m_TransformUI->Draw();
        m_MaterialUI->Draw();
        ImGui::TreePop();
    }
}