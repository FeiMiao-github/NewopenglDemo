#include "demo/colordef.h"
#include "demo/imgui.h"
#include "demo/material.h"
#include "demo/log.h"

using namespace demo;
using namespace demo::imgui;

const Material Material::test = {{1.0f, 0.5f, 0.31f}, {1.0f, 0.5f, 0.31f}, {0.5f, 0.5f, 0.5f}, 64.0f};

MaterialUI::MaterialUI(Material& material)
    : m_Material(material),
      m_AmbientPublisher(new AmbientPublisher("Ambient", material.ambient)),
      m_DiffusePublisher(new DiffusePublisher("Diffuse", material.diffuse)),
      m_SpecularPublisher(new SpecularPublisher("Specular", material.specular)),
      m_ShinessPublisher(new ShinessPublisher("shiness", material.shininess))
{
    m_AmbientPublisher->AddSubscriber(this);
    m_DiffusePublisher->AddSubscriber(this);
    m_SpecularPublisher->AddSubscriber(this);
    m_ShinessPublisher->AddSubscriber(this);
}

MaterialUI::~MaterialUI()
{
    m_ShinessPublisher->RemoveSubscriber(this);
    m_SpecularPublisher->RemoveSubscriber(this);
    m_DiffusePublisher->RemoveSubscriber(this);
    m_AmbientPublisher->RemoveSubscriber(this);

    delete m_ShinessPublisher;
    m_ShinessPublisher = nullptr;

    delete m_SpecularPublisher;
    m_SpecularPublisher = nullptr;

    delete m_DiffusePublisher;
    m_DiffusePublisher = nullptr;

    delete m_AmbientPublisher;
    m_AmbientPublisher = nullptr;
}

void MaterialUI::Update(AmbientPublisher*, const AmbientSubscriber::Type& ambient)
{
    Log::debug("update ambient: ", ambient);
    m_Material.ambient = ambient;
}

void MaterialUI::Update(DiffusePublisher*, const DiffuseSubscriber::Type& diffuse)
{
    Log::debug("update diffuse: ", diffuse);
    m_Material.diffuse = diffuse;
}

void MaterialUI::Update(SpecularPublisher*, const SpecularSubscriber::Type& specular)
{
    Log::debug("update specular: ", specular);
    m_Material.specular = specular;
}

void MaterialUI::Update(ShinessPublisher*, const ShinessSubscriber::Type& shiness)
{
    Log::debug("update shiness:", shiness);
    m_Material.shininess = shiness;
}

void MaterialUI::Draw()
{
    if (ImGui::TreeNode("Material"))
    {
        m_AmbientPublisher->Draw();
        m_DiffusePublisher->Draw();
        m_SpecularPublisher->Draw();
        m_ShinessPublisher->Draw();
        ImGui::TreePop();
    }
}